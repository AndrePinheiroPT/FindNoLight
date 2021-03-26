#ifndef FINDNOLIGHT_H_INCLUDED
#define FINDNOLIGHT_H_INCLUDED

#include "Arduino.h"

class Neural_Network{
public:
    Neural_Network();
    double rd();
    double reLU(double x);
    double reLU_prime(double x);
    double feed_forward(int inputs[]);
    double back_propagation(int inputs[], int target);
    double weights_l1[3][4];
    double weights_l2[4];
    double bias_l1[4];
    double bias_l2;

    double a_l1[4];
    double a_l2;

    double o_l1[4];
    double o_l2;
};

#endif
