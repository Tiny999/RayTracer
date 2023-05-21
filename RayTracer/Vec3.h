#pragma once

#include <cmath>
#include <iostream>

#include "Rtweekend.h"


using std::sqrt;

class Vec3
{
public:
	Vec3();
	Vec3(double e0, double e1, double e2);

	double x() const;
	double y() const;
	double z() const;

	Vec3 operator -() const;
	double operator [] (int i) const;
	double& operator []	 (int i);

	Vec3& operator += (const Vec3& v);
	Vec3& operator *= (const double t);
	Vec3& operator /= (const double t);

	double length() const;
	double length_squared() const;

	inline static Vec3 random() {
		return Vec3(random_double(), random_double(), random_double());
	}

	inline static Vec3 random(double min, double max) {
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

public:
	double e[3];
};

// Type Aliases
typedef Vec3 Point3;
typedef Vec3 Color;


// Utility Functions 

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1,1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3& normal)
{
	Vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}