#pragma once

#include "Rtweekend.h"
#include "Ray.h"
#include "Vec3.h"
#include "Hittable.h"

struct hit_record;

class Material
{
public:
	/*virtual bool Scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) = 0;*/

	virtual bool Scatter(
		const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered
	) const = 0;
};