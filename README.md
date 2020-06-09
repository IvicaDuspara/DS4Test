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
TODO: add this 

-----------------------------------------------------------
<a name="Running"></a>
## Running
If you built this project successfully default name of executable is DS4Test
```
root@user:/home/user/# ./DS4Test 
```
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