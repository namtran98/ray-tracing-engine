#pragma once

class Math {
public:

    /* 
        Clamps the first parameter between the last two, using linear 
        interpolation to join the min and the max values. 
    */
    static float clamp(float x, float min, float max);
}