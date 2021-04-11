# SPDX-License-Identifier: Apache-2.0

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CONF_FILE prj.conf)

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tag_hello)

target_sources(app PRIVATE src/main.c)

