#include "cub3d.h"


void cub_init(t_cube *cub, int ac, char *av[])
{
	if (!ac)
		(void)av;
	(void)cub;
}

void cub_destroy(t_cube *cub)
{
	(void)cub;
}

// int main(int ac, char *av[])
// {
// 	t_cube cub;

// 	cub_init(&cub, ac, av);
// 	printf("THIS IS THE MAIN");
// 	cub_destroy(&cub);
// }
