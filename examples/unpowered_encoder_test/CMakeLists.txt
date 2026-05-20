# --- Executable ---
add_executable(unpowered_encoder_test
    main.cpp
)

target_link_libraries(unpowered_encoder_test PRIVATE DRV8871 pico_stdlib)


# --- Enable USB I/O ---
pico_enable_stdio_usb(unpowered_encoder_test 1)
pico_enable_stdio_uart(unpowered_encoder_test 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(unpowered_encoder_test)