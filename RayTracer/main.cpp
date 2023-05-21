#include <iostream>

#include "Rtweekend.h"
#include "Color.h"
#include "Hittable_List.h"
#include "Sphere.h"
#include "Vec3.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

Color ray_color(const Ray& r, const Hittable& world, int depth)
{
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return Color(0, 0, 0);

	if (world.Hit(r, 0.001, infinity, rec))
	{
		Ray scattered;
		Color attenuation;
		if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return Color(0, 0, 0);
	}

	Vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	auto R = cos(pi / 4);
	Hittable_List world;

	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left = make_shared<Dielectric>(1.5);
	auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

	world.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));
	
	// Camera

	Point3 lookfrom(3, 3, 2);
	Point3 lookat(0, 0, -1);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 2.0;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			Color pixel_color(0, 0, 0);

			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);

				Ray r = cam.Get_Ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";

}