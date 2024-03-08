#include "cub3d.h"

void	print_textures(t_textures textures)	//TODO: remove
{
	ft_printf("WALL_no: %s\n", textures.wall_no);
	ft_printf("WALL_so: %s\n", textures.wall_so);
	ft_printf("WALL_we: %s\n", textures.wall_we);
	ft_printf("WALL_ea: %s\n", textures.wall_ea);

	printf("floor: %d\n", textures.floor);
	printf("ceiling: %d\n", textures.ceiling);
}

void	print_player(t_player player)	//TODO: remove
{
	printf("Player x: %f\n", player.pos.x);
	printf("Player y: %f\n", player.pos.y);
	printf("Player angle: %f\n", player.angle);
	printf("Player speed x: %f\n", player.speed.x);
	printf("Player speed y: %f\n", player.speed.y);
}

void	charptr_array_print(t_charptr_array *arr)	//TODO: remove
{
	size_t	i;

	i = 0;
	if (!arr)
	{
		ft_printf("{NULL}");
		return ;
	}
	if (arr->sz == 0)
	{
		ft_printf("{EMPTY}");
		return ;
	}
	while (i < arr->sz)
		ft_printf("%s\n", arr->buf[i++]);
}

void cub_init(t_cube *cub, int ac, char *av[])
{
	ft_bzero(cub, sizeof(t_cube));
	cub->player.pos.x = -1.0;
	cub->player.pos.y = -1.0;
	if (charptr_array_init(&cub->map.raw_map) != SUCCESS)
	{
		perror("cub_init: charptr_array_init");
		error_exit(cub, FAILURE);
	}
	if (ac < 2)
	{
		print_error("Please provide a scene description "
			"as parameter (.cub file).");
		error_exit(cub, FAILURE);
	}
	read_scene_description(cub, av[1]);
	cub->done = false;
}

int main(int ac, char *av[])
{
	t_cube cub;

	cub_init(&cub, ac, av);
	while (!cub.done)
	{
		printf("in game loop\n");
		usleep(1000000);
	}
	cub_destroy(&cub);
}
