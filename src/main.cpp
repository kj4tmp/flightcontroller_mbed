#include <stdio.h>
#include <mbed.h>
//#include <rtos.h>
//#include <rtos.h>
#include <seven_segment.h>
SPI spi(p30, p4, p3); // mosi, miso, sclk
DigitalOut cs(p2); //rclk

int main()
{
    // Blink LED
    spi.format(8, 3);
    spi.frequency(10000);

    cs = 0;
    spi.write(0b00000000);
    cs = 1;
    while (1) {
        //myled = 1;          // set LED1 pin to high
        //printf("myled = %d \n\r", (uint8_t)myled);
        //wait_us(1000000);
        //ThisThread::sleep_for(1s);

        //myled.write(0);     // set LED1 pin to low
        //printf("myled = %d \n\r", myled.read());
        //ThisThread::sleep_for(1s);
        //wait_us(1000000);
        cs = 1;
        for (uint8_t i = 0; i < 10; i++)
        {
            
            //spi.write(seven_segment_int_to_uint8(i));
            
            char *command = seven_segment_float_to_command(23.457);
            for (uint8_t i = 0; i < 9; i++)
            {   
                cs = 0;
                spi.write(command[2*i]);
                spi.write(command[2*i+1]);
                cs = 1;
                wait_us(2000000);
            }
            //ThisThread::sleep_for(1s);
            wait_us(20000);
            
        }
        
        
    }
}