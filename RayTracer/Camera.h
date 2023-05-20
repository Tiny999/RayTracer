#pragma once

#include "Rtweekend.h"

class Camera
{
public:
	Camera();
	
	Ray Get_Ray(double u, double v) const;
	

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
};