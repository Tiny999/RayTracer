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


Hittable_List random_scene()
{
	Hittable_List world;

	auto ground_material = make_shared<Lambertian>(Color(.5, .5, .5));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			Point3 center(a + .9 * random_double(), .2, b + .9 * random_double());

			if ((center - Point3(4, .2, 0)).length() > .9)
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < .8)
				{
					// diffuse
					auto albedo = Color::random() * Color::random();
					sphere_material = make_shared<Lambertian>(albedo);
					world.Add(make_shared<Sphere>(center, .2, sphere_material));
				}
				else if (choose_mat < .95)
				{
					// metal 
					auto albedo = Color::random(.5, 1);
					auto fuzz = random_double(0, .5);
					sphere_material = make_shared<Metal>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, .2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, .2, sphere_material));
				}
			}

		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1., material1));

	auto material2 = make_shared<Lambertian>(Color(.4, .2, .1));
	world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1., material2));

	auto material3 = make_shared<Metal>(Color(.7, .6, .5), 0.);
	world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1., material3));

	return world;
}


int main() {
	// Image
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 50;

	// World
	auto world = random_scene();
	
	// Camera

	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = .1;

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