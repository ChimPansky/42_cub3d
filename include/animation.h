#ifndef ANIMATION_H
# define ANIMATION_H

# include "image.h"

typedef struct s_animation
{
	t_image	*sprites;
	t_pixel	one_sprite_size;
	int		sprites_num;
	int		frames_per_sprite;
	int		frames_since_start;
	bool	play;
}		t_animation;

void init_leg_animation(t_animation *leg, t_image *sprites);

#endif  // ANIMATION_H
