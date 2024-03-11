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

void cub_init(t_cube *cub)
{



	//charptr_array_print(&cub->map.raw_map);
	//printf("\n");
	// print_textures(cub->walls_floor_ceiling);
	// printf("\n");
	// print_player(cub->player);
	// printf("\n");
	cub->done = false;
}

void	app_init(t_app *app, char *cub_path)
{
	ft_bzero(app, sizeof(t_app));
	if (charptr_array_init(app->cub->map.raw_map) != SUCCESS)
	{
		perror("cub_init: charptr_array_init");
		error_exit(app, FAILURE, NULL);
	}
	read_scene_description(&app, cub_path);

	graphics_init(&app->graphics);


}

int main(int ac, char *av[])
{
	t_app	app;

	if (ac < 2)
		return (print_error("Please provide a scene description "
			"as parameter (.cub file)."), FAILURE);
	if (ac > 2)
		return (print_error("Too many arguments!"), FAILURE);
	app_init(&app, av[1]);
	while (!cub.done)
	{
		printf("in game loop\n");
		usleep(1000000);
	}
	cub_destroy(&cub);
	return (SUCCESS);
}
