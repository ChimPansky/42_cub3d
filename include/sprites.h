#ifndef SPRITES_H
# define SPRITES_H

# include "image.h"

# define DOOR_SPRITE_PATH "resources/sprites/door.xpm"
# define MINIMAP_CURSOR_PATH "resources/sprites/coursor.xpm"
# define LEG_ANIMATION_PATH "resources/sprites/leg_sc.xpm"

typedef enum	e_sprite_types
{
	NO_SPRITE = -1,
	WALL_EA = 0,
	WALL_SO = 1,
	WALL_WE = 2,
	WALL_NO = 3,
	DOOR_SPRITE = 4,
	MINIMAP_CURSOR = 5,
	LEG_ANIMATION = 6,
	MAX_SPRITE = 7,
}		t_sprite_types;

typedef union u_sprites
{
	struct {
		t_image	wall_ea;
		t_image	wall_so;
		t_image	wall_we;
		t_image	wall_no;
		t_image	door;
		t_image	minimap_cursor;
		t_image	leg;
	};
	t_image	array[MAX_SPRITE];
}		t_sprites;

int		add_sprite_img(void *mlx, t_sprites *sprites,
		int sprite_type, char *img_path);
void	sprites_destroy(void *mlx, t_sprites *sprites);
int		load_native_sprites(void *mlx, t_sprites *sprites);

#endif  // SPRITES_H
