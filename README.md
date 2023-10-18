# pic18_dietemp
Testing the die temperature sensor on a PIC18F46K42

The PIC18FxxK42 series PICs have an inbuilt temperature sensor. The datasheet does not describe the sensor in detail 
but elsewhere it is described as three series-connected diodes and a current source, with an option to bypass one diode.

The device has some built in calibration data and there is some data in the datasheet. In past experiments using the
published formulae room temperature has been reported as 32-33 Centigrade when the actual temperature was nearer 21C.

This has yet to be adequately explained, the problem could be
intrinsic to the sensor
a problem with the formula
a bug in my implementation of the formula
self-heating of the PIC die
or some other unknown issue.

