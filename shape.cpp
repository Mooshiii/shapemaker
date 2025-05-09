#include "supershapemaker.h"


//  SSSSS   H   H     A     PPPPP   EEEEE
//  S       H   H    A A    P   P   E
//  SSSSS   HHHHH   AAAAA   PPPPP   EEEEE
//      S   H   H   A   A   P       E
//  SSSSS   H   H   A   A   P       EEEEE

// Constructors

shape::shape()
{
	base = new vertex;
}

shape::~shape()
{
	delete_all_data();
}

shape::shape(float x, float y, float z)
{
	base = new vertex{ x, y, z };
}

shape::shape(const shape& source)
{
	name = source.get_name();

	base = new vertex{ *source.base };

	for (vertex* v : source.shape_points)
	{
		add_vertex(v->get_x(), v->get_y(), v->get_z());
	}
}

shape& shape::operator=(const shape& source)
{
	if (this == &source) return *this;

	delete_all_data();

	name = source.get_name();

	base = new vertex{ *source.base };

	for (vertex* v : source.shape_points)
	{
		add_vertex(v->get_x(), v->get_y(), v->get_z());
	}

	return *this;
}

// Data Returns

int shape::get_vector_count() const
{
	return shape_points.size();
}

vector<vector<float>> shape::get_all__relative_vertices() const
{
	vector<vector<float>> return_vector;

	for (vertex* v : shape_points)
	{
		return_vector.push_back(v->get_xyz());
	}

	return return_vector;
}

vector<float> shape::get_relative_vertex(int index) const
{
	return shape_points[index]->get_xyz();
}

vector<vector<float>> shape::get_all_vertices() const
{
	vector<vector<float>> return_vector;

	for (vertex* v : shape_points)
	{
		return_vector.push_back
		({
			v->get_x() + base->get_x(),
			v->get_y() + base->get_y(),
			v->get_z() + base->get_z()
			});
	}

	return return_vector;
}

vector<float> shape::get_vertex(int index) const
{
	return
	{
		shape_points[index]->get_x() + base->get_x(),
		shape_points[index]->get_y() + base->get_y(),
		shape_points[index]->get_z() + base->get_z()
	};
}

vector<float> shape::get_base() const
{
	return base->get_xyz();
}

float shape::get_base_coord(int direction) const
{
	switch (direction)
	{
	case 0: return base->get_x();
	case 1: return base->get_y();
	case 2: return base->get_z();
	default: return 987654.321f;
	}
}

string shape::get_name() const
{
	return name;
}

void shape::print() const
{
	if (name.length()) cout << name << ":" << endl;

	cout << "Base: " << base->get_x() << ", "
		<< base->get_y() << ", "
		<< base->get_z() << endl;

	if (!shape_points.empty())
	{
		for (vertex* v : shape_points)
		{
			cout << "\tVertex: (" << v->get_x() + base->get_x() << ", "
				<< v->get_y() + base->get_y() << ", "
				<< v->get_z() + base->get_z() << ")" << endl;
		}
	}
}

void shape::print_vertices() const
{
	if (name.length()) cout << name << ":" << endl;

	cout << "(" << base->get_x() << ", "
		<< base->get_y() << ", "
		<< base->get_z() << ")" << endl;

	for (vertex* v : shape_points)
	{
		cout << "\t(" << v->get_x() + base->get_x() << ", "
			<< v->get_y() + base->get_y() << ", "
			<< v->get_z() + base->get_z() << ")" << endl;
	}
}

// Origin Transforms

void shape::move_shape(float x, float y, float z)
{
	base->set(x, y, z);
}

void shape::shift_shape(float x, float y, float z)
{
	base->shift(x, y, z);
}

void shape::shift_shape_x(float length)
{
	base->shift_x(length);
}

void shape::shift_shape_y(float length)
{
	base->shift_y(length);
}

void shape::shift_shape_z(float length)
{
	base->shift_z(length);
}

// Vertex Transforms

void shape::add_vertex(float x, float y, float z)
{
	for (vertex* v : shape_points)
	{
		if (check_equals(v, x, y, z)) return;
	}

	vertex* new_vertex = new vertex(x, y, z);

	shape_points.push_back(new_vertex);
}

void shape::rescale(float factor)
{
	for (vertex* v : shape_points)
	{
		v->scale(factor);
	}
}

void shape::rescale(float factor_x, float factor_y, float factor_z)
{
	for (vertex* v : shape_points)
	{
		v->scale_xyz(factor_x, factor_y, factor_z);
	}
}

void shape::rescale_x(float factor)
{
	for (vertex* v : shape_points)
	{
		v->scale_x(factor);
	}
}

void shape::rescale_y(float factor)
{
	for (vertex* v : shape_points)
	{
		v->scale_y(factor);
	}
}

void shape::rescale_z(float factor)
{
	if (tolerance(factor, 0)) return;

	for (vertex* v : shape_points)
	{
		v->scale_z(factor);
	}
}

void shape::rotate_x(float angle)
{
	float angle_radians = to_radians(angle);

	for (vertex* v : shape_points)
	{
		float y = v->get_y();
		float z = v->get_z();

		float new_y = (y * cos(angle_radians)) - (z * sin(angle_radians));
		float new_z = (y * sin(angle_radians)) + (z * cos(angle_radians));

		if (tolerance(new_y, 0)) new_y = 0;
		if (tolerance(new_z, 0)) new_z = 0;

		v->set(v->get_x(), new_y, new_z);
	}
}

void shape::rotate_y(float angle)
{
	float angle_radians = to_radians(angle);

	for (vertex* v : shape_points)
	{
		float x = v->get_x();
		float z = v->get_z();

		float new_x = (x * cos(angle_radians)) + (z * sin(angle_radians));
		float new_z = (-x * sin(angle_radians)) + (z * cos(angle_radians));

		if (tolerance(new_x, 0)) new_x = 0;
		if (tolerance(new_z, 0)) new_z = 0;

		v->set(new_x, v->get_y(), new_z);
	}
}

void shape::rotate_z(float angle)
{
	float angle_radians = to_radians(angle);

	for (vertex* v : shape_points)
	{
		float x = v->get_x();
		float y = v->get_y();

		float new_x = (x * cos(angle_radians)) - (y * sin(angle_radians));
		float new_y = (x * sin(angle_radians)) + (y * cos(angle_radians));

		if (tolerance(new_x, 0)) new_x = 0;
		if (tolerance(new_y, 0)) new_y = 0;

		v->set(new_x, new_y, v->get_z());
	}
}

// Misc Public

void shape::rename_shape(string new_name)
{
	name = new_name;
}

// Numerical Analysis

float shape::to_radians(float angle)
{
	return (angle * (3.14159265358979f / 180.0f));
}

bool shape::tolerance(float a, float b) const
{
	float difference = a - b;
	difference = (difference < 0 ? -difference : difference);
	return (difference < 0.0001f);
}

bool shape::check_equals(vertex* v1, vertex* v2) const
{
	return
	(
		tolerance(v1->get_x(), v2->get_x()) &&
		tolerance(v1->get_y(), v2->get_y()) &&
		tolerance(v1->get_z(), v2->get_z())
	);
}

bool shape::check_equals(float x1, float y1, float z1, float x2, float y2, float z2) const
{
	return
	(
		tolerance(x1, x2) &&
		tolerance(y1, y2) &&
		tolerance(z1, z2)
	);
}

bool shape::check_equals(vertex* v1, float x, float y, float z) const
{
	return
	(
		tolerance(v1->get_x(), x) &&
		tolerance(v1->get_y(), y) &&
		tolerance(v1->get_z(), z)
	);
}

// Misc Private

void shape::delete_all_data()
{
	for (vertex* v : shape_points)
	{
		delete v;
	}

	shape_points.clear();

	delete base;
	base = nullptr;
}