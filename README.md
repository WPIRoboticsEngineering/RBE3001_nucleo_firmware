# RBE3001_nucleo_firmware

This is the firmware for the nucleo-f746zg

# Toolchains

sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update
sudo apt install gcc-arm-embedded automake libusb-1.0-0-dev putty libhidapi-dev

pip install mbed-cli

cd ~/git/

git clone http://repo.or.cz/r/openocd.git
cd openocd
./bootstrap
./configure --enable-stlink --enable-ftdi --enable-cmsis-dap --prefix=/usr/local
make -j8
sudo make install


# Eclipse Setup

Add the plugin:

https://gnu-mcu-eclipse.github.io/downloads/

git clone https://github.com/madhephaestus/RBE3001_nucleo_firmware.git

cd RBE3001_nucleo_firmware

git checkout eclipse

git submodule init
git submodule update

mbed deploy

mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ 
