# Power over Ethernet (PoE)

This document is dedicated to recording the relevant information for PoE that needs to be used by the WashU robotics club Rover Electrical Team. Refer to the sections below to learn about how PoE is used on the Rover.

### Sections
* [Why PoE](#why-poe)
* [PoE Standard](#what-poe-standard-is-being-used)


## Why PoE?

There is one main reason why we chose to include PoE on the rover: a large portion of networking equipment can be powered using PoE. This allows us to run a single cable to each networking-enabled device, rather than a power cable and ethernet cable. This reduces clutter in our device.

## What PoE standard is being used?

We are currently using a custom PoE setup because Ubiquiti field networking equipment uses 24V PoE. We are looking into switching to a IEEE 802.11af standard to allow us greater flexibility with other networking equipment. The Ubiquiti 24V power uses pairs 4,5 for positive and 7,8 for ground. A diagram of a standard ethernet connection is show below:

![Standard RJ45 ethernet jack](./ethernet.jpg)

RJ45 is the standard for the jack size, and T-568B is for the way the wires are organized. In our case, the positive pairs are Blue, Blue/White, and the negative pairs are Brown/White, Brown.