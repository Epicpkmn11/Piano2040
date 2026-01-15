# Schematic for binary release

## Overview

```text
                               ------- USB-C --------
                No connection -|5V                 0|- C
                No connection -|GND    RP2040      1|- C# / Db
                No connection -|3V3     Zero       2|- D
                No connection -|29                 3|- D# / Eb
                No connection -|28                 4|- E
                No connection -|27                 5|- F
                   3rd octave -|26                 6|- F# / Gb
                   2nd octave -|15                 7|- G
                   1st octave -|14 13 12 11 10  9  8|- G# / Ab
                               ----------------------
                     No connection -/  |  |  |  \- A
           2nd C (final octave only) -/   |   \- A# / Bb
                                           \- B
```
## Scanning matrix
The RP2040 only has enough GPIOs to support two octaves without
using a matrix. I wanted three octaves, so a key matrix is used.

Each octave is pulled high sequentially from left to right,
output from the octave pins to the key pins, so make sure your
diodes are oriented towards the key pins.

The RP2040 seems to take about 3ms to react to a change on
the GPIOs. This adds up for each octave, so the rate of a
full scan will decrease the larger the keyboard.

### Wiring
This is the wiring diagram for 3 octaves, it can be expanded with
'ease' up to seven octaves at which point you run out of easily
accessible GPIO pins on the RP2040-Zero (there are more in the
form of pads on the bottom).

Pins 2 through 11 are omitted for simplicity, but those keys
are wired exactly the same as 0 and 12.

I believe the diode on pin 13 is optional since there is only one.

```text
|     14      |   |     15      |   |        26           |
---------------   ---------------   -----------------------
       |                 |                    |
       +-----------------|--------------------|--------------+
                         +--------------------|--------------|-+
                                              +--------------|-|-+
                                                             | | |
| 0 | .. | 12 |   | 0 | .. | 12 |   | 0 | .. | 12 | | 13 |   | | |
-----    ------   -----    ------   -----    ------ ------   | | |
  |         |       |         |       |         |      |     | | |
  V         V       V         V       V         V      |     | | |
  +---------|-------+---------|-------+         |      |     | | |
  |         +-----------------+-----------------+      |     | | |
  |         |   +--------------------------------------+     | | |
  |         |   |   ------------                             | | |
  +---------|---|---|0   RP  14|-----------------------------+ | |
            +---|---|12 2040 15|-------------------------------+ |
                +---|13      26|---------------------------------+
                    ------------
```
