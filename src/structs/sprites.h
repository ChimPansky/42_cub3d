#ifndef SPRITES_H
# define SPRITES_H

# include "image.h"

//#define DOOR_SPRITE_PATH "textures/door.xpm"
#define DOOR_SPRITE_PATH "sprites/door.xpm"

typedef enum	e_sprite_types
{
	NO_SPRITE = 99,
	WALL_EA = 0,
	WALL_SO = 1,
	WALL_WE = 2,
	WALL_NO = 3,
	DOOR_SPRITE = 4,
}		t_sprite_types;

typedef union u_sprites
{
	struct {
		t_image	wall_ea;
		t_image	wall_so;
		t_image	wall_we;
		t_image	wall_no;
		t_image	door;
	};
	t_image	images[5];
}		t_sprites;

int		add_sprite_img(void *mlx, t_sprites *sprites,
		int sprite_type, char *img_path);
void	sprites_destroy(void *mlx, t_sprites *sprites);

#endif  // SPRITES_H
