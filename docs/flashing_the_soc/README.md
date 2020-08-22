### Flashing the SoC
To flash Soc run the following command:
```bash
nrfjprog -f nrf52 --program build/firmware.hex --sectorerase
```
or run:
```bash
make flash
```
