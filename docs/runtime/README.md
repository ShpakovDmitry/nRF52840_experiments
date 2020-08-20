### Startup
Startup starts by loading four bytes from address 0x00000000 to stack pointer (SP) register and
then loading next four bytes from address 0x00000004 to program counter (PC) register which
means that first instruction that is executed after RESET is the one at this address.
So here, call to runtime routine should be called. At runtime setup we need at least copy
**.data** and **.bss** sections to RAM memory region.

### Vector table
![vector table](images/cortexM4_vector_table.png)

