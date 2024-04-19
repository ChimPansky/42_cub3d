#ifndef SPRITES_H
# define SPRITES_H

# include "image.h"

#define SPRITE_DOOR_PATH "textures/door.xpm"

typedef enum	e_sprite_types
{
	NO_SPRITE = 0,
	WALL_EA = 1,
	WALL_SO = 2,
	WALL_WE = 3,
	WALL_NO = 4,
	DOOR_SPRITE = 5,
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
	t_image	walls[5];
}		t_sprites;

#endif  // SPRITES_H
