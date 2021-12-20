/*
 __  __    _                                        _     
|  \/  |  (_)   _ _     ___    __    __ _     _ _  | |_   
| |\/| |  | |  | ' \   / -_)  / _|  / _` |   | '_| |  _|  
|_|__|_| _|_|_ |_||_|  \___|  \__|_ \__,_|  _|_|_  _\__|  
_|"""""_|"""""_|"""""_|"""""_|"""""_|"""""_|"""""_|"""""| 
"`-0-0-"`-0-0-"`-0-0-"`-0-0-"`-0-0-"`-0-0-"`-0-0-"`-0-0-' 

_____________________________________________________

v0.0.5a - The Rotation Update
---------------------------------
By: Dylan Dirkes (84443B)
---------------------------------


Minecart is an advanced, easy to use alternative to Drivetrain


Currently supports:
  > Drive for distance [No Correction]
  > 2 & 4 Wheel drive - Note: rightFront and leftFront motors are used for 2WD, configure just those.
  > Modifiable wheel diameter settings
  > Built in tank control
  > Turn To Angle [No Correction, Inertial Based]
Planned Features:
  > PID Drive [Based on Inertial Sensor]
  > PID Turn to Angle [Based on Inertial Sensor]
  > Game Object Seeker [Based on vision Sensor]
______________________________________________________

Notice: Enable expert auto complete and compile (Build) before modifying for autocomplete to work correctly

Warning: May contain minecraft references.

*/


#include "vex.h"

using namespace vex;

class minecartDriver
{
  public:
    bool fourWheel = true;
    bool useGyro = true; // Currently Ignored
    double wheelDiameter = 4.05;
    double wheelCircumfrence = wheelDiameter * 3.14159265359; // I'd make this the equation for a square or something because minecraft, but then it wouldn't work :(
   
   
   
    /*
      Default motor configuration is meant for our robot (the one with the googly eyes)

      You can change the config here or you can define it after importing minecart to your program

      Example:

      #include 'minecart.h'

      minecartDriver anything; // "anything" can be anything you want, if that is not obvious

      anything.rightFront = yourRightFrontMotor // as in yourRightFrontMotor.spin(forward);
    */


    // If you do not know how to do that, come find me I guess
    motor rightFront = motor(PORT1, ratio18_1, true);
    motor rightBack = motor(PORT10, ratio18_1, true);
    motor leftFront = motor(PORT15, ratio18_1, false);
    motor leftBack = motor(PORT20, ratio18_1, false);

    controller Controller1; // In case a controller isn't configured, this prevents the program from blowing up like a creeper.

    motor_group leftMotors = motor_group(leftFront, leftBack);
    motor_group rightMotors = motor_group(rightFront,rightBack);

    inertial gyroSensor = inertial(PORT5);
    
  // 
    void stopAll()
    {
      rightFront.stop();
      rightBack.stop();
      leftFront.stop();
      leftBack.stop();
    }

    // Raw drive, "Drive for distance" program without any corrections


    void rawDrive(double targetDist, int vel)
    {
      if(fourWheel == true){
        // Full Drive

        double targetEncoderCount = (targetDist / wheelCircumfrence) * 360;
        rightFront.setVelocity(vel, percent);
        leftFront.setVelocity(vel, percent);
        rightBack.setVelocity(vel, percent);
        leftBack.setVelocity(vel, percent);

        rightFront.spinFor(forward, targetEncoderCount,degrees, false);
        leftFront.spinFor(forward, targetEncoderCount,degrees, false);
        rightBack.spinFor(forward, targetEncoderCount,degrees,false);
        leftBack.spinFor(forward, targetEncoderCount, degrees, true);

        // End Full Drive
      
      } else {
        // Half Drive

        double targetEncoderCount = (targetDist / wheelCircumfrence) * 360;
        rightFront.setVelocity(vel, percent);
        leftFront.setVelocity(vel, percent);
        
        rightFront.spinFor(forward, targetEncoderCount,degrees, false);
        leftFront.spinFor(forward, targetEncoderCount,degrees, true);

        // End Half Drive
      }
    }


    // Gyro-based turning
    void turnDegrees(double deg, int vel, double tol = 2, double correction = 0)
    {

      if(fourWheel == true){
        // Full Drive
        rightMotors.spin(forward);
        leftMotors.spin(forward);
        while(true){
          double currentRotation = gyroSensor.rotation();
          if(currentRotation > (deg+correction)){
            rightMotors.setVelocity(vel, percent);
            leftMotors.setVelocity(vel*-1, percent);
          } else {
            rightMotors.setVelocity(vel*-1, percent);
            leftMotors.setVelocity(vel, percent);
          }

          if(currentRotation > ((deg+correction) - tol) && ((deg+correction) + tol) < currentRotation){
            rightMotors.stop();
            leftMotors.stop();
            break;
          }
        }

       // End Full Drive 
      } else {
        // Half Drive
                while(true){
          double currentRotation = gyroSensor.rotation();
          if(currentRotation > (deg+correction)){
            rightFront.setVelocity(vel, percent);
            leftFront.setVelocity(vel*-1, percent);
          } else {
            rightFront.setVelocity(vel*-1, percent);
            leftFront.setVelocity(vel, percent);
          }

          if(currentRotation > ((deg+correction) - tol) && ((deg+correction) + tol) < currentRotation){
            leftFront.stop();
            rightFront.stop();
            break;
          }
          // End Half Drive
        }
      
      }

    }



    // Very basic manual control program, Testing motor groups.
    void basicManualControl(double speedDivision){


      if(fourWheel == true){
        // Full Drive
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("[A+B] | Terminate");
        rightMotors.spin(forward);
        leftMotors.spin(forward);
        while(true){

          int rightAxis = Controller1.Axis2.position();
          int leftAxis = Controller1.Axis3.position();

          int rightAxisEquation = rightAxis/speedDivision;
          int leftAxisEquation = leftAxis/speedDivision;

          rightMotors.setVelocity(rightAxisEquation, percent);
          leftMotors.setVelocity(leftAxisEquation,percent);

          if(Controller1.ButtonA.pressing() && Controller1.ButtonB.pressing())
          {
            break;
          }
        
        }
      } else {
        // Half Drive
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("[A+B] | Terminate");
        rightFront.spin(forward);
        leftFront.spin(forward);
        while(true){

          int rightAxis = Controller1.Axis2.position();
          int leftAxis = Controller1.Axis3.position();

          int rightAxisEquation = rightAxis/speedDivision;
          int leftAxisEquation = leftAxis/speedDivision;

          rightFront.setVelocity(rightAxisEquation, percent);
          leftMotors.setVelocity(leftAxisEquation,percent);

          if(Controller1.ButtonA.pressing() && Controller1.ButtonB.pressing())
          {
            break;
          }
        
        }


      }
    }


};
