/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:48:28 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:48:52 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"
#include "image.h"
#include "libft.h"
#include "utils.h"

int	add_sprite_img(void *mlx, t_sprites *sprites,
	int sprite_type, char *img_path)
{
	t_image	*sprite_ptr;

	sprite_ptr = &sprites->array[sprite_type];
	if (sprite_ptr->image != NULL)
		return (print_error("Found duplicate texture: ", img_path));
	if (image_init_from_xpm(mlx, sprite_ptr, img_path) == NULL)
		return (print_error("image_init_from_xpm failed: ", img_path),
			FAILURE);
	return (SUCCESS);
}

void	sprites_destroy(void *mlx, t_sprites *sprites)
{
	int	i;

	i = 0;
	while (i < MAX_SPRITE)
		image_destroy(mlx, &sprites->array[i++]);
}

int	load_native_sprites(void *mlx, t_sprites *sprites)
{
	if (add_sprite_img(mlx, sprites, MINIMAP_CURSOR, MINIMAP_CURSOR_PATH)
		!= SUCCESS)
		return (!SUCCESS);
	if (add_sprite_img(mlx, sprites, DOOR_SPRITE, DOOR_SPRITE_PATH) != SUCCESS)
		return (!SUCCESS);
	if (add_sprite_img(mlx, sprites, LEG_ANIMATION, LEG_ANIMATION_PATH)
		!= SUCCESS)
		return (!SUCCESS);
	return (SUCCESS);
}
