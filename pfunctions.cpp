#include "vex.h"
#include "pfunctions.h"
#include "robotconfig.h"
#include "tracking.h"



using namespace vex;

float distanceError;
float rotationError;
float rotationsToTarget;
float inertialRotation = BrainInertial.rotation(degrees);
float kp = 0.3;
float LMpos;
float RMpos;
float pos;

float output;
float LM_velocity;
float RM_velocity;
float LMfp2;
float RMfp2;
float LMsp2;
float RMsp2;
float kp2 = 0.3;

float rotError;
float power;



int LoggingP(){
  
  while(true){
  
  
  //Brain.Screen.printAt(10, 20, "pos %.2f", pos);
  //Brain.Screen.printAt(10, 40, "rtt %.2f", rotationsToTarget);
  Brain.Screen.printAt(10, 20, "rot %.2f", BrainInertial.rotation(degrees));
  Brain.Screen.printAt(10, 40, "output %.2f", output);
  Brain.Screen.printAt(10, 60, "LMV %.2f", LM_velocity);
  Brain.Screen.printAt(10, 80, "RMV %.2f", RM_velocity);
  wait(40, msec);
  }


return 0;

}

void driveStraight(int target, float head, int velo){
  
  
  //LM.setPosition(0, degrees);
  //LM.setPosition(0, degrees);
  LMfp2 = LM.position(degrees);
  RMfp2 = RM.position(degrees);

  LMpos = 0;
  RMpos = 0;
  pos = (LMpos + RMpos)/2;

  rotationsToTarget = ((target/(2*pi*radius)) * 360) * (velo/ abs(velo));
  LM.setVelocity(velo, percent);
  RM.setVelocity(velo, percent);
  
  if (velo > 0){
  while (pos < rotationsToTarget){
     
     LMsp2 = LM.position(degrees);
     RMsp2 = RM.position(degrees);

     LMpos = LMsp2 - LMfp2;
     RMpos = RMsp2 - RMfp2;
 

     pos = (LMpos + RMpos)/2;
     rotationError = head - BrainInertial.rotation(degrees); //IMPORTANT!! INERTIALROTATION DOES NOT RETURN UPDATED ROTATION
     output = rotationError*kp;
     LM.setVelocity(velo + output, percent);
     RM.setVelocity(velo - output, percent);
     LM_velocity = velo + output;
     RM_velocity = velo - output;
     
     LM.spin(forward);
     RM.spin(forward);
     wait(20, msec);


  }

  }

  if (velo < 0){
   while (pos > rotationsToTarget){
     
     LMsp2 = LM.position(degrees);
     RMsp2 = RM.position(degrees);

     LMpos = LMsp2 - LMfp2;
     RMpos = RMsp2 - RMfp2;
     
     pos = (LMpos + RMpos)/2;
     rotationError = head - inertialRotation;
     
     output = rotationError*kp;
    
     LM.setVelocity(velo + output, percent);
     RM.setVelocity(velo - output, percent);
     LM.spin(forward);
     RM.spin(forward);
     wait(20, msec);


  }



  }
LM.stop();
RM.stop();
Brain.Screen.printAt(20, 100, "Done");
}

void turnTo(float targetRotation, int velo2){

    
    if (targetRotation < BrainInertial.rotation(degrees)){
       
       while (targetRotation < BrainInertial.rotation(degrees)){
           
           LM_velocity = -velo2*kp2;
           RM_velocity = velo2*kp2;
           LM.setVelocity(LM_velocity, percent);
           RM.setVelocity(RM_velocity, percent);
           LM.spin(forward);
           RM.spin(forward);
           wait(20, msec);
   

       }
      LM.stop();
      RM.stop();

    }


    if (targetRotation > BrainInertial.rotation(degrees)){
       
       while (targetRotation > BrainInertial.rotation(degrees)){
           
           LM_velocity = velo2*kp2;
           RM_velocity = -velo2*kp2;
           LM.setVelocity(LM_velocity, percent);
           RM.setVelocity(RM_velocity, percent);
           LM.spin(forward);
           RM.spin(forward);
           wait(20, msec);
   

       }
      LM.stop();
      RM.stop();

    }
  
  


}


void driveConst(int constVelo, float heading){
  
  
  //LM.setPosition(0, degrees);
  //LM.setPosition(0, degrees);


  LM.setVelocity(constVelo, percent);
  RM.setVelocity(constVelo, percent);
  
  while (heading > BrainInertial.rotation(degrees)+5 || heading < BrainInertial.rotation(degrees)-5){
     

     rotError = heading - BrainInertial.rotation(degrees); //IMPORTANT!! INERTIALROTATION DOES NOT RETURN UPDATED ROTATION
     power = rotError*0.4;
     LM.setVelocity(constVelo + power, percent);
     RM.setVelocity(constVelo - power, percent);

     
     LM.spin(forward);
     RM.spin(forward);
     wait(20, msec);


  }

  

LM.stop();
RM.stop();
Brain.Screen.printAt(20, 100, "Done");
}

// void computeVelocities(float linearError, float directionError){
  
// }