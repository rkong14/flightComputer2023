# flightComputer2023

Hello! This has all the code we used for making the flight computer. Some files have commented explanations, however I cannot guarantee it all makes sense, my sincerest apologies. Should the future generations have any questions, Autumn Rogers helped make some of this, or you are free to harras me (Ray Kong). The code itself is fairly simple if you're familiar with weakly typed languages (but Arduino is based in C++). Below I included a breif description of each file I uploaded.

<b>circuit testing</b>
uses hardcoded data to simulate apogee, we used this to test if ignition circuit would go off and if the conditional we used would correctly sense when it hit apogee

<b>master serial</b>
gets data from the accelerometer and altimeter, prints them to the serial monitor

<b>master sd</b>
gets and saves data from altimere and accelerometer to the sd card, the file we used to launch so it also has the conditional for apogee and some more formatting things on the sd file

<b>master sd to accel</b>
same as sd but without accelerometer code, meant to be used on the 3in computer where the accelerometer gave out on us

Also uploaded is the txt file from our launch so you can see what the master sd code outputted and the pinouts for the arduino uno and mega for reference (depending on what you're working with, these may or may not be relevant).
