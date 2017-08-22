# RBE3001_nucleo_firmware

This is the firmware for the nucleo-f746zg

# Toolchains
```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa

sudo apt-get update

sudo apt install gcc-arm-embedded automake libusb-1.0-0-dev putty libhidapi-dev

sudo apt-get install python-pip

sudo apt-get install libtool

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


Add the plugin: `https://gnu-mcu-eclipse.github.io/downloads/`

To launch eclipse go to where you installed eclipse.

if you installed in it in the deault location run:

```
cd ~/eclipse/cpp-oxygen/eclipse

./eclipse
```

# Eclipse Setup

create a workspace for you RBE3001 devlepmet.

```
git clone https://github.com/madhephaestus/RBE3001_nucleo_firmware.git

cd RBE3001_nucleo_firmware

git checkout eclipse

git submodule init

git submodule update

mbed deploy

sudo mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ 
```
Set up a new project using "Importing to Eclipse and Building" section from: 

`https://developer.mbed.org/users/c1728p9/notebook/debugging-mbed-50-projects-with-eclipse-and-pyocd/`

Set the build command to the mbed-compile string above

![](/Screenshot_2017-08-21_12-50-00.png)

Set the build command to push the firmware with '-f'

![](/Screenshot_2017-08-21_12-43-41.png)

