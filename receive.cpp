#include "vex.h"
#include "receive.h"
#include <cstdio>
#include <cstdlib>

using namespace vex;

float path[50];

float* receive(){
//     string num;

//     ifstream read("ints.txt");

//     while( getline(read, num) ){

//         cout << num;
//     }

//     ofstream file("ints.txt", ios::trunc); //truncates (clears) the file
//     return 0;

FILE *file = fopen("ints.txt", "r");
    if (!file) {
        printf("File could not be opened!\n");
        
    }

    char line[256];
    
    int x = 0;
    while (fgets(line, sizeof(line), file)) {
        float numLine = atof(line);
        path[x] = numLine;
        x+=1;
    }

    fclose(file);
    
    return path;
}

// int main(){
//     float* ptrNum = receive();
    
//     for (int i = 0; i < 44; i++){
//         printf("%f", ptrNum[i]);
//         printf("\n");
//     }
    
// }