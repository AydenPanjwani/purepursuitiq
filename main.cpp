/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Achievan                                                  */
/*    Created:      2/16/2024, 11:32:08 AM                                    */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robotconfig.h"
#include "tracking.h"
#include "intersection.h"
#include "pfunctions.h"
#include "receive.h"

//#include <iostream>



int coord[] = {0,0, 12,12,5, 14, 12, -5}; //want to reverse it - +22,+3

//int coord[] = {0,0, 2,3, 4, 5};8,14 - 12,-5   

float start[2] = {0,0};
float target[2] = {1, 20};
float nexttarget[2] = {0, 40};

using namespace vex;
int main(){
  BrainInertial.calibrate();
  BrainInertial.setRotation(0, degrees);
  // vex::task ws1(Logging);
  vex::task ws2(Odometry);
  vex::task ws3(lookAheadCircle);
  wait(2, seconds); //lets inertial calibrate properly   //maybe try putting the wait directly after calibration. makes more sense
  //Waypoint(5, 5);

  purepursuit(coord, 8, 3);  

  float* ptrNum = receive();
    
  //  for (int i = 0; i < 50; i++){
  //    printf("%f", ptrNum[i]);
  //    printf("\n");
  //   }


  // float vun[2] = {0,0};
  // float vree[2] = {0,-12};
  // float vour[2] = {0,12};
  // float* ptr2 = intersection(vun, 3, vree, vour);
  // Brain.Screen.printAt(0, 40, "goalPoint%.2f", ptr2[0]);
  // Brain.Screen.printAt(0, 60, "goalPoint%.2f", ptr2[1]);

  // driveConst(30,60);
  // driveConst(30, 0);
  // driveConst(30, 60);
  
  //driveConst(30, 60);

  



}
