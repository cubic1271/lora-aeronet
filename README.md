# AeroNet / LoRa

## Introduction

This project is a collection of various items / documentation.  The intent is
to build a communications system for a model remote-control aircraft based on
LoRa packet radio, with the intent of minimizing transmit power (allowing for
good range with a relatively low SWaP).  A similar system could, for example,
be placed into a high-altitude balloon or the like.

The project is based on a little Heltec ESP32 / OLED / LoRa board with almost
no documentation at all.  The part does have some reasonable example code that
seems to work pretty well, though.

In this case, we're avoiding LoRaWAN and just trying to re-invent a MAC because
it seems like a fun thing to do.

## Notes

This is a section that discusses notes / other considerations.  As someone who
had never used LoRa, the intent is to document stuff here as I figure it out.

This is also intended to document development / trade-offs involved with
putting together a MAC.
