#include "uop_msb.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb;
using namespace chrono;

//Fun output stuff
LCD_16X2_DISPLAY disp;
Buzzer buzz;
LatchedLED ledDisp(LatchedLED::STRIP);

DigitalOut green_led(PC_6);
DigitalOut yellow_led(PC_3);
DigitalOut red_led(PC_2);

//Analogue Inputs
AnalogIn pot(AN_POT_PIN);
AnalogIn ldr(AN_LDR_PIN);
AnalogIn mic(MIC_AN_PIN);

int main()
{

    //Test LED Bar Display
    ledDisp.enable(true);



    while (true) {
        //Read Analog to Digital Converter values (16 bit)
        unsigned short potVal   = pot.read_u16();
        unsigned short lightVal = ldr.read_u16();
        signed int micVal   = mic.read_u16()-32768; 

        //Write to terminal
        printf("--------------------------------\n");
        printf("Potentiometer: %X\n", potVal);
        printf("Light Dependant Resistor: %X\n", lightVal);
        printf("Microphone: %X\n", micVal);   

        //Wait 0.25 seconds
        wait_us(500000);
        if(lightVal<4096){
            ledDisp.setGroup(LatchedLED::LEDGROUP::GREEN);
            for (unsigned int n=0; n<8; n++) {
                ledDisp = 1 << n;
                wait_us(250000);
            }
            ledDisp = 0;
        }

        if(potVal>32768){
         ledDisp.setGroup(LatchedLED::LEDGROUP::RED);
            for (unsigned int n=0; n<8; n++) {
                ledDisp = 1 << n;
                wait_us(250000);
            }
            ledDisp = 0;
        }

        if(micVal>4095){
            ledDisp.setGroup(LatchedLED::LEDGROUP::BLUE);
            for (unsigned int n=0; n<8; n++) {
                ledDisp = 1 << n;
                wait_us(250000);
            }     
            ledDisp = 0;
        }

    }

}

