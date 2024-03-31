#ifndef SPRITES_H
# define SPRITES_H

# include "image.h"

enum	e_sprite_types
{
	WALL_NO = 0,
	WALL_SO = 1,
	WALL_EA = 2,
	WALL_WE = 3,
};

typedef union u_sprites
{
	struct {
		t_image	wall_no;
		t_image	wall_so;
		t_image	wall_ea;
		t_image	wall_we;
	};
	t_image	walls[4];
}		t_sprites;

void	sprites_destroy(void *mlx, t_sprites *sprites);

#endif  // SPRITES_H
