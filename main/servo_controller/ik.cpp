/*******************************************************
 * Spider IK
 * 
 * Spider leg:
 *       C
 *      / \
 *  L0 /   \
 *    /     \ L1
 *  AB       \
 *            \
 *             \  
 *           (x, y, z)
 * 
 * A       -> yaw axis
 * B and C -> pitch axis
 * 
 * A - theta_0 (yaw)    = atg(y/x)
 * B - theta_1 (pitch)  = gama +- alpha 
 * C - theta_2 (pitch)  = 180° - beta
 * alpha    = acos((P² + L0² - L1²)/(2PL0))
 * beta     = acos((L0² + L1² -P²)/(2L0L1))
 * gama     = atg(z/x)
 * 
 * x, y -> footprint
 * z    -> height
 * 
*******************************************************/

#include <math.h>
#include <vector>
#include "servo_controller/ik.hpp"

float IK::getP(float x, float z){
    float p = sqrt(x*x + z*z);
    return p;
}
float IK::getAlpha(float L0, float L1, float P){

    float a = P*P + L0*L0 - L1*L1;
    float b = 2*P*L0;
    float alpha = acos(a/b);
    return alpha;
    
}
float IK::getBeta(float L0, float L1, float P){

    float a = L0*L0 + L1*L1 - P*P;
    float b = 2*L0*L1;
    float beta = acos(a/b);
    return beta;
    
}
float IK::getTheta0(float x, float y){
    float theta0 = atan(y/x);
    return theta0;
}
float IK::getTheta1(float x, float z, float alpha){
    
    float gama = atan(z/x);
    float theta1 = gama + alpha;
    return theta1;

}
float IK::getTheta2(float beta){

    float theta2 = 2*M_PI - beta;
    return theta2;

}
std::vector<float> IK::getAngles(float position[3], float L0, float L1){

    // split position vector
    float x = position[0];
    float y = position[1];
    float z = position[2];

    // ----------------------------------------
    // calculate angles
    // ----------------------------------------

    float theta0 = getTheta0(x, y);
    
    float P = getP(x, z);
    float alpha = getAlpha(L0, L1, P);
    float theta1 = getTheta1(x, z, alpha);

    float beta = getBeta(L0, L1, P);
    float theta2 = getTheta2(beta);

    // ----------------------------------------

    // mount angle vector
    std::vector<float> angles{theta0, theta1, theta2};

    return angles;

}