#include "supershapemaker.h"

//  V   V   EEEEE   RRRR    TTTTT   EEEEE   X   X
//  V   V   E       R   R     T     E        X X
//  V   V   EEEEE   RRRR      T     EEEEE     X
//   V V    E       R   R     T     E        X X
//    V     EEEEE   R   R     T     EEEEE   X   X

vertex::vertex() : x_coord(0), y_coord(0), z_coord(0) {}

vertex::~vertex() = default;

vertex::vertex(float x, float y, float z) : x_coord(x), y_coord(y), z_coord(z) {}

vertex::vertex(const vertex& source) : x_coord(source.x_coord), y_coord(source.y_coord), z_coord(source.z_coord) {}

vertex& vertex::operator=(const vertex& source)
{
	if (this == &source) return *this;

	x_coord = source.x_coord;
	y_coord = source.y_coord;
	z_coord = source.z_coord;

	return *this;
}

// Data Returns

vector<float> vertex::get_xyz() const
{
	return { x_coord, y_coord, z_coord };
}

float vertex::get_coord(int axis) const
{
	switch (axis)
	{
	case 0: return x_coord;
	case 1: return y_coord;
	case 2: return z_coord;
	default: return 987654.321f;
	}
}

float vertex::get_x() const
{
	return x_coord;
}

float vertex::get_y() const
{
	return y_coord;
}

float vertex::get_z() const
{
	return z_coord;
}

// Transforms

void vertex::set(float x, float y, float z)
{
	x_coord = x;
	y_coord = y;
	z_coord = z;
}

void vertex::scale(float factor)
{
	if (tolerance(factor, 0)) return;

	x_coord *= factor;
	y_coord *= factor;
	z_coord *= factor;
}

void vertex::scale_xyz(float factor_x, float factor_y, float factor_z)
{
	if (tolerance(factor_x, 0)) factor_x = 1.0f;
	if (tolerance(factor_y, 0)) factor_y = 1.0f;
	if (tolerance(factor_z, 0)) factor_z = 1.0f;

	x_coord *= factor_x;
	y_coord *= factor_y;
	z_coord *= factor_z;
}

void vertex::scale_x(float factor)
{
	x_coord *= factor;
}

void vertex::scale_y(float factor)
{
	y_coord *= factor;
}

void vertex::scale_z(float factor)
{
	z_coord *= factor;
}

void vertex::shift(float x, float y, float z)
{
	x_coord += x;
	y_coord += y;
	z_coord += z;
}

void vertex::shift_x(float x)
{
	x_coord += x;
}

void vertex::shift_y(float y)
{
	y_coord += y;
}

void vertex::shift_z(float z)
{
	z_coord += z;
}

// Helper

bool vertex::tolerance(float a, float b) const
{
	float difference = a - b;
	difference = (difference < 0 ? -difference : difference);
	return (difference < 0.0001f);
}

