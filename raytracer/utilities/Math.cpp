#include "Math.hpp"

float Math::clamp(float x, float min, float max) {
    return (x < min ? min : (x > max ? max : x));
}