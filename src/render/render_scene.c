/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/20 12:35:26 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "structs/app.h"
#include "structs/image.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/trgb.h"
#include "vector/vector.h"
#include "structs/sprites.h"
#include <math.h>
#include "structs/ray.h"

static void		draw_screen_column(
					t_image *screen_img,
					t_static_graphics *sprites,
					t_pixel window_pixel,
					t_ray *player_view);
static t_trgb	get_color_from_sprites(
					t_static_graphics *stat_gr,
					t_ray *ray, double relative_y);

static t_trgb	get_color_from_picture(
					t_static_graphics *stat_gr,
					t_ray_collision *collision,
					double relative_y,
					double scaled_wall_h)
{
	t_image	*sprite_img;
	t_pixel	sprite_pixel;
	double	relative_x;

	sprite_img = &stat_gr->sprites.array[collision->sprite];
	relative_x = 0.0;
	if (collision->direction == COLL_EA)
		relative_x = collision->point.y - floor(collision->point.y);
	else if (collision->direction == COLL_SO)
		relative_x = 1 - (collision->point.x - floor(collision->point.x));
	else if (collision->direction == COLL_WE)
		relative_x = 1 - (collision->point.y - floor(collision->point.y));
	else if (collision->direction == COLL_NO)
		relative_x = collision->point.x - floor(collision->point.x);
	sprite_pixel.x = relative_x * sprite_img->width;
	sprite_pixel.y = ((relative_y - (1.0 - scaled_wall_h) / 2) / scaled_wall_h)
		* sprite_img->height;
	return (image_get_pixel_color(sprite_img, &sprite_pixel));
}

// relative_y: ]0.0, 1.0[; 0.0: top of screen, 1.0: bottom]
// scaled_wall_height: the further from the wall, the lower the wall
// using 1/cos to remove fish eye effect, that means
// making sure that all walls that have the same orthogonal
// distance from the player have the same height on screen
// (even though their actual distance might be further away)
static t_trgb	get_color_from_sprites(t_static_graphics *stat_gr,
		t_ray *ray, double relative_y)
{
	double	scaled_wall_height;

	scaled_wall_height = (1.0 / ray->raycaster.collision.distance)
		* WALL_HEIGHT
		* (1.0 / cos(fabs(ray->vec.phi - ray->raycaster.fov_center_angle)));
	if (relative_y < (1.0 - scaled_wall_height) / 2)
		return (stat_gr->ceiling_col);
	if (relative_y > scaled_wall_height + (1.0 - scaled_wall_height) / 2)
		return (stat_gr->floor_col);
	if (ray->raycaster.collision.sprite == NO_SPRITE)
		return (trgb(0, 0, 255, 0));
	return (get_color_from_picture(
			stat_gr,
			&ray->raycaster.collision,
			relative_y,
			scaled_wall_height));
}

static void	draw_screen_column(t_image *screen_img, t_static_graphics *sprites,
	t_pixel window_pixel, t_ray *player_view)
{
	t_trgb	color;

	window_pixel.y = 0;
	while (window_pixel.y < screen_img->height)
	{
		color = get_color_from_sprites(sprites, player_view,
				(double)window_pixel.y / screen_img->height);
		image_put_pixel(screen_img, window_pixel, color);
		window_pixel.y++;
	}
}

void animation_put_to_image(t_image *dest, t_pixel insert_pos, t_animation *anim)
{
	const int		idx = anim->frames_since_start++ / anim->frames_per_sprite;
	const t_pixel	start = pixel(anim->one_sprite_size.x * idx, 0);
	const t_pixel	end = pixel(anim->one_sprite_size.x * (idx + 1), anim->one_sprite_size.y);

	if (idx >= anim->sprites_num)
	{
		anim->frames_since_start = 0;
		anim->play = false;
		return ;
	}
	image_put_to_image(dest, anim->sprites, insert_pos, start, end);
}

void	render_leg(t_image *scene_image, t_animation *leg)
{
	const t_pixel	insert_pos
		= pixel((scene_image->width - leg->one_sprite_size.x) / 2,
				scene_image->height - leg->one_sprite_size.y);
	animation_put_to_image(scene_image, insert_pos, leg);
}

void	render_scene(t_app *app)
{
	t_pixel			window_pixel;
	t_ray			player_view;

	window_pixel.x = 0;
	window_pixel.y = 0;
	ft_bzero(&player_view, sizeof(t_ray));
	player_view.origin = app->game_state.player.pos;
	player_view.vec = pvector(1.0, app->game_state.player.angle - FOV / 2);
	player_view.raycaster.fov_center_angle = app->game_state.player.angle;
	while (window_pixel.x < app->gr.scene.width)
	{
		calculate_ray_collision(&player_view, &app->game_state.map);
		draw_screen_column(&app->gr.scene, &app->static_gr, window_pixel, &player_view);
		pvector_rotate(&player_view.vec, FOV / app->gr.scene.width);
		window_pixel.x++;
	}
	if (app->gr.leg.play)
		render_leg(&app->gr.scene, &app->gr.leg);
}
