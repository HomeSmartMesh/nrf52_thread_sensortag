/**
 * Copyright (c) 2017 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup thread_mqttsn_sleepy_publisher_example_main main.c
 * @{
 * @ingroup thread_mqttsn_sleepy_publisher_example
 * @brief Thread MQTT-SN Sleepy Publisher Example Application main file.
 *
 * @details This example demonstrates an MQTT-SN sleepy publisher application that enables to toggle
 *          BSP_LED_2 on a board with related MQTT-SN sleepy subscriber application via MQTT-SN messages.
 *          As the MQTT-SN sleepy publisher has no subscriptions, it will not need to receive data except
 *          for ACKs for its own messages, so asynchronous receiving is not needed. It therefore serves
 *          as a Thread Sleepy End Device.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "app_timer.h"
#include "bsp_thread.h"
#include "nrf_assert.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "mqttsn_client.h"
#include "thread_utils.h"

#include <openthread/ip6.h>
#include <openthread/thread.h>

#define DEFAULT_CHILD_TIMEOUT    40                                         /**< Thread child timeout [s]. */
#define DEFAULT_POLL_PERIOD      1000                                       /**< Thread Sleepy End Device polling period when MQTT-SN Asleep. [ms] */
#define SHORT_POLL_PERIOD        100                                        /**< Thread Sleepy End Device polling period when MQTT-SN Awake. [ms] */
#define SEARCH_GATEWAY_TIMEOUT   5                                          /**< MQTT-SN Gateway discovery procedure timeout in [s]. */                                   

static mqttsn_client_t      m_client;                                       /**< An MQTT-SN client instance. */
static mqttsn_remote_t      m_gateway_addr;                                 /**< A gateway address. */
static uint8_t              m_gateway_id;                                   /**< A gateway ID. */
static mqttsn_connect_opt_t m_connect_opt;                                  /**< Connect options for the MQTT-SN client. */
static uint8_t              m_led_state        = 0;                         /**< Previously sent BSP_LED_2 command. */
static uint16_t             m_msg_id           = 0;                         /**< Message ID thrown with MQTTSN_EVENT_TIMEOUT. */
static char                 m_client_id[]      = "nRF52840_publisher";      /**< The MQTT-SN Client's ID. */
static char                 m_topic_name[]     = "nRF52840_resources/led3"; /**< Name of the topic corresponding to subscriber's BSP_LED_2. */
static mqttsn_topic_t       m_topic            =                            /**< Topic corresponding to subscriber's BSP_LED_2. */
{
    .p_topic_name = (unsigned char *)m_topic_name,
    .topic_id     = 0,
};

/***************************************************************************************************
 * @section MQTT-SN
 **************************************************************************************************/

/**@brief Turns the MQTT-SN network indication LED on.
 *
 * @details This LED is on when an MQTT-SN client is in connected or awake state.
 */
static void light_on(void)
{
    LEDS_ON(BSP_LED_3_MASK);
}

/**@brief Turns the MQTT-SN network indication LED off.
 *
 * @details This LED is on when an MQTT-SN client is in disconnected or asleep state.
 */
static void light_off(void)
{
    LEDS_OFF(BSP_LED_3_MASK);
}

/**@brief Puts MQTT-SN client in sleep mode.
 *
 * @details This function changes Thread Sleepy End Device polling period to default.
 */
static void sleep(void)
{
    otError error;

    error = otLinkSetPollPeriod(thread_ot_instance_get(), DEFAULT_POLL_PERIOD);
    ASSERT(error == OT_ERROR_NONE);
}

/**@brief Puts MQTT-SN client in active mode.
 *
 * @details This function changes Thread Sleepy End Device polling period to short.
 */
static void wake_up(void)
{
    otError error;

    error = otLinkSetPollPeriod(thread_ot_instance_get(), SHORT_POLL_PERIOD);
    ASSERT(error == OT_ERROR_NONE);
}

/**@brief Initializes MQTT-SN client's connection options.
 */
static void connect_opt_init(void)
{
    m_connect_opt.alive_duration = MQTTSN_DEFAULT_ALIVE_DURATION,
    m_connect_opt.clean_session  = MQTTSN_DEFAULT_CLEAN_SESSION_FLAG,
    m_connect_opt.will_flag      = MQTTSN_DEFAULT_WILL_FLAG,
    m_connect_opt.client_id_len  = strlen(m_client_id),

    memcpy(m_connect_opt.p_client_id, (unsigned char *)m_client_id, m_connect_opt.client_id_len);
}

/**@brief Processes GWINFO message from a gateway.
 *
 * @details This function initializes MQTT-SN Client's connect options and launches the connect procedure.
 *
 * @param[in]    p_event  Pointer to MQTT-SN event.
 */
static void gateway_info_callback(mqttsn_event_t * p_event)
{
    m_gateway_addr  = *(p_event->event_data.connected.p_gateway_addr);
    m_gateway_id    = p_event->event_data.connected.gateway_id;
}

/**@brief Processes CONNACK message from a gateway.
 *
 * @details This function launches the topic registration procedure if necessary.
 */
static void connected_callback(void)
{
    light_on();

    uint32_t err_code = mqttsn_client_topic_register(&m_client,
                                                     m_topic.p_topic_name,
                                                     strlen(m_topic_name),
                                                     &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("REGISTER message could not be sent. Error code: 0x%x\r\n", err_code);
    }
}

/**@brief Processes DISCONNECT message from a gateway. */
static void disconnected_callback(void)
{
    light_off();
    sleep();
}

/**@brief Processes REGACK message from a gateway.
 *
 * @details This function puts the client in sleep mode.
 *
 * @param[in] p_event Pointer to MQTT-SN event.
 */
static void regack_callback(mqttsn_event_t * p_event)
{
    m_topic.topic_id = p_event->event_data.registered.packet.topic.topic_id;
    NRF_LOG_INFO("MQTT-SN event: Topic has been registered with ID: %d.\r\n",
                 p_event->event_data.registered.packet.topic.topic_id);

    sleep();
}

/**@brief Processes PUBACK message from a gateway.
 *
 * @details This function puts the client in sleep mode.
 */
static void puback_callback(void)
{
    sleep();
}

/**@brief Processes DISCONNECT message being a response to sleep request.
 *
 * @details This function puts the client in sleep mode.
 */
static void sleep_callback(void)
{
    sleep();
}

/**@brief Processes callback from keep-alive timer timeout.
 *
 * @details This function puts the client in active mode.
 */
static void wakeup_callback(void)
{
    wake_up();
}

/**@brief Processes retransmission limit reached event. */
static void timeout_callback(mqttsn_event_t * p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Timed-out message: %d. Message ID: %d.\r\n",
                  p_event->event_data.error.msg_type,
                  p_event->event_data.error.msg_id);
}

/**@brief Processes results of gateway discovery procedure. */
static void searchgw_timeout_callback(mqttsn_event_t * p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Gateway discovery result: 0x%x.\r\n", p_event->event_data.discovery);
    sleep();
}

/**@brief Function for handling MQTT-SN events. */
void mqttsn_evt_handler(mqttsn_client_t * p_client, mqttsn_event_t * p_event)
{
    switch (p_event->event_id)
    {
        case MQTTSN_EVENT_GATEWAY_FOUND:
            NRF_LOG_INFO("MQTT-SN event: Client has found an active gateway.\r\n");
            gateway_info_callback(p_event);
            break;

        case MQTTSN_EVENT_CONNECTED:
            NRF_LOG_INFO("MQTT-SN event: Client connected.\r\n");
            connected_callback();
            break;

        case MQTTSN_EVENT_DISCONNECTED:
            NRF_LOG_INFO("MQTT-SN event: Client disconnected.\r\n");
            disconnected_callback();
            break;

        case MQTTSN_EVENT_REGISTERED:
            NRF_LOG_INFO("MQTT-SN event: Client registered topic.\r\n");
            regack_callback(p_event);
            break;

        case MQTTSN_EVENT_PUBLISHED:
            NRF_LOG_INFO("MQTT-SN event: Client has successfully published content.\r\n");
            puback_callback();
            break;

        case MQTTSN_EVENT_SLEEP_PERMIT:
            NRF_LOG_INFO("MQTT-SN event: Client permitted to sleep.\r\n");
            sleep_callback();
            break;

        case MQTTSN_EVENT_SLEEP_STOP:
            NRF_LOG_INFO("MQTT-SN event: Client wakes up.\r\n");
            wakeup_callback();
            break;

        case MQTTSN_EVENT_TIMEOUT:
            NRF_LOG_INFO("MQTT-SN event: Retransmission retries limit has been reached.\r\n");
            timeout_callback(p_event);
            break;

        case MQTTSN_EVENT_SEARCHGW_TIMEOUT:
            NRF_LOG_INFO("MQTT-SN event: Gateway discovery procedure has finished.\r\n");
            searchgw_timeout_callback(p_event);
            break;

        default:
            break;
    }
}

/***************************************************************************************************
 * @section State
 **************************************************************************************************/

static void state_changed_callback(uint32_t flags, void * p_context)
{
    NRF_LOG_INFO("State changed! Flags: 0x%08x Current role: %d\r\n",
                 flags, otThreadGetDeviceRole(p_context));
}

/***************************************************************************************************
 * @section Buttons
 **************************************************************************************************/

static void led_state_pub(uint8_t led_state)
{
    uint32_t err_code = mqttsn_client_publish(&m_client, m_topic.topic_id, &led_state, 1, &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("PUBLISH message could not be sent. Error code: 0x%x\r\n", err_code)
    }
}

static void publish(void)
{
    m_led_state = m_led_state == 1 ? 0 : 1;
    led_state_pub(m_led_state);
}

static void bsp_event_handler(bsp_event_t event)
{
    if (otThreadGetDeviceRole(thread_ot_instance_get()) < OT_DEVICE_ROLE_CHILD )
    {
        (void)event;
        return;
    }

    switch (event)
    {
        case BSP_EVENT_KEY_1:
        {
            wake_up();

            uint32_t err_code = mqttsn_client_search_gateway(&m_client, SEARCH_GATEWAY_TIMEOUT);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
            }
            break;
        }

        case BSP_EVENT_KEY_2:
        {
            wake_up();

            uint32_t err_code;

            if (mqttsn_client_state_get(&m_client) == MQTTSN_CLIENT_CONNECTED)
            {
                err_code = mqttsn_client_disconnect(&m_client);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("DISCONNECT message could not be sent. Error: 0x%x\r\n", err_code);
                }
            }
            else
            {
                err_code = mqttsn_client_connect(&m_client, &m_gateway_addr, m_gateway_id, &m_connect_opt);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("CONNECT message could not be sent. Error: 0x%x\r\n", err_code);
                }
            }
            break;
        }

        case BSP_EVENT_KEY_3:
        {
            wake_up();
            publish();
            break;
        }

        default:
        {
            break;
        }
    }
}

/***************************************************************************************************
 * @section Initialization
 **************************************************************************************************/

/**@brief Function for initializing the Application Timer Module.
 */
static void timer_init(void)
{
    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the LEDs.
 */
static void leds_init(void)
{
    LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);
}

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for initializing the Thread Board Support Package.
 */
static void thread_bsp_init(void)
{
    uint32_t err_code;
    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_thread_init(thread_ot_instance_get());
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the Thread Stack.
 */
static void thread_instance_init(void)
{
    thread_configuration_t thread_configuration =
    {
        .radio_mode            = THREAD_RADIO_MODE_RX_OFF_WHEN_IDLE,
        .autocommissioning     = true,
        .poll_period           = DEFAULT_POLL_PERIOD,
        .default_child_timeout = DEFAULT_CHILD_TIMEOUT,
    };

    thread_init(&thread_configuration);
    thread_state_changed_callback_set(state_changed_callback);
}

/**@brief Function for initializing the MQTTSN client.
 */
static void mqttsn_init(void)
{
    uint32_t err_code = mqttsn_client_init(&m_client,
                                           MQTTSN_DEFAULT_CLIENT_PORT,
                                           mqttsn_evt_handler,
                                           thread_ot_instance_get());
    APP_ERROR_CHECK(err_code);

    connect_opt_init();
}

/***************************************************************************************************
 * @section Main
 **************************************************************************************************/

int main(int argc, char *argv[])
{
    log_init();
    timer_init();
    leds_init();

    thread_instance_init();
    thread_bsp_init();
    mqttsn_init();

    while (true)
    {
        thread_process();

        if (NRF_LOG_PROCESS() == false)
        {
            thread_sleep();
        }
    }
}

/**
 *@}
 **/
