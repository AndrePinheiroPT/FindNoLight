#include "FindNoLight.h"
#include "Arduino.h"  

#include <stdlib.h> 
#include <time.h>
#include <math.h>  

Neural_Network::Neural_Network(){
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < 4; k++){
            weights_l1[i][k] = rd();
            weights_l2[k] = rd();
            bias_l1[k] = rd();
            bias_l2 = rd();
        } 
    }
}

double Neural_Network::reLU(double x){
    return (x >= 0) ? x : 0;
}

double Neural_Network::reLU_prime(double x){
    return (x >= 0) ? 1 : 0;
}

double Neural_Network::rd(){
    float rad = random(0, 32768);
    return  rad / 32767;
}

double Neural_Network::feed_forward(int inputs[]){
    for(int j = 0; j < 4; j++){
        double total_sum1 = 0;
        for(int k = 0; k < 3; k++){
            total_sum1 += inputs[k] * weights_l1[k][j];
        }
        a_l1[j] = total_sum1 + bias_l1[j];
        o_l1[j] = reLU(a_l1[j]);
    }
    
    double total_sum2 = 0;
    for(int k = 0; k < 4; k++){
        total_sum2 += o_l1[k] * weights_l2[k];
    }
    a_l2 = total_sum2 + bias_l2;
    o_l2 = reLU(a_l2);

    return o_l2;
}

double Neural_Network::back_propagation(int inputs[], int target){
    double learning_rate, output, cost;
    double dcost_dwij, dcost_dbj, dcost_do2, do2_da2, da2_do1, do1_da1, da1_dwij, da1_dbj,da2_dwij, da2_dbj;

    learning_rate = 0.00000001;
    output = feed_forward(inputs);
    cost = pow(output - target, 2);

    for(int j = 0; j < 4; j++){
        dcost_do2 = 2 * (output - target);
        do2_da2 = reLU_prime(a_l2);
        da2_dwij = o_l1[j];
        da2_dbj = 1;

        dcost_dwij = dcost_do2 * do2_da2 * da2_dwij;
        dcost_dbj = dcost_do2 * do2_da2 * da2_dbj;

        weights_l2[j] -= learning_rate * dcost_dwij;
        bias_l2 -= learning_rate * dcost_dbj;
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            dcost_do2 = 2 * (output - target);
            do2_da2 = reLU_prime(a_l2);
            da2_do1 = weights_l2[j];
            do1_da1 = reLU_prime(a_l1[j]);
            da1_dwij = reLU(inputs[i]);
            da1_dbj = 1;

            dcost_dwij = dcost_do2 * do2_da2 * da2_do1 * do1_da1 * da1_dwij;
            dcost_dbj = dcost_do2 * do2_da2 * da2_do1 * do1_da1 * da1_dbj;

            weights_l1[i][j] -= learning_rate * dcost_dwij;
            bias_l1[j] -= learning_rate * dcost_dbj;
        }
    }

    return cost;
}
