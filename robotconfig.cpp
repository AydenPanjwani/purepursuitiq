#include "vex.h"
#include "robotconfig.h"
using namespace vex;


vex::brain       Brain;
inertial BrainInertial = inertial();
motor LM = motor(PORT12, true);
motor RM = motor(PORT6, false);






