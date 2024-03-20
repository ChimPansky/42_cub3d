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
	t_pvector	pvec;

	pvec = coords_to_pvector(-1, 0);

	pvector_print(pvec);
	//printf("vector_len(v2): %f\n", vector_len(v2));
	//printf("add_angles(M_PI, 4 * M_PI / 2): %f\n", add_angles(M_PI, 7.3333 * M_PI));
	//vector_print(vector_rotate(v2, 1.5 * M_PI));
	//vector_print(v3);
	return (0);
}
