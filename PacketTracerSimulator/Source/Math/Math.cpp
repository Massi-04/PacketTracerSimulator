#include "Math.h"
#include <math.h>

double Math::Normalize(const double& value, const double& min, const double& max)
{
	return (value - min) / (max - min);
}

double Math::DeNormalize(const double& value, const double& min, const double& max)
{
	return value * (max - min) + min;
}

double Math::Sqrt(const double& value)
{
	return sqrt(value);
}
