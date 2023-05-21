#pragma once

#include "Rtweekend.h"
#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
	Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);
	
	Ray Get_Ray(double s, double t) const;
	

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 w, u, v;
	double lens_radius;
};