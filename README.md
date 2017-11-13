# IoT-DatabaseLogger
Main IoT Module code that communicates the power consumption values to a Firebase database for our Web App to read and update the user interface with

## Making the ESP2866 board work
This was a large challenge. I used a [development board variant](https://www.amazon.com/dp/B01N8UUE3L/ref=cm_sw_r_fm_apip_KY213ViIeBONJ) that featured an ESP2866 that was unusually tough to work with, but I figured it out in the end. I would not recommend using this board in the end, but that's up to you. Make sure your board has adequate community support and documentation available!

I used the Arduino IDE version 1.8.5. I used the following upload options:


Option  | Value
------- | -----
Board | NodeMCU 1.0 (ESP-12E Module)
CPU Frequency | 80 MHz
Flash Size | 4M (3M SPIFFS)
Upload Speed | 115200 baud
Programmer | AVRISP mkII

Also the BaudRade of the Serial.begin was 19200 baud. Any other value for it made the board output trash to the serial monitor

## Uesful links
The [firebase-arduino](https://github.com/firebase/firebase-arduino) library was the *most crucial* component to the success of the project. Check out the guide there to get your board setup

## Troubleshooting
If the serial monitor still outputs trash, make sure all the I/O used isn't necessary for the UART. I think doing `pinMode(5, OUTPUT)` made the entire code not work at all so beware of pin 5
