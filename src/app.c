#include "cub3d.h"
#include "mlx.h"
#include "render/render.h"
#include "game_state/game_state.h"
#include "scene_description/scene_description.h"
#include <time.h>

// 1000/60 = 16.6666
#define MSEC_PER_FRAME 16

void	sprite_sources_destroy(t_sprite_sources *sprites)
{
	free(sprites->wall_no);
	free(sprites->wall_so);
	free(sprites->wall_we);
	free(sprites->wall_ea);
}

static int	app_init(t_app *app, char *cub_path)
{
	t_sprite_sources	sprites;

	ft_bzero(app, sizeof(t_app));
	if (game_init(&app->game) != SUCCESS)
		return (FAILURE);
	if (read_scene_description(app, cub_path, &sprites) != SUCCESS)
		return (game_destroy(&app->game), FAILURE);
	if (graphics_init(&app->graph, &sprites) != SUCCESS)
		return (game_destroy(&app->game), FAILURE);
	sprite_sources_destroy(&sprites);
	return (SUCCESS);
}

void	app_destroy(t_app *app)
{
	game_destroy(&app->game);
	graphics_destroy(&app->graph);
}

int	main_loop(void *data)
{
	clock_t	start_time;
	int		msec_passed;
	t_app	*app;

	start_time = clock();
	app = (t_app *)data;
	process_logic(app);
	render_scene(&app->graph.minimap, &app->game);
	mlx_put_image_to_window(app->graph.mlx, app->graph.win,
		app->graph.scene.image, 0, 0);
	render_minimap(&app->graph.minimap, &app->game);
	mlx_put_image_to_window(app->graph.mlx, app->graph.win,
		app->graph.minimap.image, MM_X, MM_Y);
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
	mlx_loop_hook(app.graph.mlx, main_loop, &app);
	set_hooks(&app);
	mlx_loop(app.graph.mlx);
	app_destroy(&app);
}
