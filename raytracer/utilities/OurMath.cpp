#include "OurMath.hpp"

float OurMath::clamp(float x, float min, float max) {
    return (x < min ? min : (x > max ? max : x));
}