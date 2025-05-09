#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cout;
using std::endl;

//  V   V   EEEEE   RRRR    TTTTT   EEEEE   X   X
//  V   V   E       R   R     T     E        X X
//  V   V   EEEEE   RRRR      T     EEEEE     X
//   V V    E       R   R     T     E        X X
//    V     EEEEE   R   R     T     EEEEE   X   X

class vertex
{
public:

	// Constructors

	vertex();
	~vertex();
	vertex(float x, float y, float z);
	vertex(const vertex& source);
	vertex& operator=(const vertex& source);

	// Data Returns

	vector<float> get_xyz() const;
	float get_coord(int axis) const;
	float get_x() const;
	float get_y() const;
	float get_z() const;

	// Transforms

	void set(float x, float y, float z);
	void scale(float factor);
	void scale_xyz(float factor_x, float factor_y, float factor_z);
	void scale_x(float factor);
	void scale_y(float factor);
	void scale_z(float factor);
	void shift(float x, float y, float z);
	void shift_x(float x);
	void shift_y(float y);
	void shift_z(float z);

private:

	// Helper

	bool tolerance(float a, float b) const;

	float x_coord;
	float y_coord;
	float z_coord;
};

//  SSSSS   H   H     A     PPPPP   EEEEE
//  S       H   H    A A    P   P   E
//  SSSSS   HHHHH   AAAAA   PPPPP   EEEEE
//      S   H   H   A   A   P       E
//  SSSSS   H   H   A   A   P       EEEEE

class shape
{
public:

	// Constructors

	shape();
	virtual ~shape();
	shape(float x, float y, float z);
	shape(const shape& source);
	shape& operator=(const shape& source);

	// Data Returns

	int get_vector_count() const;
	vector<vector<float>> get_all__relative_vertices() const;
	vector<float> get_relative_vertex(int index) const;
	vector<vector<float>> get_all_vertices() const;
	vector<float> get_vertex(int index) const;
	vector<float> get_base() const;

	float get_base_coord(int axis) const;
	string get_name() const;
	void print() const;
	void print_vertices() const;

	// Origin Transforms

	void move_shape(float x, float y, float z);
	void shift_shape(float x, float y, float z);
	void shift_shape_x(float length);
	void shift_shape_y(float length);
	void shift_shape_z(float length);

	// Vertex Transforms

	void add_vertex(float x, float y, float z);
	void rescale(float scale);
	void rescale(float factor_x, float factor_y, float factor_z);
	void rescale_x(float factor);
	void rescale_y(float factor);
	void rescale_z(float factor);
	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);

	// Misc Public

	void rename_shape(string new_name);

protected:

	// Numerical Analysis

	float to_radians(float angle);
	bool tolerance(float a, float b) const;
	bool check_equals(vertex* v1, vertex* v2) const;
	bool check_equals(float x1, float y1, float z1, float x2, float y2, float z2) const;
	bool check_equals(vertex* v1, float x, float y, float z) const;

	vector<vertex*> shape_points;

private:

	// Misc Private

	void delete_all_data();

	string name;
	vertex* base;
};

//   CCCC   U   U   BBBB     OOO    IIIII   DDDD
//  C       U   U   B   B   O   O     I     D   D
//  C	    U   U   BBBB    O   O     I     D   D
//  C       U   U   B   B   O   O     I     D   D
//   CCCC    UUU    BBBB     OOO    IIIII   DDDD

class cuboid : public shape
{
public:

	// Constructors

	cuboid();
	~cuboid() = default;
	cuboid(float scale);
	cuboid(float scale_x, float scale_y, float scale_z);

private:

	// Helper

	void generate_vertices(float scale_x, float scale_y, float scale_z);
};

//  TTTTT   EEEEE   TTTTT   RRRR      A     H   H   EEEEE   DDDD    RRRR     OOO    N   N
//    T     E         T     R   R    A A    H   H   E       D   D   R   R   O   O   NN  N
//    T     EEEEE     T     RRRR    AAAAA   HHHHH   EEEEE   D   D   RRRR    O   O   N N N
//    T     E         T     R   R   A   A   H   H   E       D   D   R   R   O   O   N  NN
//    T     EEEEE     T     R   R   A   A   H   H   EEEEE   DDDD    R   R    OOO    N   N

class tetrahedron : public shape
{
public:

	// Constructors

	tetrahedron();
	~tetrahedron() = default;
	tetrahedron(float scale);
	tetrahedron(float scale_xy, float scale_z);

private:

	// Helper

	void generate_vertices(float scale_xy, float scale_z);
};

// Other Shapes Coming Soon!

#endif
