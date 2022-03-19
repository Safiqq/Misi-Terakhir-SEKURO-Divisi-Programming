#ifndef robot_hpp
#define robot_hpp

#include <iostream>
#include <cstdio>
#include "axis.h"

using namespace std;

class Robot {
    public:
        Robot();
    	int health;
        int power;
        double range;
        bool isAlive();
        int position[2];
};

class MechaKurama {
    public:
        MechaKurama();
    	int health;
        int power;
        double range;
        bool isAlive();
        int position[2];
        int bunshinNumber;
};

#endif