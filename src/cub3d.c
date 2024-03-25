// 1000/60 = 16.6666
#define MSEC_PER_FRAME 16

#define COLOR_RESET "\033[0;39m"
#define COLOR_RED "\033[0;91m"
#define COLOR_GREEN "\033[0;92m"
#define COLOR_YELLOW "\033[0;93m"

#include "libft.h"
#include "structs/app.h"
#include "scene_description/scene_description.h"
#include "render/render.h"
#include "logic/logic.h"
#include "hooks/hooks.h"
#include <time.h>

int	print_error(char *err_msg)
{
	ft_dprintf(STDERR_FILENO, COLOR_RED);
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		ft_dprintf(STDERR_FILENO, "Unknown Error\n");
	ft_dprintf(STDERR_FILENO, COLOR_RESET);
	return (FAILURE);
}

// TODO mlx_put_image_to_window inside render?
int	main_loop(void *data)
{
	clock_t	start_time;
	int		msec_passed;
	t_app	*app;

	start_time = clock();
	app = (t_app *)data;
	process_inputs(&app->game_state, &app->inputs);
	change_state_for_next_frame(&app->game_state);
	render_scene(&app->gr.scene, &app->game_state);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.scene.image, 0, 0);
	render_minimap(&app->gr.minimap, &app->game_state);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.minimap.image.image, MM_X, MM_Y);
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
	set_hooks(&app);
	mlx_loop_hook(app.mlx, main_loop, &app);
	mlx_loop(app.mlx);
	app_destroy(&app);
}
