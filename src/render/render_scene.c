/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:49:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/20 14:55:24 by tkasbari         ###   ########.fr       */
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

void			render_scene(
					t_image *scene_image,
					t_static_graphics *sprites,
					t_game_state *game);
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

	sprite_img = &stat_gr->sprites.images[collision->sprite];
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

	scaled_wall_height = (1.0 / fmax(ray->raycaster.collision.distance, 1.0))
		* WALL_HEIGHT
		* (1.0 / cos(fabs(ray->vec.phi - ray->raycaster.fov_center_angle)));
	if (relative_y < (1.0 - scaled_wall_height) / 2)
		return (stat_gr->ceiling_col);
	if (relative_y > scaled_wall_height + (1.0 - scaled_wall_height) / 2)
		return (stat_gr->floor_col);
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

void	render_scene(t_image *scene_image, t_static_graphics *sprites,
t_game_state *game)
{
	t_pixel			window_pixel;
	t_ray			player_view;

	window_pixel.x = 0;
	window_pixel.y = 0;
	ft_bzero(&player_view, sizeof(t_ray));
	player_view = ray_copy(&game->player.view);
	pvector_rotate(&player_view.vec, - (FOV / 2));
	while (window_pixel.x < scene_image->width)
	{
		calculate_ray_collision(&player_view, &game->map);
		draw_screen_column(scene_image, sprites, window_pixel, &player_view);
		pvector_rotate(&player_view.vec, FOV / scene_image->width);
		window_pixel.x++;
	}
}
