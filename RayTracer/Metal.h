#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

	virtual bool Scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered)  const override
	{
		Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	Color albedo;
	double fuzz;
};