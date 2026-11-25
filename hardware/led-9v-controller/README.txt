7-CHANNEL 9V LED PCB
=====================

This board is laid out from the supplied schematic as seven independent 9V LED channels.
Each channel is:
    +9V -> 370 ohm resistor -> LED -> switch -> GND

Parts to solder:
- J1: 2-pin screw terminal for 9V input
- R1-R7: 370 ohm through-hole resistors
- D1-D7: 5mm through-hole LEDs
- S1-S7: 2-pin external switches (or wire your own switches to the two pads)

LED colors on the silkscreen:
D1 RED
D2 BLUE
D3 ORANGE
D4 YELLOW
D5 GREEN
D6 WHITE
D7 RED

IMPORTANT:
The supplied schematic has the final LED/switch return (the D2/S7 section) on named nets
rather than explicitly returning to BAT1-. To make the physical board function as a normal
7-channel LED board, S7's return is connected to GND like the other six channels.

The 370 ohm resistors are retained from the supplied schematic.
Check your LED polarity before soldering: the LED anode (+ / long leg) goes toward the resistor;
the cathode (- / short leg / flat side) goes toward the switch.

Board size: 160 mm x 70 mm
Copper: 2 layer
Through-hole components

Open LED_9V_Controller.kicad_pcb in KiCad PCB Editor. Before ordering, run ERC/DRC and verify
the exact footprints and manufacturer design rules you want to use.
