`simon_says/simon_says.ino`: the game. Flash it to the Nano (Tools → Processor → ATmega328P, or "Old Bootloader" on clone boards).

- Power switch on A4: closed = on. If yours runs backwards, flip `on()`.
- Each LED has its own tone. The sequence grows by one every round and speeds up.
- Miss or wait 3 s and everything flashes, then it blinks out your score.
