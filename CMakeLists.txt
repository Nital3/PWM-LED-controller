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
