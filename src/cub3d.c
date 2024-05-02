// 1000/60 = 16.6666

#define COLOR_RESET "\033[0;39m"
#define COLOR_RED "\033[0;91m"
#define COLOR_GREEN "\033[0;92m"
#define COLOR_YELLOW "\033[0;93m"

#include "libft.h"
#include "mlx.h"
#include "structs/app.h"
#include "render/render.h"
#include "logic/logic.h"
#include "hooks/hooks.h"
#include "utils.h"
#include <time.h>
#include "cub3d.h"
//#include "log.h"


//#include "log.h"
//int g_i = 0;

#include <stdio.h>

char g_screen_info[100];	// TODO: remove

static void	print_game_info(t_app *app)
{
	char player[100];
	char phi[100];

	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 10, 0,
	"DEBUG INFO:");
	sprintf(player, "Player: %.2f, %.2f", app->game_state.player.pos.x,
		app->game_state.player.pos.y);
	sprintf(phi, "Player Phi: %.2f", fmod(app->game_state.player.angle + 2*M_PI, 2*M_PI));
	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 20, 0,
	player);
	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 30, 0,
	phi);
	mlx_string_put(app->mlx, app->gr.win, app->gr.scene.width - 150, 40, 0,
	g_screen_info);
}

int	main_loop(void *data)
{
	clock_t	start_time;
	int		msec_passed;
	t_app	*app;

	start_time = clock();
	app = (t_app *)data;
	process_inputs(&app->game_state, &app->inputs);
	change_state_for_next_frame(&app->game_state);
	render_scene(app);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.scene.image, 0, 0);
	render_minimap(&app->gr.minimap, &app->game_state);
	mlx_put_image_to_window(app->mlx, app->gr.win,
		app->gr.minimap.image.image, MM_X, MM_Y);
	print_game_info(app);
	msec_passed = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
	if (msec_passed < MSEC_PER_FRAME)
		usleep((MSEC_PER_FRAME - msec_passed) * 1000);
	return (0);
}

int	main(int ac, char *av[])
{
	t_app	app;

	#ifdef LOGGING
		int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (print_error("Failed to open log file.", NULL), FAILURE);
		dup2(fd, 1);
		dup2(fd, 2);
		close(fd);
		printf("LOGGING ENABLED\n");
	#endif
	if (ac < 2)
		return (print_error("Please provide a scene description "
				"as parameter (.cub file).", NULL), FAILURE);
	if (ac > 2)
		return (print_error("Too many arguments!", NULL), FAILURE);
	if (app_init(&app, av[1]) != SUCCESS)
		return (FAILURE);
	set_hooks(&app);
	mlx_loop_hook(app.mlx, main_loop, &app);
	mlx_loop(app.mlx);
	app_destroy(&app);
	return (SUCCESS);
}
