#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft/libft.h"

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */

# define SWIDTH 1280		// Screen width
# define SHEIGHT 720		// Screen height
# define BLOCK 64			// Block size of player
# define TILE 24			// Tile size minimap (24x24)
# define MINIMAP_SCALE 0.5
# define MINIMAP_X 10
# define MINIMAP_Y 10

# define W 119				// W key
# define S 115				// S key
# define A 97				// A key
# define D 100				// D key

# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307

# define PI 3.14159265359

/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef struct s_map
{
	char	**grid;
	int		m_width;
	int		m_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_map;

typedef struct s_config
{
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	int		floor_color;
	int		ceiling_color;
}			t_config;

// Image struct
typedef struct s_image
{
	void	*img;
	int		size_line;
	char	*data;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_key
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	l_arrow;
	bool	r_arrow;
}			t_key;

// Player struct
typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	t_key	key;
}			t_player;

// Main struct
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_config	config;
	t_image		image;
	t_player	player;
}				t_game;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// initializer
void	init_game(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
int		draw_loop(t_game *game);
void	clear_image(t_game *game);
void	draw_map(t_game *game);


// keys
int		key_press(int keycode, t_player *player);
int		key_realease(int keycode, t_player *player);

// player
void	init_player(t_player *player);
void	move_player(t_player *player);
void	draw_square(int x, int y, int size, int color ,t_game *game);

// Parsing
int		print_error(char *msg);
int		parse_file(char *filename);

// Minimap
void	draw_tile(t_game *game, int x, int y, int color);
void	draw_minimap(t_game *game);

#endif