#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction);

	Point3 origin() const;
	Vec3 direction() const;

	Point3 at(double t) const;

private:
	Point3 orig;
	Vec3 dir;
};

