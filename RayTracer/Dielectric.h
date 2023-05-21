#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(double index_of_refraction) : ir(index_of_refraction) {};

	virtual bool Scatter(
		const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered
	) const override
	{
		attenuation = Color(1., 1., 1.);
		double refraction_ratio = rec.front_face ? (1. / ir) : ir;


		Vec3 unit_direction = unit_vector(r_in.direction());

		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1. - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		Vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio);


		scattered = Ray(rec.p, direction);
		return true;
	}

public:
	double ir; // Refractive Index

private:
	static double reflectance(double cosine, double ref_idx)
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};