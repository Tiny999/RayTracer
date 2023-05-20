#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>


using std::shared_ptr;
using std::make_shared;

class Hittable_List : public Hittable
{
public:
	Hittable_List() = default;
	Hittable_List(shared_ptr<Hittable> object)
	{
		Add(object);
	}

	void Clear();
	void Add(shared_ptr<Hittable> object);

	virtual bool Hit(const Ray& r, double t_min, double t_max, hit_record& rec)const override;

public:
	std::vector<shared_ptr<Hittable>> objects;
};