#pragma once

#include "../utils/Common.h"

#include <math.h>

#define SP_PI 3.14159265358f

inline float toRadians(float degrees)
{
	return (float)(degrees * (SP_PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return (float)(radians * (180.0f / SP_PI));
}

inline int sign(float value)
{
	return (value > 0) - (value < 0);
}

inline float _min(float value, float minimum)
{
	return (value < minimum) ? minimum : value;
}

inline float _max(float value, float maximum)
{
	return (value > maximum) ? maximum : value;
}

inline float clamp(float value, float minimum, float maximum)
{
	return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
}

