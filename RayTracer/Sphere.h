#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(Point3 cen, double r)
		: center(cen), radius(r) {}

public:
	Point3 center;
	double radius;
};

