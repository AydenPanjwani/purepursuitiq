#include "vex.h"
using namespace vex;

int Logging();
int Odometry();
int lookAheadCircle();
// int Waypoint(int targetx, int targety);

// int path(int coordinates[], int size);
int purepursuit(int coordinates[], int size, float ld);
float* computeVelocities(float goalPoint[]);

extern float LRVelocity[2];
extern float pi;
extern float radius;
extern float angleTT;
extern float distanceTT;
extern float xpos;
extern float ypos;
extern float ldCircle[2];