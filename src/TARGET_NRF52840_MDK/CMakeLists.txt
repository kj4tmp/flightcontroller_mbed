add_library(mbed-nrf52840_mdk INTERFACE)

target_sources(mbed-nrf52840_mdk
    INTERFACE
        PeripheralPins.c
)

target_include_directories(mbed-nrf52840_mdk
    INTERFACE
        .
)

target_link_libraries(mbed-nrf52840_mdk INTERFACE mbed-MCU_NRF52840)