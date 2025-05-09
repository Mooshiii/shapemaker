#include "supershapemaker.h"

//   CCCC   U   U   BBBB     OOO    IIIII   DDDD
//  C       U   U   B   B   O   O     I     D   D
//  C	    U   U   BBBB    O   O     I     D   D
//  C       U   U   B   B   O   O     I     D   D
//   CCCC    UUU    BBBB     OOO    IIIII   DDDD

// Constructors

cuboid::cuboid()
{
	generate_vertices(1, 1, 1);
}

cuboid::cuboid(float scale)
{
	if (tolerance(scale, 0))
	{
		rename_shape("VERTEX");
		return;
	}

	generate_vertices(scale, scale, scale);
}

cuboid::cuboid(float scale_x, float scale_y, float scale_z)
{
	if (tolerance(scale_x, 0) || tolerance(scale_y, 0) || tolerance(scale_z, 0))
	{
		rename_shape("VERTEX");
		return;
	}

	generate_vertices(scale_x, scale_y, scale_z);
}

// Helper

void cuboid::generate_vertices(float scale_x, float scale_y, float scale_z)
{
	rename_shape("CUBOID");

	for (int i = -1; i < 2; i += 2)
		for (int j = -1; j < 2; j += 2)
			for (int k = -1; k < 2; k += 2)
				add_vertex(i * scale_x, j * scale_y, k * scale_z);
}

//  TTTTT   EEEEE   TTTTT   RRRR      A     H   H   EEEEE   DDDD    RRRR     OOO    N   N
//    T     E         T     R   R    A A    H   H   E       D   D   R   R   O   O   NN  N
//    T     EEEEE     T     RRRR    AAAAA   HHHHH   EEEEE   D   D   RRRR    O   O   N N N
//    T     E         T     R   R   A   A   H   H   E       D   D   R   R   O   O   N  NN
//    T     EEEEE     T     R   R   A   A   H   H   EEEEE   DDDD    R   R    OOO    N   N

// Constructors

tetrahedron::tetrahedron()
{
	generate_vertices(1, 1);
}

tetrahedron::tetrahedron(float scale)
{
	if (tolerance(scale, 0))
	{
		rename_shape("VERTEX");
		return;
	}

	generate_vertices(scale, scale);
}

tetrahedron::tetrahedron(float scale_xy, float scale_z)
{
	if (tolerance(scale_xy, 0) || tolerance(scale_z, 0))
	{
		rename_shape("VERTEX");
		return;
	}

	generate_vertices(scale_xy, scale_z);
}

// Helper

void tetrahedron::generate_vertices(float scale_xy, float scale_z)
{
	rename_shape("TETRAHEDRON");

	float scale_factor_xy = (sqrt(8.0) / 3.0) * scale_xy;
	float shift_factor = scale_xy / 3.0;

	for (int i = 0; i < 3; i++)
	{
		add_vertex(0, scale_factor_xy, 0);
		rotate_z(120);
	}

	for (vertex* v : shape_points)
	{
		v->shift_z(-shift_factor);
	}

	add_vertex(0, 0, scale_z);
}