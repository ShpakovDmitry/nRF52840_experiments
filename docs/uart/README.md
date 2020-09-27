### UART

nRF52840 has 2x UART on chip including one with DMA support. At the moment only
UART **without** DMA will be used. UART module implements the following:
* full-duplex operation
* automatic flow control
* parity checking and generation for 9th data bit
* up to 1Mega baud rate

###### Pin configuration
The different signals `RXD`, `CTS`(Clear To Send, active low), `RTC`(Request
To Send,active low), and `TXD` associated with the UART are mapped to physical
pins according to the configuration specified in the `PSEL.RXD`, `PSEL.CTS`,
`PSEL.RTS` and `PSEL.TXD` registers respectively.

If the `CONNECT` field of a `PSEL.xxx` register is set to `Disconnected`, the
associated UART signal will not be connected to any physical pin. The
`PSEL.RXD`,`PSEL.CTS`, `PSEL.RTS` and `PSEL.TXD` registers and their
configurations are only used as long as the UART is enabled, and retained only
for the duration the device is in `ON` mode. `PSEL.RXD`, `PSEL.CTS`,
`PSEL.RTS` and `PSEL.TXD` must only be configured when the UART is disabled.

| UART pin | Direction | Output value   |
|:-------- |:--------- |:-------------- |
| RXD      | Input     | Not applicable |
| CTS      | Input     | Not applicable
| RTS      | Output    | 1              |
| TXD      | Output    | 1              |

> TODO complete description
