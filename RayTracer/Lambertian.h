#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Color& a) : albedo(a) {};

	virtual bool Scatter(
		const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered
	) const override
	{
		auto scatter_direction = rec.normal + random_unit_vector();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;


		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}


public:
	Color albedo;
};