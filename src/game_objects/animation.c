#include "animation.h"

void init_leg_animation(t_animation *leg, t_image *sprites)
{
	leg->play = false;
	leg->frames_since_start = 0;
	leg->sprites_num = 3;
	leg->sprites = sprites;
	leg->one_sprite_size = pixel(400, 400);
	leg->frames_per_sprite = 3;
}
