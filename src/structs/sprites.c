#include "sprites.h"
#include "image.h"
#include "mlx.h"
#include "libft.h"
#include "utils.h"

int	add_sprite_img(void *mlx, t_sprites *sprites,
	int sprite_type, char *img_path)
{
	t_image	*sprite_ptr;

	sprite_ptr = &sprites->images[sprite_type];
	if (sprite_ptr->image != NULL)
		return (print_error("Found duplicate texture: ", img_path));
	if (image_init_from_xpm(mlx, sprite_ptr, img_path) == NULL)
		return (print_error("image_init_from_xpm failed: ", img_path),
			FAILURE);
	return (SUCCESS);
}

void	sprites_destroy(void *mlx, t_sprites *sprites)
{
	if (sprites->wall_ea.image)
		mlx_destroy_image(mlx, sprites->wall_ea.image);
	if (sprites->wall_so.image)
		mlx_destroy_image(mlx, sprites->wall_so.image);
	if (sprites->wall_we.image)
		mlx_destroy_image(mlx, sprites->wall_we.image);
	if (sprites->wall_no.image)
		mlx_destroy_image(mlx, sprites->wall_no.image);
	if (sprites->door.image)
		mlx_destroy_image(mlx, sprites->door.image);
}
