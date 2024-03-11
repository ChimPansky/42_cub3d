#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "mlx_utils.h"

#define APP_W 640
#define APP_H 480

// minimap offset and size
#define MM_X 20
#define MM_Y 20
#define MM_W 100
#define MM_H 75
#define MM_PIXEL_PER_FIELD 5.

#define MM_WALL_COL 0xFFFFFFFF
#define MM_PATH_COL 0x00000000
#define MM_PLAYER_COL 0x00FF0000

typedef struct	s_graph {
	void	*mlx;
	void	*win;
    t_image minimap;
    t_image scene;
}				t_graph;

void    graphics_init(t_graph *gr);
void    graphics_destroy(t_graph *gr);

#endif  // GRAPHICS_H