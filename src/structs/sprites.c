#include "sprites.h"
#include "image.h"
#include "mlx.h"
#include "libft.h"

// TODO: print_error("Found duplicate wall element in "
//				"scene description.")
// TODO: error loading xpm
int	sprites_load_one(void *mlx, t_sprites *sprites, char *xpm_path, enum e_sprite_types sprite_type)
{
	t_image	*sprite;

	sprite = &sprites->walls[sprite_type];
	if (sprite->image != NULL)
		return (!SUCCESS);
	if (image_init_from_xpm(mlx, sprite, xpm_path) == NULL)
		return (!SUCCESS);
	return (SUCCESS);
}

void	sprites_destroy(void *mlx, t_sprites *sprites)
{
	if (sprites->wall_no.image)
		mlx_destroy_image(mlx, sprites->wall_no.image);
	if (sprites->wall_so.image)
		mlx_destroy_image(mlx, sprites->wall_so.image);
	if (sprites->wall_we.image)
		mlx_destroy_image(mlx, sprites->wall_we.image);
	if (sprites->wall_ea.image)
		mlx_destroy_image(mlx, sprites->wall_ea.image);
}
