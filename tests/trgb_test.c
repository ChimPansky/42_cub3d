#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

# define FLOOR_CEILING_TRANSPARENCY 50

typedef unsigned int	t_trgb;

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

int	print_error(char *err_msg)
{
	dprintf(STDERR_FILENO, "Error\n");
	if (err_msg)
		dprintf(STDERR_FILENO, "%s\n", err_msg);
	return (FAILURE);
}

t_trgb	trgb_create(int t, int r, int g, int b)
{
	t_trgb	color;

	color = 0;
	color |= t << 24;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

int	get_t_from_trgb(t_trgb color)
{
	return ((color >> 24) & 255);
}

int	get_r_from_trgb(t_trgb color)
{
	return ((color >> 16) & 255);
}

int	get_g_from_trgb(t_trgb color)
{
	return ((color >> 8) & 255);
}

int	get_b_from_trgb(t_trgb color)
{
	return (color & 255);
}

static int	get_next_rgb_val(char **str, int *rgb_val)
{
	*rgb_val = 0;
	skip_spaces(str);
	if (**str == '\0' || **str == ',')
		return (print_error("Scene description: Found incomplete RGB value"));
	while (**str != '\0' && **str != ' ' && **str != ',')
	{
		if (**str < '0' || **str > '9')
			return (print_error("Scene description: "
				"RGB values can only contain digits."));
		*rgb_val = *rgb_val * 10 + **str - '0';
		(*str)++;
		if (*rgb_val > 255)
			return (print_error("Scene description: "
				"RGB values must be between 0 and 255."));
	}
	skip_spaces(str);
	return (SUCCESS);
}

int	extract_trgb_from_line(char **str, t_trgb *trgb)
{
	int	rgb[4];
	int	i;

	rgb[0] = FLOOR_CEILING_TRANSPARENCY;
	i = 1;
	while (i < 4)
	{
		if (get_next_rgb_val(str, rgb + i) != SUCCESS)
			return (FAILURE);
		if (i < 3)
		{
			if (**str != ',')
				return (print_error("RGB values in scene description "
					"must be separated by commas."));
			(*str)++;
		}
		i++;
	}
	*trgb = trgb_create(rgb[0], rgb[1], rgb[2], rgb[3]);
	return (SUCCESS);
}

void	print_trgb(t_trgb color)
{
	printf("t: %d; r: %d; g: %d; b: %d\n",
		(int)get_t_from_trgb(color),
		(int)get_r_from_trgb(color),
		(int)get_g_from_trgb(color),
		(int)get_b_from_trgb(color));
}


int	main(int ac, char **av)
{
	t_trgb	color;
	char *test;

	test = "100, 78, 230";

	if (ac < 2)
		return (0);
	if (extract_trgb_from_line(&av[1], &color) != SUCCESS)
		return (1);
	print_trgb(color);
	return (0);
}
