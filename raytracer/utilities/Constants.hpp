#pragma once
#include "RGBColor.hpp"
/**
    This file caches common values and constants.

    Courtesy Kevin Suffern.
*/

// Precompute commonly used values.
const float PI = 3.1415926535897932384;
const float TWO_PI = 6.2831853071795864769;
const float PI_ON_180 = 0.0174532925199432957;
const float invPI = 0.3183098861837906715;
const float invTWO_PI = 0.1591549430918953358;

// Small and large values.
const float kEpsilon = 0.0001;
const float kHugeValue = 1.0E10;

// Some standard colors.
const RGBColor black(0.0);
const RGBColor white(1.0);
const RGBColor grey(0.5);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor blue(0.0, 0.0, 1.0);
// colors
const RGBColor skyBlue(0.498, 0.855, 1);  //sky blue
const RGBColor oceanBlue(0, 0.467, 0.745);  //ocean blue
const RGBColor yellow(1, 1, 0);  // yellow
const RGBColor brown(0.71, 0.40, 0.16);  // brown
const RGBColor darkGreen(0.0, 0.41, 0.41);  // darkGreen
const RGBColor orange(1, 0.75, 0);  // orange
const RGBColor green(0, 0.6, 0.3);  // green
const RGBColor lightGreen(0.65, 1, 0.30);  // light green
const RGBColor darkYellow(0.61, 0.61, 0);  // dark yellow
const RGBColor lightPurple(0.65, 0.3, 1);  // light purple
const RGBColor darkPurple(0.5, 0, 1);  // dark purple

// Useful for scaling the output of rand() to [0,1].
const float invRAND_MAX = 1.0 / (float)RAND_MAX;
