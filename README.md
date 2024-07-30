# DigitalFunctionGenerator
A digitally-controlled function generator

# Outline
Sometimes, electronic tools can be expensive or hard to come by (seriously, the cheapest one I could find was still over $100!). That's exactly why I wanted to build a function generator. By designing the function generator such that it is digitally controlled, I can incorporate an Arduino Uno R3 as well. This seemed like a great project to build, since it would improve my digital/embedded systems skills, as well as leaving me with a useful tool that I can use for future electronics projects!

For this function generator, I want it to be capable of outputting square, triangle, sine, and sawtooth waveforms. Additionally, being able to manually control the frequency and amplitude would be great additions. Lastly, I want to add an LCD screen so the user knows what the output currently is.

It would also be good to get some woodworking skills in and make a nice wooden box for this function generator.

# The hardware
As previously mentioned, I'll be using an Arduino Uno R3 as the microcontroller for this project. With lots of digital I/O and a good CPU clock speed (16 MHz), it's a good start to this project. 
In addition, I'll be using a MCP4822 IC, which is a 12-bit DAC with a dual voltage output. The dual voltage output is not really needed (only one output is necessary), but it's what I had on hand. But another great thing about this project is that the MCP4822 is able to be controlled via SPI, which the Arduino is capable of.
Lastly, I'll be using a LCD1602 display. Again, I would've preferred to use a larger display, but this is what I had on hand and with a bit of creativity, we can get it to work.

# The code
We'll need to write a few lines of code to be able to control the DAC through code. For the sine and triangle waveforms, I'll be pre-computing them and storing the values as an array which will help with processing speeds. The square and sawtooth waves won't be pre-computed, since they can be generated pretty easily by the microcontroller itself.

The rest of the code will be written in the Arduino IDE and will consist of some code to control the LCD screen and send the data to the DAC through SPI. I'll be using the LiquidCrystal and SPI libraries.

# Future work
There are definitely some improvements that I want to make. Mainly, I want to get rid of the Arduino and work directly with the AVR. Basically, I want to pull the ATMEGA32p off of the Arduino Uno and code it directly. This will get rid of the huge amounts of abstraction going on when working with Arduino.

Some other miscellaneous changes would be to add a bigger LCD screen, adding some more functions (reverse sawtooth, etc.), and being able to change things like the duty cycle.


This idea was heavily inspired by the amazing Sine Labs YouTube channel. Check it out if you haven't already, it's absolutely amazing! 
