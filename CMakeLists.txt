# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(PWM_LED_Controller)



# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(PWM_LED_Controller
    main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(PWM_LED_Controller
pico_stdlib
pico_cyw43_arch_none
hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(PWM_LED_Controller)
