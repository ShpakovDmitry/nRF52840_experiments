### NOTE
All work was done in ArchLinux. Please refer to manufacturer reference designs
how to setup tools and how to use them in different OS.

### Tools required.
* `jlink-software-and-documentation`, [download](https://www.segger.com/downloads/jlink/) from manufacturer.
* `nrf5x-command-line-tools`, [download](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools/Download) from manufacturer.

### Setup tools under ArchLinux.
Get compiler and binutils:
```bash
$ sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib
```
Tools listed in `Tools required` section could be found at AUR. To get them make the following.\
Here git repo is used to build package.
1. Before start make sure that all tools to build packages are installed.\
For this run:
```bash
$ pacman -S --needed base-devel
```
2. For `jlink-software-and-documentation`:\
Clone the git repository:
```bash
$ git clone https://aur.archlinux.org/jlink-software-and-documentation.git
```
Make and install the package:
```bash
$ makepkg -sri
```
3. For `nrf5x-command-line-tools`:\
Clone the git repository:
```bash
$ git clone https://aur.archlinux.org/nrf5x-command-line-tools.git
```
Make and install the package:
```bash
$ makepkg -sri
```
If tools are set you should be able to download firmware from nRF52840DK board to local `fw.hex` file using `nrfjprog` tool.
To do this do the following:\
Connect DK via usb to host computer. Make sure firmware is present on DK. For factory supplied DK default firmware flashes led on and off.\
Run the following:
```bash
$ nrfjprog --readcode fw.hex
```
