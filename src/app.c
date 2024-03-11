#include "cub3d.h"
#include "mlx.h"
#include "render/render.h"

void app_init(t_app *app, int ac, char *av[])
{
	cub_init(&app->cube, ac, av);
    graphics_init(&app->gr);
}

void app_destroy(t_app *app)
{
	cub_destroy(&app->cube);
	graphics_destroy(&app->gr);
}

void render(t_app *app)
{

}

int main_loop(void *data)
{
	t_app *app;

    // time now
	app = (t_app *)data;
    render_minimap(app);
    render_scene(app);
    // usleep till now + 1sec/60
    return 0;
}

void set_up_event_hooks()
{

}

int main(int ac, char *av[])
{
	t_app app;

	app_init(&app, ac, av);
    set_up_event_hooks(&app);
	mlx_loop_hook(app.gr.mlx, main_loop, &app);
	mlx_loop(app.gr.mlx);
	app_destroy(&app);
}
