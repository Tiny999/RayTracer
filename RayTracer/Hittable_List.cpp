#include "Hittable_List.h"

void Hittable_List::Clear()
{
	objects.clear();
}

void Hittable_List::Add(shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool Hittable_List::Hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->Hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
