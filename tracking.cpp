#include "vex.h"
#include "tracking.h"
#include "robotconfig.h"
#include "intersection.h"
#include "pfunctions.h"

//#include <iostream>


  
// Allows for easier use of the VEX Library
using namespace vex;


  float pi = 3.14159265358979323846264338327; //initializing pi (couldn't find a math library here)
  float xpos; //initializing xpos
  float ypos; //initializing ypos
  float radius = 2.5; //initializing radius - although in final testing, the diameter is more accurate when returning the inches the wheel has travelled
  float LMDistanceRaw; //initializing the degrees the left motor has travelled
  float LMDistance; //initializing the inches the left motor has travelled
  float RMDistanceRaw; //same as left motor
  float RMDistance; //same as left motor
  float Distance; //the distance travelled by the robot - calculated by the average of LM and RM distance. This is so, if the robot turns, the positive value on one motor and negative value on the other cancel each other out. 
  float HEADING; //the final heading, after being rounded and converted to radians so the sin and cos function work on it
  float rawx; //the distance travelled on the x axis in each loop, which is then added to the pastx to get the accurate position
  float rawy; //the distance travelled on the y axis in each loop, which is then added to the pasty to get the accurate position
  float pastx;
  float pasty;
  float rawH1;
  float rawH2;
  float targety;
  float targetx;
  float angleTT;
  float distanceTT;
  float LMfp; //LM firstpos
  float RMfp; //RM firstpos
  float LMsp; //LM secondpos
  float RMsp; //RM secondpos
  float ldCircle[2];
  

int lookAheadCircle(){
  while(true){
    ldCircle[0] = xpos;
    ldCircle[1] = ypos;
    wait(20, msec);
  }
  return 0;
}

int Logging(){
while(true){
Brain.Screen.printAt(0, 20, "Heading %.2f", rawH2);
   
   Brain.Screen.printAt(0,80, "xpos %.2f", xpos);
   Brain.Screen.printAt(0,100, "ypos %.2f", ypos);
   wait(20, msec);
   
}

return 0;


}


// "when started" hat block
int Odometry() {


   BrainInertial.calibrate();
 while(true) {
   
   LMfp = LM.position(degrees);
   RMfp = RM.position(degrees);
   //RM.setPosition(0,degrees);
   //LM.setPosition(0,degrees);
   
   wait(20,msec);
   LMsp = LM.position(degrees);
   RMsp = RM.position(degrees);

   rawH1 = BrainInertial.heading(degrees);
   rawH2 = round(rawH1);
   LMDistanceRaw = LMsp - LMfp;
   
   LMDistance = LMDistanceRaw * (pi/180) * radius;
   RMDistanceRaw = RMsp - RMfp;
   RMDistance = RMDistanceRaw * (pi/180) * radius;
   Distance = (RMDistance + LMDistance)/2;
   HEADING = rawH2 * pi/180;

   rawx = (Distance * sin(HEADING));
   rawy = (Distance * cos(HEADING));

   xpos = rawx + pastx;
   ypos = rawy + pasty;

   //Brain.Screen.printAt(0, 10, " xpos %.2f", xpos);
   //Brain.Screen.printAt(0, 50, "ypos %.2f", ypos);
   
   pastx = xpos;
   pasty = ypos;



 }


 return 0;
}

int purepursuit(int coordinates[], int size, float ld){ //maybe change size to dif var

  float x_points[size/2];
  float y_points[size/2];
  float ld_point[2];
  ld_point[0] = coordinates[0];
  ld_point[1] = coordinates[1];
  float startLineSegment[2];
  float endLineSegment[2];
  float angleTDC;
  int lastFoundPoint = 0;
  float linex[2];
  float liney[2];
  float goalPoint[2];
  float prevGoalPoint[2] = {0,0};
  
  
  
  // float prev_ld_point[2];
  // float dx;
  // float dy;
  // float dr;
  
   
   for(int k = 0; k < (size/2); k++){
    x_points[k] = coordinates[k*2];
    y_points[k] = coordinates[k*2+1];
   
  
 }
 
 while (true){
   Brain.Screen.printAt(120, 100, "%d", lastFoundPoint);
   startLineSegment[0] = x_points[lastFoundPoint];
   startLineSegment[1] = y_points[lastFoundPoint];

   endLineSegment[0] = x_points[lastFoundPoint+1];
   endLineSegment[1] = y_points[lastFoundPoint+1];
   float goalPoints[size/2 - 1+lastFoundPoint][2];


   for (int z = 0; z < (size/2 - (1+lastFoundPoint)); z++){

    linex[0] = x_points[lastFoundPoint+z];
    linex[1] = x_points[lastFoundPoint+z+1];

    liney[0] = y_points[lastFoundPoint+z];
    liney[1] = y_points[lastFoundPoint+z+1];
    float* ptr;
    ptr = intersection(ldCircle, ld, linex, liney);
    
    
    goalPoints[z][0] = ptr[0]; 
    goalPoints[z][1] = ptr[1];
    

   }
   for(int l = 0; l < (size/2 - (1+lastFoundPoint)); l++){
    Brain.Screen.printAt(0, (l+1)*20, "%.2f", goalPoints[l][0]);
    Brain.Screen.printAt(50, (l+1)*20, "%.2f", goalPoints[l][1]);
   }
   
   for(int j = 0; j < (size/2 - (1+lastFoundPoint)); j++){
    
    if (goalPoints[j][0] == 0 && goalPoints[j][1] == 0){
      continue;
    }
    
    if (euclideanDistance(goalPoints[j], endLineSegment) < euclideanDistance(ldCircle, endLineSegment)){
      goalPoint[0] = goalPoints[j][0];
      goalPoint[1] = goalPoints[j][1];
      lastFoundPoint = j+lastFoundPoint;
      // printf("\n index%.2d", j);
      
      
      
      break;
    }
    else {
      lastFoundPoint += 1;
      // Brain.Screen.printAt(0, 40, "index%.0f", j);
      
      continue;
    }
   }
   //move to position code here
   Brain.Screen.printAt(0, 100, "%.2f", goalPoint[0]);
   Brain.Screen.printAt(50, 100, "%.2f", goalPoint[1]);
   
  //  Brain.Screen.printAt(0, 60, "goalPoint%.2f", goalPoint[1]);
    // printf("\n GoalPoint%.2f", goalPoint[0]);
    // printf("\n GoalPoint%.2f", goalPoint[1]);
    
    if (goalPoint[0] >= xpos && goalPoint[1] >= ypos){
        angleTDC = atan2(abs(goalPoint[0] - xpos), abs(goalPoint[1] - ypos)); //45
        angleTDC = angleTDC * (180/pi);
    }
  
    else if (goalPoint[0] < xpos && goalPoint[1] >= ypos){
        angleTDC = atan2(abs(goalPoint[1] - ypos), abs(goalPoint[0] - xpos)); //-45 aka 315
        angleTDC = (angleTDC * (180/pi) )+270;
    }

    else if (goalPoint[0] < xpos && goalPoint[1] < ypos){
        angleTDC = atan2(abs(goalPoint[0] - xpos), abs(goalPoint[1] - ypos)); //225
        angleTDC = (angleTDC * (180/pi)) + 180;
    }

    else if (goalPoint[0] >= xpos && goalPoint[1] < ypos){
        angleTDC = atan2(abs(goalPoint[1] - ypos), abs(goalPoint[0] - xpos)); //135
        angleTDC = (angleTDC * (180/pi) )+90;
    }

    float distanceTDC = sqrt( ((goalPoint[0] - xpos)*(goalPoint[0] - xpos)) + ((goalPoint[1] - ypos)*(goalPoint[1] - ypos)) );
     
    //  dx = prev_ld_point[0] - ld_point[0];
    //  dy = prev_ld_point[1] - ld_point[1];
    //  dr = sqrt(dx*dx + dy*dy);
   
   
    
   if(angleTDC > 180){
    angleTDC = angleTDC - 360;
    }

  //   turnError = absTargetAngle - currentHeading
  // if turnError > 180 or turnError < -180 :
  //   turnError = -1 * sgn(turnError) * (360 - abs(turnError))
     


    // turnTo(angleTDC, 20);
    // wait(1, seconds);
    // driveStraight(distanceTDC, angleTDC, 20);
    // wait(1, seconds);

    LM.setVelocity((distanceTDC*1) + ((angleTDC - BrainInertial.rotation(degrees))*0.3), percent);
    RM.setVelocity((distanceTDC*1) - ((angleTDC - BrainInertial.rotation(degrees))*0.3), percent);

    

    LM.spin(forward);
    RM.spin(forward);

   //wait 20 msec
   prevGoalPoint[0] = goalPoint[0];
   prevGoalPoint[1] = goalPoint[1];
   wait(20, msec);

 }


 return 0;

}


// int Waypoint(int targetx, int targety){

 

//    angleTT = atan2(targety - ypos, targetx - xpos);
   
//    //angleTT is assuming that you are at 0 deg. Let's say that after 5,5, you're turned to 45 deg. If angleTT generates 45 deg, how
//    //do we stay at that. What calculation should we do?

//    //Answer - Subtraction? Try it out. 

//    //if we are at 45, and the next angleTT is 45, we should do angleTT - inertial = 0
//    //if we are at 45 and the next angleTT is 90, =45
//    //if we are at 0 and the next angle TT is 45, =45
//    distanceTT = sqrt( ((targetx - xpos)*(targetx - xpos)) + ((targety - ypos)*(targety - ypos)) );
//    //turnTo(angleTT);
//    //driveForward(distanceTT, angleTT);
//    angleTT = angleTT * (180/pi);
//    if (angleTT > 180){
     
//      angleTT = angleTT - 360;


//    }