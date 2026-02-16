# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
#set(PICO_BOARD pico_w CACHE STRING "Board type")
#set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID for examples")
#set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password for examples")

if (PICO_CYW43_SUPPORTED) # set by PICO_BOARD=pico_w
if (NOT TARGET pico_cyw43_arch)
    message("Skipping Pico W examples as support is not available")
else()

    if (DEFINED ENV{WIFI_SSID} AND (NOT WIFI_SSID))
        set(WIFI_SSID $ENV{WIFI_SSID})
        message("Using WIFI_SSID from environment ('${WIFI_SSID}')")
    endif()

    if (DEFINED ENV{WIFI_PASSWORD} AND (NOT WIFI_PASSWORD))
        set(WIFI_PASSWORD $ENV{WIFI_PASSWORD})
        message("Using WIFI_PASSWORD from environment")
    endif()

    set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID for examples")
    set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password for examples")

    if (NOT TARGET pico_btstack_base)
        message("Skipping Pico W Bluetooth examples as support is not available")
    endif()
endif()
endif()

set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID for examples")
set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password for examples")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(tb6612 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(tb6612 tb6612.c)
#add_executable(motorw motor_web.c)
#add_executable(test test.c)

#target_compile_definitions(motorw PRIVATE
#    WIFI_SSID=\"${WIFI_SSID}\"
#    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
#    )

#target_compile_definitions(test PRIVATE
#    WIFI_SSID=\"${WIFI_SSID}\"
#    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
#    )

#target_include_directories(motorw PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}
    #${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
#    ${PICO_LWIP_CONTRIB_PATH}/apps/httpd
#    )

#target_include_directories(test PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}
    #${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
#    ${PICO_LWIP_CONTRIB_PATH}/apps/httpd
#    )

pico_set_program_name(tb6612 "tb6612")
#pico_set_program_version(tb6612 "0.3")

#pico_set_program_name(motorw "motorw")
#pico_set_program_version(motorw "0.1")

#pico_set_program_name(test "test")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(tb6612 1)
pico_enable_stdio_usb(tb6612 0)

# Add libraries to the build
target_link_libraries(tb6612 PRIVATE
    pico_stdlib
    hardware_pwm
    )

# Add libraries to the build
#target_link_libraries(motorw PRIVATE
#    pico_cyw43_arch_lwip_threadsafe_background
#    pico_lwip_http
#    pico_lwip_mdns
#    pico_httpd_content
#    pico_stdlib
#    hardware_pwm
#)

# Add libraries to the build
#target_link_libraries(test PRIVATE
#pico_cyw43_arch_lwip_threadsafe_background
#pico_lwip_http
#pico_lwip_mdns
#pico_httpd_content
#pico_stdlib
#pico_printf
#hardware_pwm
#)

# Add the standard include files to the build
target_include_directories(tb6612 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)
# Add the standard include files to the build
#target_include_directories(motorw PRIVATE
#  ${CMAKE_CURRENT_LIST_DIR}
#)

pico_add_extra_outputs(tb6612)
#pico_add_extra_outputs(motorw)
#pico_add_extra_outputs(test)

#pico_add_library(motorw NOFLAG)
#pico_set_lwip_httpd_content(motorw INTERFACE
#        ${CMAKE_CURRENT_LIST_DIR}/content/404.html
#        ${CMAKE_CURRENT_LIST_DIR}/content/index.shtml
#        ${CMAKE_CURRENT_LIST_DIR}/content/test.shtml
#        ${CMAKE_CURRENT_LIST_DIR}/content/ledpass.shtml
#        ${CMAKE_CURRENT_LIST_DIR}/content/ledfail.shtml
#        ${CMAKE_CURRENT_LIST_DIR}/content/img/rpi.png.gz
#        )
