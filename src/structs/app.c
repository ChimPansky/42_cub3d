#include "app.h"
#include "mlx.h"
#include "input_parsing/input_parsing.h"

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
