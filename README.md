# G547
Kernel module for a virtual 8 Channel ADC. Resolution of ADC is 10bit and the result is
stored in a 16-bit register. Settings can be changed to store the result in lower or higher 10 bits in
the 16-bit result register. Character device driver for this ADC must export the device file named
“adc8” into the /dev directory. Implement following system calls in the driver
● Open
● Read (to read the ADC output from selected channel )
● IOCTL (to select channel 0-7 and to select alignment of 10-bit result)
● Close
