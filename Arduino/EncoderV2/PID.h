#ifndef PID_H
#define PID_H

#include "Arduino.h"

class PID {
public:
    PID();  // Constructor
    void setParameters(float K_p_new, float K_i_new, float K_d_new);  // Change gain values 
    void calculateNewSignal(int target_speed, int current_speed);  // Calculate and send new signal
    float u_t;
private:
    // Member variables
    float K_p, K_i, K_d, prev_error, integral_error, dt;
    int current_time, prev_time;
};

#endif
