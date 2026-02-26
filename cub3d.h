#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
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

# define SWIDTH 1920		// Screen width
# define SHEIGHT 1080		// Screen height


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

// Main struct
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_config	config;
	t_image		image;
}				t_game;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// initializer
void	init_game(t_game *game);


// Parsing
int		print_error(char *msg);
int		parse_file(char *filename);


#endif