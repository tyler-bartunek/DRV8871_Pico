# --- Add my subdirectories ---
add_subdirectory(../src)

# --- Executable ---
add_executable(fixed_speed_test
    main.cpp
)

target_link_libraries(fixed_speed_test PRIVATE utils pico_stdlib)


# --- Enable USB I/O ---
pico_enable_stdio_usb(motor_test 1)
pico_enable_stdio_uart(motor_test 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(fixed_speed_test)
