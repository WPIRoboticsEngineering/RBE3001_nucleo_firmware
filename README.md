# RBE3001_nucleo_firmware

This is the firmware for the nucleo-f746zg

# Driver and udev rule
The nucleo needs a udev rule installed in

/etc/udev/rules.d/98-openocd-udev.rules

```
wget https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/98-openocd-udev.rules
sudo cp 98-openocd-udev.rules /etc/udev/rules.d/
sudo  udevadm control --reload-rules
sudo adduser $USER dialout 
```
Udev for nucleo source
https://github.com/platformio/platformio-core/blob/develop/scripts/98-openocd-udev.rules

# Toolchains
```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt install gcc-arm-embedded automake libusb-1.0-0-dev putty libhidapi-dev python-pip libtool git oracle-java8-set-default oracle-java8-installer
sudo pip install mbed-cli
git clone http://repo.or.cz/r/openocd.git
cd openocd
./bootstrap
./configure --enable-stlink --enable-ftdi --enable-cmsis-dap --prefix=/usr/local
make -j8
sudo make install

```
Log out and log back in to make the user permissions stick.

# Firmware Source Code

Download and compile the source code with mbed-cli
## Configure git
```
git config --global user.name "John Doe"
git config --global user.email johndoe@wpi.edu
```
## Clone Firmware
First create a new private repository and hold on to that git url.
```
git clone https://github.com/WPIRoboticsEngineering/RBE3001_nucleo_firmware.git
cd RBE3001_nucleo_firmware
```
## Set up your private repo
```
#Set your fresh clean Private repo here
git remote set-url origin git@github.com:MY_3001_PROJECT_GROUP/MY_PRIVATE_REPO.git
git checkout master
#this pushes the master baranch to your private repo
git push origin master
```
## Initialize and Compile Firmware
```
git submodule init
git submodule update
mbed deploy
mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ -f
```
If everything worked your terminal should look like: 

![](/terminal.png)
# Print statements

Use Putty to open the serial port

`/dev/ttyACM0 at 9600`


# Install Eclipse (CDT)
[Direct Download Link for Eclipse](https://www.eclipse.org/downloads/download.php?file=/oomph/epp/oxygen/R/eclipse-inst-linux64.tar.gz)

Extract and run the installer. Select C/C++ version of eclipse and install it in the default location. 

`eclipse-inst`

![](/eclipse.png)

To launch eclipse, go to where you installed eclipse

if you installed in it in the deault location run:

```
cd ~/eclipse/cpp-oxygen/eclipse
./eclipse
```
Optionally you can make an eclipse launcher
```
mkdir -p ~/bin/
echo "[Desktop Entry]
Version=1.0
Type=Application
Name=Eclipse Arm Toolchain
Comment=
Exec=/home/$USER/eclipse/cpp-oxygen/eclipse/eclipse
Icon=/home/$USER/eclipse/cpp-oxygen/eclipse/icon.xpm
Path=
Terminal=false
StartupNotify=false" > ~/bin/EclipseARM.desktop
chmod +x ~/bin/EclipseARM.desktop
ln -s ~/bin/Eclipse.desktop ~/Desktop/EclipseARM.desktop
```

# Eclipse Setup

create a workspace for you RBE3001 devlepmet. First add the GNU ARM toolchain

Name: GNU ARM Eclipse Plug-ins

Location: `http://gnu-mcu-eclipse.netlify.com/v4-neon-updates`

Install plugins from that site. 

Restart Eclipse after installing plugins.

Next Set up the toolchain path for MCU's

Window->Preferences->MCU->Global ARM Toolchain Paths->Toolchain folder:

`/usr/arm-none-eabi/bin/`

Apply and Close

Set up a new project using "Importing to Eclipse and Building" section from: 

Right click in Project Explorer:
Import... ->C/C++ -> Existing Code as Makefile Project

Browse in Existing Code Location for your RBE3001_Nucleo_firmware (This should set the project name as well

Select ARM Cross GCC

Finish

Then set the build command by right clicking on RBE3001_Nucleo_firmware

Properties->C/C++ Buld->Builder Settings->Build Command:

`mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/`

![](/Screenshot_2017-08-21_12-50-00.png)


Set the build command to push the firmware with '-f'

Properties->C/C++ Buld->Behavior Build(Incremental Build)

![](/Screenshot_2017-08-21_12-43-41.png)

right click on RBE3001_Nucleo_firmware 

Properties->C/C++ Buld ->Settings->Toolchains->Toolchain path

and make sure it says:

`/usr/arm-none-eabi/bin/`

right click on RBE3001_Nucleo_firmware

Index-> Rebuild

Wait for the C/C++ indexer to complete and then you can begin working.

