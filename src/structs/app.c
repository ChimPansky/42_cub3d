#include "app.h"
#include "libft.h"
#include "mlx.h"
#include "input_parsing/input_parsing.h"
#include "sprites.h"

static void	ptr_mlx_destroy(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}

int	app_init(t_app *app, char *cub_path)
{
	ft_bzero(app, sizeof(t_app));
	app->mlx = mlx_init();
	if (!app->mlx)
		return (!SUCCESS);
	if (game_init(&app->game_state) != SUCCESS)
		return (ptr_mlx_destroy(app->mlx), FAILURE);
	if (read_scene_description(app, cub_path) != SUCCESS)
		return (game_destroy(&app->game_state),
			ptr_mlx_destroy(app->mlx), FAILURE);
	if (add_sprite_img(app->mlx, &app->static_gr.sprites, DOOR_SPRITE,
		DOOR_SPRITE_PATH) != SUCCESS
		|| graphics_init(app->mlx, &app->gr) != SUCCESS)
		return (game_destroy(&app->game_state),
			sprites_destroy(app->mlx, &app->static_gr.sprites),
			ptr_mlx_destroy(app->mlx), FAILURE);
	return (SUCCESS);
}

void	app_destroy(t_app *app)
{
	game_destroy(&app->game_state);
	sprites_destroy(app->mlx, &app->static_gr.sprites);
	graphics_destroy(app->mlx, &app->gr);
	ptr_mlx_destroy(app->mlx);
}
