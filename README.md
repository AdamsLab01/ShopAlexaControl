# ShopAlexaControl

This is a the code and schematic(s) for my ESP8266 based Alexa control of a shop lighting and tools. It's basically (actually quite literally) just the fauxmoESP library (https://bitbucket.org/xoseperez/fauxmoesp/src/master/) with the custom names of the devices that I'm using added. There is nothing special or advancd going on.

At the time of writing this I have tested it with v3.1.0 of the FauxmoESP library on the Adafruit HUZZAH ESP8266 programed in v1.8.9 of the Arduino IDE with v2.5.0 of the esp8266 core. I'm using this with Gen2 Echo Dot.

In the Arduino IDE be sure to change the LwIP Variant setting under tool to "v2 Higher Bandwidth."

I also suggest that you use device_name rather than the device_id as I found that devices would trigger (i.e. turn on) at the same time when usign device_id.


