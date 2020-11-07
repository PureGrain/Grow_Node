# Grow Node

>This is a simple ESP-12E NodeMCU Shield I designed for my indoor gardening project. Hence, Grow Node!

* [Use Case](#use-case)
* [Development](#development)
   * [The Setup](#the-setup)
* [Parts List](#parts-list)
* [Installation](#installation)
* [Release History](#release-history)

> ESP-12E NodeMCU Shield on STEROIDS for indoor gardening.

ehh.. Actually it's just a shield for a NodeMCU that I quickly designed (my first Fritzing to PCB Design) to use for a bunch of soil moisture sensors to keep track of multiple plants in my home using [Blynk Dedicated Server](https://github.com/blynkkk/blynk-server) in a [Docker](https://www.docker.com/products/docker-desktop) container running on my Desktop. [Get the container here](https://github.com/mpherg/blynk-server) In the process I also track the temperature and relative humidity using a DHT22 sensor. All parts are obtainable from Amazon and I will be sharing those links as I get time to put this read me together. There is access to all of the pins on the NodeMCU to add additional sensors for those who want to hack away and build something custom.

OTA.. YAY!! I also wanted to be able to update the nodes without having to unplug and bring them into the house each time. So, I decided to add in the OTA code using some existing libraries and code I found using Google, which will be tagged/linked later in the [Installation](#installation) section.

![](/images/v1.0.png) 
![](/images/app_demo.png)

## Use Case:

**House Plants, Gardens, Potted Plants, Lawn, Landscape, Sump Pump Detection and many more ideas and uses for the Grow Node.

* House Plants that you forget to water, always dead or dying? - Not with Grow Node!
* Monitor the ground moisture around your home and get notified when you need to water your landscaping and lawn.
* Do you have a pesky sump pump that sometimes likes to stop working at 4am during a bad rainstorm? You can be notifed a lot sooner with this device!!
* Get notifications on your smart phone using the Blynk app. Free!!


The Grow Node can be used in all kinds of gardening projects. While I set this one up for indoor growing. It can easily be used in thousands of other projects as it gives quick access to the pins via screw terminals and male/female headers. You simply pop in a NodeMCU, attach your sensors, program the board via your favorite IDE. (In my case I use the Arduion IDE) And that's it. Your plants will live to see another day and you'll be much happier knowing you can rely on the Grow Node to keep them healthy.

## Development:

* You'll need [Arudion IDE](https://www.arduino.cc/en/software) or your favorite IDE you use to deploy your code to microcontrollers. If you're new to this, just go grab the [Arduino IDE](https://www.arduino.cc/en/software). It's the simplest.

### The Setup
So, how does this thing actually work? 

> I'll do my best to explain and then move on to putting together the files you'll need and quit messing with this read me.

Buy/Obtain the parts, build the prototype, setup the Blynk Server, Download the Blynk app for your phone, connect and get it Blynk working, edit/upload the provided sktech and watch the magic happen.

## Parts List:

Part Name | Affiliate Link =)
------------ | -------------
ESP-12E NodeMCU | Coming Soon
Capacitive Soil Moisture Sensor | Coming Soon
More... | Coming Soon...

## Installation

Coming soon.

## Release History

* 1.0.0
    * The first prototype breadboards have been in the field now for two weeks and working perfect. (pics coming)
    * I have the Dedicated Blynk Server and App dialed in working great. It is smooth and very easy to use once you see how it works. I'll be moving this to a dedicated virtual server on Digital Ocean for demo purposes and video tutorials I'm putting together. More to come.
    
*ToDo: Add mounting holes... ;) 

## Contributions

https://www.digitalocean.com/community/tutorials/how-to-set-up-a-private-docker-registry-on-ubuntu-18-04


