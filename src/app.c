#include "cub3d.h"
#include "mlx.h"
#include "render/render.h"
#include "logic/logic.h"
#include <unistd.h>
#include <time.h>

// 1000/60 = 16.6666
#define MSEC_PER_FRAME 16

void	app_init(t_app *app, int ac, char *av[])
{
	cub_init(app, ac, av);
	graphics_init(&app->gr);
}

void	app_destroy(t_app *app)
{
	cub_destroy(app);
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
	render_scene(&app->gr.minimap, &app->cub);
	mlx_put_image_to_window(app->gr.mlx, app->gr.win,
		app->gr.scene.image, 0, 0);
	render_minimap(&app->gr.minimap, &app->cub);
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

	app_init(&app, ac, av);
	mlx_loop_hook(app.gr.mlx, main_loop, &app);
	set_hooks(&app);
	mlx_loop(app.gr.mlx);
	app_destroy(&app);
}
