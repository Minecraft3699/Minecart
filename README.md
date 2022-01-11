<h1> Minecart </h1>
<h2> Open Source alternative to Vex Robotics drivetrain. </h2>
<p>
  Minecart is a library that can be used in place of the built-in drivetrain functions in vexcode, Not to be confused with Mineshaft <br>
  <br>
  Minecart is very early in development, the library will become far more useful in the future.
  <br>
  Currently, Minecart supports:<br>
<ul>
  <li> 2 And 4 Wheel Drive </li>
  <li> Inertial Based Turning </li>
  <li> Variable Wheel Diameter </li>
  <li> Accurate Forward / Backward Movement </li>
</ul>
<br>
<p> Planned Features: <br> </p>
<ul>
  <li> PID Turning, Inertial Based </li>
  <li> Raw Turning, Without sensors </li>
  <li> PID Driving for even more precise movement </li>
  <li> Printing useful data on the controller
  <li> Goto coordinates, GPS based </li> 
  <li> And More... </li>
</ul>
<br>
<br>
<h1> How to use Minecart </h1>
<br>
<h2> Including the library </h2>
<br>
<p> The first step is importing the library...<br>
  <br>
  Simply put the "#include minecartXXX.h" line below where the vex.h file is included as seen in the example below <br>
  In case it is not obvious, replace the XXX with the version number (e.g. #include "minecart005a.h")
 <br>
Note: you can replace the name mainDrive with whatever you want.   
<br>

```
#include "vex.h"  
#include "minecartXXX.h"

minecartDriver mainDrive;

int main()
{
  mainDrive.rawDrive(10,50)
}

```
<br>
<br>
<h2> Motor & Wheel Configuration </h2>
<br>
<p> First, for the math to be accurate you must input the correct wheel diameter </p>
<br>

```
int main() {
  mainDrive.wheelDiameter = 4.05
}
```

<br>
<p> Minecart supports 2 and 4 wheel drive robots, so next set the fourWheel variable to true or false. </p>


```
int main() {
  mainDrive.wheelDiameter = 4.05
  mainDrive.fourWheel = true
}
```

<br>
<br>
<p> Now, you need to add your motors to minecart.. add your motors with the regular device config panel on the right side of vexcode and then add them to minecart like so <br>

```
int main() {
  mainDrive.wheelDiameter = 4.05
  mainDrive.fourWheel = true 
  
  // Use the names you set for your motors in the device config.
  mainDrive.rightFront = yourRightFrontMotor
  mainDrive.leftFront = yourLeftFrontMotor
  // If you are using 2wD, set both drive motors to rightFront and leftFront.
  mainDrive.rightBack = yourRightBackMotor
  mainDrive.leftBack = yourLeftBackMotor
}
```

  
<br>
<br>
<h2> rawDrive() </h2>
<br>
<p> the rawDrive function takes 2 parameters, distance in inches and velocity in percent. Sorry about the imperial measurements.. configuration options coming soon.
<br>  
 
```
  mainDrive.rawDrive(10,50) // Forward 10 inches at 50% speed.
```
