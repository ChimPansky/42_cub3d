#include "cub3d.h"
#include "mlx.h"
#include "render/render.h"
#include "logic/logic.h"
#include <unistd.h>
#include <time.h>
#include "logic/game.h"
#include "scene_description/scene_description.h"

// 1000/60 = 16.6666
#define MSEC_PER_FRAME 16

static int	app_init(t_app *app, char *cub_path)
{
	ft_bzero(app, sizeof(t_app));
	if (game_init(&app->game_state) != SUCCESS)
		return (FAILURE);
	t_sprite_sources sources;
	if (read_scene_description(app, cub_path, &sources) != SUCCESS)
		return (game_destroy(&app->game_state), FAILURE);
	graphics_init(&app->gr);
	return (SUCCESS);
}

void	app_destroy(t_app *app)
{
	game_destroy(&app->game_state);
	graphics_destroy(&app->gr);
}

int	main_loop(void *data)
{
	clock_t	start_time;
	int		msec_passed;
	t_app	*app;

	start_time = clock();
	app = (t_app *)data;
	process_logic(app);
	render_scene(&app->gr.minimap, &app->game_state);
	mlx_put_image_to_window(app->gr.mlx, app->gr.win,
		app->gr.scene.image, 0, 0);
	render_minimap(&app->gr.minimap, &app->game_state);
	mlx_put_image_to_window(app->gr.mlx, app->gr.win,
		app->gr.minimap.image, MM_X, MM_Y);
	msec_passed = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
	if (msec_passed < MSEC_PER_FRAME)
		usleep((MSEC_PER_FRAME - msec_passed) * 1000);
	return (0);
}

int	main(int ac, char *av[])
{
	t_app	app;

	if (ac < 2)
		return (print_error("Please provide a scene description "
			"as parameter (.cub file)."), FAILURE);
	if (ac > 2)
		return (print_error("Too many arguments!"), FAILURE);
	if (app_init(&app, av[1]) != SUCCESS)
		return (FAILURE);
	mlx_loop_hook(app.gr.mlx, main_loop, &app);
	set_hooks(&app);
	mlx_loop(app.gr.mlx);
	app_destroy(&app);
}
