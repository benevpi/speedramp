# speedramp

This will run some basic benchmarks on your Pico and publish the results over the UART. Each loop, it'll increase the speed and try again. At some point, it'll crash, and this is the fastest your Pico can go

# Options

You can chance #define VREG_VSEL VREG_VOLTAGE_1_30 to other voltages if you want to know the speed your pico can go at different voltages

# Compiling

If you want to build this yourself, you'll need the Pico SDK installed and working
