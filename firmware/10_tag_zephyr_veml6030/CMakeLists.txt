# SPDX-License-Identifier: Apache-2.0

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(light_sensor)
#zephyr_include_directories(../drivers)

target_sources(app PRIVATE src/main.c)

