
#include "vex.h"
#include "intersection.h"
#include "robotconfig.h"



using namespace vex;


bool sol1_in_bounds = false;
bool sol2_in_bounds = false;

// Consider using structs


float x1;
float x2;
float y3;
float y2;




float a;
float b;
float m;
float c;
float A;
float B;
float C;
float discriminant;

float solx1;
float solx2;
float soly1;
float soly2;
float sol[2];
float sol1[2];
float sol2[2];
float endLine[2];
float dist;

float minimum(float min1, float min2){
    return min1 < min2 ? min1:min2;
}

float maximum(float min1, float min2){
    return min1 > min2 ? min1:min2;
}

float euclideanDistance(float pt1[], float pt2[]){
    dist = sqrt((pt2[0] - pt1[0])*(pt2[0] - pt1[0]) + (pt2[1] - pt1[1])*(pt2[1] - pt1[1]));
    return dist;
}


float* intersection(float circle[], float r, float lineX[], float lineY[]){
    x1 = lineX[0];
    x2 = lineX[1];
    
    y3 = lineY[0];
    y2 = lineY[1];
    
    a = circle[0];
    b = circle[1];

    m = (y2-y3)/(x2-x1);
    c = y3 - m*x1;
    A = 1+m*m;
    B = 2* (m*c - m *b -a);
    C = a*a + b*b + c*c - 2*c*b - r*r;

    discriminant = B*B - 4*A*C;
    if (discriminant < 0){
        sol[0] = 0;
        sol[1] = 0;
        return sol;
    }
    
    solx1 = (-B + sqrt(discriminant)) / (2*A);
    solx2 = (-B - sqrt(discriminant)) / (2*A);
    soly1 = m*solx1 + c;
    soly2 = m*solx2 + c;
    // Brain.Screen.printAt(0, 40, "NIB%.2f", soly1);
    // Brain.Screen.printAt(0, 60, "NIB%.2f", soly2);
    //problem HAS TO BE WITH FMIN and FMAX(I THINK)
    if ( minimum(x1,x2) <= solx1 && solx1 < maximum(x1,x2) && minimum(y3,y2) <= soly1  && soly1 < maximum(y3,y2)){
        sol1_in_bounds = true;
        sol[0] = solx1;
        sol[1] = soly1;

    }

    if ( minimum(x1,x2) <= solx2 && solx2 < maximum(x1,x2) && minimum(y3,y2) <= soly2 && soly2 < maximum(y3,y2)){
        sol2_in_bounds = true;
        sol[0] = solx2;
        sol[1] = soly2;
    }

    if (sol2_in_bounds == false && sol1_in_bounds == false) {
        sol[0] = 0;
        sol[1] = 0;
        return sol; 
    }

    sol2[0] = solx2;
    sol2[1] = soly2;

    sol1[0] = solx1;
    sol1[1] = soly1;

    endLine[0] = lineX[1];
    endLine[1] = lineY[1];
    

    if (sol1_in_bounds == true && sol2_in_bounds == true){
        if (euclideanDistance(sol1, endLine) < euclideanDistance(sol2, endLine)){
            sol[0] = solx1;
            sol[1] = soly1;
        }

        else {
            sol[0] = solx2;
            sol[1] = soly2;
        }
    }
    
    // cout << x1 << "\n";
    // cout << x2 << "\n";
    // cout << y3 << "\n";
    // cout << y2 << "\n";
    // cout << a << "\n";
    // cout << b << "\n";
    // cout << m << "\n";
    // cout << c << "\n";
    // cout << A << "\n";
    // cout << B << "\n";
    // cout << C << "\n";
    // cout << discriminant << "\n";
    // cout << solx1 << "\n";
    // cout << solx2 << "\n";
    // cout << soly1 << "\n";
    // cout << soly2 << "\n";
    // cout << sol[0] << "\n";
    // cout << sol[1];
    return sol;
}

// int main(){
//     float c[2] = {5,5};
//     float l[2] = {0,10};

//     intersection(c, 2, l, l);
// }

