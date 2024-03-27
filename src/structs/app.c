#include "app.h"
#include "mlx.h"
#include "scene_description/scene_description.h"

int	app_init(t_app *app, char *cub_path)
{
	t_sprite_sources	sources;

	ft_bzero(app, sizeof(t_app));
	app->mlx = mlx_init();
	if (!app->mlx)
		return (!SUCCESS);
	if (game_init(&app->game_state) != SUCCESS)
		return (FAILURE);
	if (read_scene_description(app, cub_path, &sources) != SUCCESS)
		return (game_destroy(&app->game_state), FAILURE);
	graphics_init(app->mlx, &app->gr);
	return (SUCCESS);
}

void	app_destroy(t_app *app)
{
	game_destroy(&app->game_state);
	graphics_destroy(app->mlx, &app->gr);
	free(app->mlx);
}
