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
//# include "minilibx-linux/mlx.h"
//# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */

# define FORM_ERR "Invalid file format"
# define TEXT_EXT "Invalid texture extension"
# define MISS_TEXT "Wall texture file doesn't exist or is inaccessible"
# define DBL_TEXT "Double definition of wall texture"
# define DBL_COLOR "Double definition of color"
# define ALL_ERR "Allocation error"
# define RGB_ERR "Invalid RGB range or format"
# define TYP_ERR "Invalid identifier"
# define MAP_ERR "Invalid map format"
# define M_TYP_ERR "Invalid map character"
# define DBL_PLAYER "Double definition of player spawn point"

/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef enum e_token
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	MAP,
	ERROR,
}	t_token;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
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


// Main struct
typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			fd;
	t_map		map;
	t_config	config;
}		t_game;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// Parsing
void	print_error(char *msg);
int		check_ext(char *filename, char *ext);
int		parse_file(t_game *game, char *filename);
int		skipwhitespace(char *str, int pos);
int		count_elems(char const *s);
t_token	find_token_type(char *line);
int		parse_color_code(char *color, int *i);
char	*buildline(char *s1, char *s2);
void	extract_data(t_game *game);
int		check_config(t_game *game);
void	clean_map(char **map);
int		normalize_map(t_map *map);
int		validate_map(t_map *map);

#endif