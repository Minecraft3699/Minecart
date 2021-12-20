<h1> Minecart </h1>
<h2> Open Source alternative to Vex Robotics drivetrain. </h2>
<p>
  Minecart is a library that can be used in place of the built-in drivetrain functions in vexcode, Not to be confused with Mineshaft <br>
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
<p> Documentation is W.I.P, and will be more extensive.. but here is an example of how to use Minecart</p>
<br>
<br>

```
#include minecartXXX.h

minecartDriver mainDrive;
mainDrive.fourWheel = true;
mainDrive.useGyro = true;

mainDrive.rawDrive(25,50); // Inputs are in inches, I'm sorry, update soon for metric
mainDrive.rawTurn(90); // Use negative numbers to turn left


```
