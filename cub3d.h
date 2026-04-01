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
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
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
# define MOVE_SPEED 2.2f	// Player movement speed
# define ROT_SPEED 0.06f	// Player rotation speed

# define W 119				// W key
# define S 115				// S key
# define A 97				// A key
# define D 100				// D key

# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307

# define PI 3.14159265359
# include "libft/get_next_line/get_next_line.h"

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
# define MISS_PLAYER "Missing player spawn point definition"

/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef enum e_token
{
	NO,
	SO,
	WE,
	EA,
	DIR_COUNT,
	F,
	C,
	MAP,
	ERROR,
}	t_token;

typedef struct s_map
{
	char	**grid;
	int		m_width;
	int		m_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}			t_map;

// ray struct
typedef struct s_rays
{
	float	dir_x;
	float	dir_y;
	float	delta_x;
	float	delta_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		wall_dir;
}			t_rays;

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

// sprite struct
typedef struct s_tex
{
	char	*path[DIR_COUNT];
	t_image	img[DIR_COUNT];
	int		floor_color;
	int		ceiling_color;
}			t_tex;

// Minimap struct
typedef struct s_minimap
{
	int	x;
	int	y;
	int	t_size;
	int	width;
	int	height;
}		t_minimap;

// Key struct
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
	int			fd;
	t_map		map;
	t_tex		texture;
	t_image		image;
	t_player	player;
	t_rays		ray;
	t_minimap	mm;
}				t_game;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// initializer
void	init_game(t_game *game);
void	init_player(t_game *game);
int		draw_loop(t_game *game);
void	draw_map(t_game *game);

// free hub
void	clean_config(t_game *game);
void	clean_map(char **map);
void	clear_image(t_game *game);
int		on_destroy(t_game *game);

// keys
int		key_press(int keycode, t_game *game);
int		key_realease(int keycode, t_game *game);

// player
void	move_player(t_game *game);

// player utils
void	draw_square(int x, int y, int size, int color, t_game *game);
bool	can_move_to(t_game *game, float x, float y, float r);
float	get_spawn_angle(char dir);

// Textures
int		load_textures(t_game *game);

// Draw
void	draw_tex_colum(t_game *game, int x, int start, int end);

// Draw lines
void	draw_line(t_player *player, t_game *game, float angle, int x);
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_background(t_game *game);

// Parsing
void	print_error(char *msg);
void	init_config(t_game *game);
void	init_map(t_game *game);
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

// Minimap
void	init_minimap(t_game *game);
void	draw_tile(t_game *game, int x, int y, int color);
void	draw_minimap(t_game *game);

// Wall colision
bool	touch_wall(float px, float py, t_game *game);

// Raycasting
float	cast_ray_dda(t_game *game, float angle, int *side);

#endif