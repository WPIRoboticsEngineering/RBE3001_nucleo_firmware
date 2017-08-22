# RBE3001_nucleo_firmware

This is the firmware for the nucleo-f746zg

# Driver and udev rule
The nucleo needs a udev rule installed in

/etc/udev/rules.d/98-openocd-udev.rules

```
wget https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/98-openocd-udev.rules
sudo cp 98-openocd-udev.rules /etc/udev/rules.d/
sudo  udevadm control --reload-rules
```
Udev for nucleo source
https://github.com/platformio/platformio-core/blob/develop/scripts/98-openocd-udev.rules

# Toolchains
```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa

sudo apt-get update

sudo apt install gcc-arm-embedded automake libusb-1.0-0-dev putty libhidapi-dev python-pip libtool 

sudo pip install mbed-cli

cd mkdir git && cd ~/git/

git clone http://repo.or.cz/r/openocd.git

cd openocd

./bootstrap

./configure --enable-stlink --enable-ftdi --enable-cmsis-dap --prefix=/usr/local

make -j8

sudo make install
```
If everything worked your terminal should look like: 

![](/terminal.png)

# Install Eclipse (CDT)

`https://www.eclipse.org/downloads/download.php?file=/oomph/epp/oxygen/R/eclipse-inst-linux64.tar.gz`

![](/eclipse.png)

To launch eclipse go to where you installed eclipse.

if you installed in it in the deault location run:

```
cd ~/eclipse/cpp-oxygen/eclipse

./eclipse
```

# Eclipse Setup

create a workspace for you RBE3001 devlepmet. First add the GNU ARM toolchain

Name: GNU ARM Eclipse Plug-ins

Location: `http://gnu-mcu-eclipse.netlify.com/v4-neon-updates`

```
git clone https://github.com/madhephaestus/RBE3001_nucleo_firmware.git

cd RBE3001_nucleo_firmware

git checkout eclipse

git submodule init

git submodule update

mbed deploy

mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ 
```
Set up a new project using "Importing to Eclipse and Building" section from: 

Right click in Project Explorer:
Import... ->C/C++ -> Existing Code as Makefile Project

Browse in Existing Code Location for your RBE3001_Nucleo_firmware (THis should set the project name as well

Select ARM Cross GCC

Finish

Then set the build command by right clicking on RBE3001_Nucleo_firmware

Properties->C/C++ Buld->Builder Settings->Build Command:

`mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ `

![](/Screenshot_2017-08-21_12-50-00.png)


Set the build command to push the firmware with '-f'

Properties->C/C++ Buld->Behavior Build(Incremental Build)

![](/Screenshot_2017-08-21_12-43-41.png)


right click on RBE3001_Nucleo_firmware

Properties->C/C++ Buld ->Settings->Toolchains->Toolchain path:

`/usr/arm-none-eabi/bin/`

right click on RBE3001_Nucleo_firmware

Index-> Rebuild

