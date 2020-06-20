# DS4Test
This is a C program designed for testing communication with The DUALSHOCK4® controller.

[1. Introduction](#Intro)

[2. Building](#Building)

[3. Running](Running)

---------------------------------------------------------
<a name="Intro"></a>
## Introduction
I decided that it would be fun to learn more about Linux device drivers. So I decided to 
write this program. Strictly speaking this program is not a driver. This 
is merely communication test.

This program is intended a stepping stone for future work where I plan to write
user-space driver which would allow:

* Connection via USB or Bluetooth
* Binding joystick buttons to keyboard / mouse input
* Changing light bar color
* Macro commands (pressing a button causes rumble and light bar change etc.)
* Saving configurations of joystick
--------------------------------------------------------
<a name="Building"></a>
## Building
For building system CMake is used. Here is an example
which assumes you downloaded code into your home folder

```
z@user: ~/DS4Test$ mkdir build
z@user: ~/DS4Test$ cd build
z@user: ~/DS4Test/build$ cmake ..
z@user: ~/DS4Test/build$ cmake --build .
```

You will see generated folders inside build folder. Enter in src
folder. There you will find an executable called DS4Test

-----------------------------------------------------------
<a name="Running"></a>
## Running
If you built this project successfully default name of executable is DS4Test.
Executable takes one argument - absoulte path to hidraw file in /dev/ which
represents controller. 
```
root@user:/home/user/DS4Test/build/src# ./DS4Test /dev/hidraw1
```
This implies that controller is recognizes as /dev/hidraw1.

Once DS4Test is running you can use commands.
Examples of commands:

This command changes light bar to red

```
light ff0000
```

This command rumbles heavy motor (1 weakest rumble, 255 strongest rumble)
```
hmotor 127
```

This command rumbles light motor (1 weakest rumble, 255 strongest rumble)

```
lmotor 202
```