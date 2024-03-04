#include "cub3d.h"


void cub_init(t_cube *cub, int ac, char *av[])
{
	if (!ac)
		(void)av;
	cub->done = false;

}

void cub_destroy(t_cube *cub)
{
	(void)cub;
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
