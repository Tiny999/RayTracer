#pragma once

#include "Ray.h"

struct hit_record
{
	Point3 p;
	Vec3 normal;
	double t;
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, double t_Smin, double t_max, hit_record& rec) const = 0;
};

