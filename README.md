# ShopAlexaControl

This is a the code and schematic(s) for my ESP8266 based Alexa control of a shop lighting and tools. It's basically (actually quite literally) just the fauxmoESP library (https://bitbucket.org/xoseperez/fauxmoesp/src/master/) with the custom names of the devices that I'm using added. There is nothing special or advanced going on.

At the time of writing this, I have tested it with v3.1.0 of the FauxmoESP library on the Adafruit HUZZAH ESP8266 programed in v1.8.9 of the Arduino IDE with v2.5.0 of the esp8266 core. I'm using this with a Gen2 Echo Dot.

In the Arduino IDE be sure to change the LwIP Variant setting under tool to "v2 Higher Bandwidth."

I also suggest that you use device_name rather than the device_id as I found that devices would trigger (i.e. turn on) at the same time when using device_id.

I'm currently controlling my shop lights, and compressor with this setup. The included schematic just shows the relay board for the lights, however. The compressor (and the compressor emptying valve) are controlled from the ESP8266 directly by solid state relays, the only thing that is is used for those is a current limiting resistor to the relays. There is also a MOV in place for protection. I do have toggle switches in place for the compressor and emptying valve to allow me to bypass the ESP8266 and turn on the relays directly, or disable them entirely.

For the lights I used a SPDT relay so that I could wire the lights in conjunction with a standard wall switch and have it act as a three way switch. While it's possible with the fauxmoESP library to convey a device state change that occurs outside of Alexa (i.e. if the device was turned on or off with a manual switch) I did not do that in the case of the lights (or compressor) for simplicity. Also, the purpose of the manual switch is for emergencies as it completely bypasses Alexa/the ESP8266.

Note, the compressor emptying valve is normally close and only open when it's turned on, it uses a capacitor to close the valve when power is removed. To close completely the valve needs to be on for a minimum of 3 minutes. I could have accomplished this is the ESB8266 but decided to use an Alexa routine to keep things simple. When I tell Alexa to "turn the compressor off" the Alexa routine turns the compressor off, turns the emptying valve on to open it, and then waits 3 minutes before it turns the emptying valve off.  

I cover this setup in this video:
