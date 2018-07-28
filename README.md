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

### Example code notes

The very first thing I tried involved taking the example transmit code and
combining it with the example receive code, without really looking at any of the
LoRa class code.  My naive approach was to call transmit once, then to call
parsePacket once, then go back to the start of the loop.  This didn't work.

It looks like the reason this didn't work is because the parsePacket method, in
this case, actually puts the radio into a packet receive mode if the radio isn't
in that mode already ... but then immediately returns from the function.  Thus,
it seems like parsePacket (as written) needs to be called twice in cases where
we desire to transmit a packet, then immediately fall back into a receive mode.
