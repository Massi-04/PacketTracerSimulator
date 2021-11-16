#pragma once

#include "Vec2.h"

#define ENGINE_UNIT 0.01f

class Math
{
public:
	Math() = delete;

	template <class T>
	static T Clamp(const T& value, const T& min, const T& max)
	{
		if (value > max)
			return max;
		if (value < min)
			return min;
		return value;
	}

	// Normalizes a value from 0 to 1
	static double Normalize(const double& value, const double& min, const double& max);
	static double DeNormalize(const double& value, const double& min, const double& max);

	static double Sqrt(const double& value);
};
