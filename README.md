# Captain Quack!
ESP8266 Wifi Controlled Captive Portal Remote Controlled Duck on a Tank.

I needed a reason to prove out ESP8266 Captive portal technology, and I wanted to see if I could make some crappy motor drivers, so this monstrocity was born!

< PHOTO OF CAPTAIN QUACK >

## Video walkthrough of the technical stuff
[![Cambot Video](https://img.youtube.com/vi/nbJNLVBo_g4/0.jpg)](https://www.youtube.com/watch?v=nbJNLVBo_g4)

## Video walkthrough of the artsy stuff
[![Cambot Video](https://img.youtube.com/vi/nbJNLVBo_g4/0.jpg)](https://www.youtube.com/watch?v=nbJNLVBo_g4)

## Software
The arduino code is very simple for this, the only real interesting bits are getting the Captive Portal to work on different devices.

The basic premise is simple, when a device connects to the access point, always return the access point's ip address for dns requests, and always 302 redirect all unkown filts / api endpoint requests to the homepage. 

Unfortunatley the DNSServer library had to be patched ( I can't take any credit for this. ) Different operating systems can be very picky about how the requests headers and responses in general are formed, so alot of fiddling went into getting that right, and the most aggravating discovery was that Android OS won't show the captive portal if the dns ip is in the 'local range', so you have to go out of your way to choose a specific kind of ip address for your webserver.

Using the ESP SPIFFs file system takes alittle getting used to as well, but it's MUCH nicer serving actual files for your website, over having to compact and embed them into arduino sketch files.

## Hardware
1. [ESP01 Microcontroller and Programmer](https://www.amazon.com/IZOKEE-Wireless-Transceiver-Mega2560-Raspberry/dp/B07D49MSTM/ref=sr_1_2?keywords=esp01+and+programmer&qid=1557848392&s=gateway&sr=8-2
)
2. [2x motors](https://www.amazon.com/gp/product/B07JMBCH1X/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)

3. 2x 2N3904 Transistors

4. 2x Blue LEDs for testing without the motors

5. 2x 2.6k Resistors for the ESP01 pullups

6. 2x 102 (1nf) Ceramic Capacitors for motor decoupling 

7. 1x 220uf Capacitor for power spikes

8. 2x 3.3k resistors for the GPIO output to transistors

9. 2x 1N4148 Diodes

10. [3.7v 720 mah lipo battery + charger](https://www.amazon.com/dp/B0748CKDCM/ref=sspa_dk_detail_0?psc=1&pd_rd_i=B0748CKDCM&pd_rd_w=dnhdy&pf_rd_p=8a8f3917-7900-4ce8-ad90-adf0d53c0985&pd_rd_wg=zHyX3&pf_rd_r=W2KZ3D4AW8NJD901AMTP&pd_rd_r=72ce8b38-765f-11e9-a563-4fe76fa75f96&smid=A2M0WCZTZC71VA)

11. Misc lego peices, building the vehicle is best left up to you

12. [A nice duck as your captain](https://www.amazon.com/gp/product/B00YMRZFE8/ref=ppx_yo_dt_b_asin_image_o00_s00?ie=UTF8&psc=1)


Crappy Circuit Schematic:
< PHOTO OF CIRCUIT SCHEMATIC HERE >

## Some things to consider, and improve upon

My circuit could be improved in alot of ways, we could pull more current from the esp01 so the transistor allows more current through it, which would speed up the motors a bit. 

I could have made the led lights removeable so they aren't pulling current when I'm not testing things. 

Using the rx / tx pins on the ESP01, and modifying the circuit to support bidirection motor movement would have been cool as well.

## Additional resources to learn more ##
[Info about the motor driver circuit I based mine off, and how it works](https://electronics.stackexchange.com/questions/95140/purpose-of-the-diode-and-capacitor-in-this-motor-circuit)

[Info about decoupling caps](https://www.esp8266.com/viewtopic.php?f=13&t=8479)

[Info about capacitors added to motors](https://robotics.stackexchange.com/questions/267/why-are-capacitors-added-to-motors-in-parallel-what-is-their-purpose)

[Info about flyback diodes](https://electronics.stackexchange.com/questions/271182/what-is-the-purpose-of-a-flyback-diode?rq=1)

[Info about using the ESP01 in general](https://www.instructables.com/id/How-to-use-the-ESP8266-01-pins/)

[Info about what Captive Portals are](https://en.wikipedia.org/wiki/Captive_portal)

[Info about using ESP8266 SPIFFs to store files](https://www.instructables.com/id/Using-ESP8266-SPIFFS/)

# Good luck and have fun! 
## Please feel free to fork or contribute! 
## Also please submit issues if you have any problems or questions and I'll do my best to help get things worked out!