#include "app.h"
#include "mlx.h"
#include "input_parsing/input_parsing.h"
#include "utils.h"
#include "sprites.h"

#include <stdio.h>
int	app_init(t_app *app, char *cub_path)
{
	ft_bzero(app, sizeof(t_app));
	app->mlx = mlx_init();
	if (!app->mlx)
		return (!SUCCESS);
	if (game_init(&app->game_state) != SUCCESS)
		return (FAILURE);
	if (read_scene_description(app, cub_path) != SUCCESS)
		return (game_destroy(&app->game_state), FAILURE);
	printf("imageptr: %p\n", app->static_gr.sprites.wall_ea.image);
	printf("imageptr: %p\n", app->static_gr.sprites.wall_so.image);
	printf("imageptr: %p\n", app->static_gr.sprites.wall_we.image);
	printf("imageptr: %p\n", app->static_gr.sprites.wall_no.image);
	printf("imageptr: %p\n", app->static_gr.sprites.door.image);
	if (image_init_from_xpm(app->mlx, &app->static_gr.sprites.door,
		SPRITE_DOOR_PATH) == NULL)
		return (print_error("image_init_from_xpm: DOOR failed"), FAILURE);
	doors_print(app->game_state.doors);
	graphics_init(app->mlx, &app->gr);
	return (SUCCESS);
}

void	app_destroy(t_app *app)
{
	game_destroy(&app->game_state);
	graphics_destroy(app->mlx, &app->gr);
	free(app->mlx);
}
