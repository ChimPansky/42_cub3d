#include "libft/libft.h"
#include "src/cub3d.h"
#include <stdbool.h>
#include "src/structs/vector.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac < 2)
		(void)av;
	//t_vector	v1 = {.x = 4.0, .y = 3.0};
	t_vector	v1;
	t_vector	v2;
	t_vector	v3;

	v1 = vector(-5.9802, 2143.30);
	v3 = vector(0.0, 0.0);
	v2 = vector_add(v1, v3);
	vector_print(v2);
	//printf("vector_len(v2): %f\n", vector_len(v2));
	//printf("add_angles(M_PI, 4 * M_PI / 2): %f\n", add_angles(M_PI, 7.3333 * M_PI));
	//vector_print(vector_rotate(v2, 1.5 * M_PI));
	v2 = vector_normalize(v2);
	vector_print(v2);
	printf("get_vec_len(v2): %f\n", get_vec_len(v2));
	//vector_print(v3);
	return (0);
}
