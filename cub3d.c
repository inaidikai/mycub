/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/10 10:33:41 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
int invisible_yes_no(char c)
{
    if(c == 32 || (c >= 9 && c<=13))
        return (1);
    return 0;
}
void ft_free_pp(void **argv)
{
    int i;
    i = 0;
    while(argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void	init_color(int *color, char *element)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(element, ',');
	if (*temp)
	{
		r = atoi(temp[0]);
		g = atoi(temp[1]);
		b = atoi(temp[2]);
		ft_free_pp((void **)temp);
		if (r <= 255 && r >= 0 && g <= 255 && g >= 0 && b <= 255 && b >= 0)
		{
			*color = 65536 * r + 256 * g + b;
			return ;
		}		
	}
	 exit(perror_cube3d("colour invalid", 0));
}

void	init_texture(t_vars *vars, t_texture *txt, char *element, int val)
{
	txt->img = mlx_xpm_file_to_image(vars->mlx, element,
			&txt->width, &txt->height);
	if (!txt->img)
		exit(perror_cube3d("texture invalid", 0));
	txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
			&txt->line_length, &txt->endian);
	txt->pix_y = 0;
	txt->pix_x = 0;
	txt->txt = val;
}
t_img	*ft_t_img(void)
{
	static t_img			img;
	static t_texture		no;
	static t_texture		so;
	static t_texture		we;
	static t_texture		ea;

	if (!img.init)
	{
		img.no = &no;
		img.so = &so;
		img.we = &we;
		img.ea = &ea;
		img.f = 0;
		img.c = 0;
		img.init = 1;
	}
	return (&img);
}
static int	init_element(char *element, int val)
{
	if (element && val == NO)
		init_texture(ft_t_vars(), ft_t_img()->no, element, val);
	else if (element && val == SO)
		init_texture(ft_t_vars(), ft_t_img()->so, element, val);
	else if (element && val == WE)
		init_texture(ft_t_vars(), ft_t_img()->we, element, val);
	else if (element && val == EA)
		init_texture(ft_t_vars(), ft_t_img()->ea, element, val);
	else if (element && val == F)
		init_color(&ft_t_img()->f, element);
	else if (element && val == C)
		init_color(&ft_t_img()->c, element);
	else
		return (0);
	return (1);
}

int val_chk(t_img *img, char *temp)
{
    if(!*temp)
        return 0;
    if(strncmp(temp, "NO", 2) == 0 && !img->no->img )
        return(NO);
    if(strncmp(temp, "SO", 2) == 0 && !img->so->img )
        return(SO);
    if(strncmp(temp, "WE", 2) == 0 && !img->we->img )
        return(WE);
    if(strncmp(temp, "EA", 2) == 0 && !img->ea->img )
        return(EA);
    if(strncmp(temp, "F", 2) == 0 && !img->f )
        return(F);
    if(strncmp(temp, "C", 2) == 0 && !img->c )
        return(C);
    return 0;
}
int find_element(char *element, int fd)
{
    int val;
    int i;
    i = 0;
    val = 0;
    while(*element && invisible_yes_no(*element) )
        element++;
    val = val_chk(ft_t_img(), element);
    if(val > 0)
    {
        element++;
        if(val < 5)
            element++;
        while(invisible_yes_no(*element))
            element++;
        while(element[i] && !invisible_yes_no(element[i]))
            i++;
        element[i] = '\0';
        if(init_element(element , val))
            return (1);
        close (fd);
        exit(perror_cube3d("element not found", 0));
    }
    return 0;
}
void element_hunter(char *ca)
{
    int     i;
    char    *temp;
        i = 6;
    int		fd;

	fd = open(ca, O_RDONLY);
	if (fd < 0)
    {
       perror_cube3d("Wrong path of the map ", 1);
    }
    temp = get_next_line(fd);
    while(i && temp)
    {
        i-= find_element(temp, fd);
        free(temp);
        temp = get_next_line(fd);
    }
    if(temp)
        free(temp);
    if(i != 0)
    {
        close(fd);
        exit(perror_cube3d("missing element", 0));
    }
}
int fill(t_map *map, char *c)
{
    int fd;
    char *line;
    size_t width;
    int height;

    fd = open(c, O_RDONLY);
    if(fd < 0)
        printf("sSs");

    line =  get_next_line(fd);
    width = ft_strlen(line);
    height = 0;
     printf("%s", line);
    while(line)
    {
        printf("%s", line);
        free(line);
 
        line = get_next_line(fd);
        printf("%s", line);
        height++;
    }
    close(fd);
    map->height = height;
    return(width);
}
void store (t_map *map, char *c)
{
    int fd;
    int i;
    char *line;
    map->width = fill(map, c);
    fd = open(c, O_RDONLY);
    if(fd<0)
        printf("error");
   
    map->map = (char **)malloc(sizeof(char *) * map->width);
    if(map->map == NULL)
    {
        exit(1);
    }
    line = get_next_line(fd);
    i = 0;
    while(line)
    {
        map->map[i] = line;
        line = get_next_line(fd);
        i++;
    }
    map->map[i] = NULL;
    close(fd);
    // parse(map, *map);
}

char cube3d(char *c)
{
    t_map map;
    element_hunter(c);
    store(&map , c);
    if(!path_struct(&map))
    {
        exit(perror_cube3d("map invalid", 0));
    }
    return 0;
}