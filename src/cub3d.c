#include "cub3d.h"

void cub_init(t_cube *cub, int ac, char *av[])
{
	ft_bzero(cub, sizeof(t_cube));
	if (ac < 2)
		error_exit(cub, "Please provide a scene description "
			"as parameter (.cub file).", FAILURE);
	read_scene_description(cub, av[1]);
	cub->done = false;
}

int main(int ac, char *av[])
{
	t_cube cub;

	cub_init(&cub, ac, av);
	while (!cub.done)
	{

	}
	cub_destroy(&cub);
}
