#ifndef HOOKS_H
# define HOOKS_H

# include <stdbool.h>

typedef struct s_pressed_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
}		t_pressed_keys;

enum e_x11_events
{
	X11_KEY_PRESS = 2,
	X11_KEY_RELEASE = 3,
	X11_BUTTON_PRESS = 4,
	X11_BUTTON_RELEASE = 5,
	X11_MOTION_NOTIFY = 6,
	X11_DESTROY_NOTIFY = 17,
	X11_CONFIGURE_NOTIFY = 22
};

enum e_x11_masks
{
	X11_KEY_PRESS_MASK			= 1L << 0,
	X11_KEY_RELEASE_MASK		= 1L << 1,
	X11_BUTTON_PRESS_MASK		= 1L << 2,
	X11_BUTTON_RELEASE_MASK		= 1L << 3,
	X11_Button1MotionMask		= 1L << 8,
	X11_Button3MotionMask		= 1L << 10,
	X11_ButtonMotionMask		= 1L<<13,
	X11_STRUCTURE_NOTIFY_MASK	= 1L << 17,
};

typedef struct s_app	t_app;

void	set_hooks(t_app *app);

int		key_release_hook(int key_code, t_app *app);
int		key_press_hook(int key_code, t_app *app);

#endif  // HOOKS_H
