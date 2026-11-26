- `gerbers/` + `lightboard-gerbers.zip`: the Light Board (Simon Says) files sent to JLCPCB (Sep 22 2026). Both hold the same 8 files.
- `led-9v-controller/`: an earlier layout, 7 LED channels on 9V with plain switches and no microcontroller. KiCad project (`.kicad_pro`) and layout (`.kicad_pcb`); there is no schematic file. A KiCad 10 design-rule check reports +9V-to-GND shorts and an unconnected second row, so it is not ready to order.

Still to add:

- KiCad project (schematic and layout) for the final Light Board. Only the gerbers exist, so the board can be re-ordered but not edited.
