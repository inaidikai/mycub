#ifndef CUBE_H
#define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_vars		t_vars;
typedef struct s_map
{
    char **map;
    int width;
    int height;
}       t_map;
typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			map_y;
	int			map_x;
	int			pos; // player starting postion
	float		pos_x; // player  x position
	float		pos_y; //player y position
	int			player_side;
	int			map_on;
	int			enemy_win;
	int			end_game;
	int			steps;
	int			time;
	int			init;
	int			radian;
	int			player_angle;
	int			rotation;
	float		player_cos;
	float		player_sin;
	float		radius;
	double		speed;
}
t_vars;
typedef struct s_texture
{
		int			txt;
	void		*img;
	int			width;
	int			height;
	float		pix_x;
	float		pix_y;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

 typedef struct s_img
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	int			f;
	int			c;
	int			init;
}				t_img;

 typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	
}				t_keys;


enum	e_element
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	F = 5,
	C = 6,

};

char	*get_next_line(int fd);
size_t	ft_strlen(char const *str);
char	*ft_strchr(char const *str, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char const *src);
char	*ft_strjoin(char const *s1, char const *s2);
void ft_free_pp(void **argv);
char cube3d(char *c);
void	free_cube3d(t_vars *vars);
int	perror_cube3d(char *str, int flag);
t_vars	*ft_t_vars(void);
int path_struct(t_map *map);
#endif