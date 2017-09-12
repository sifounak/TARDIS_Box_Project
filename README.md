# TARDIS BoProject

[![Sound-Activated TARDIS Video](https://img.youtube.com/vi/mShBE_wHAk8/0.jpg)](https://www.youtube.com/watch?v=mShBE_wHAk8)

This repository contains:
* an Arduino sketch used to trigger pulsing lights within a TARDIS model using a finger snap or a clap
* the audio clip that the LEDs are synced to

More information about this project can be found at:
https://hackaday.io/project/26964


## What does the sketch do?

At a high level, the sketch:
1. Sets the pins and a bunch of constants
2. Initializes the state of the LEDs and sound trigger
3. Continuously checks the microphone for a sound level that is higher than a set threshold
4. When the sound threshold is met or surpassed
   1. The audio board is triggered and the TARDIS landing noise is played
   2. The lights are pulsed according the to the pattern laid out in the arrays at the top of the sketch
   3. The code pauses for a second
5. Returns to step 3.

The code is pretty heavily commented, so it should be pretty easy to navigate.

**NOTE:** The sketch is designed specifically for the Pro Trinket 5V, so it might require some pin changes to work with other hardware.


## Author(s)
* **Adam Sifounakis**


## Usage

You are free to use this code however you'd like, but I request that you please include the following attribution:

> Original code by Adam Sifounakis
> Github:  https://github.com/sifounak/TARDIS_Box_Project
> Details: https://hackaday.io/project/26964

