/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:05:55 by niida             #+#    #+#             */
/*   Updated: 2025/03/02 04:01:52 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define VISITED 9
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>
#include <string.h>

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q a.out");
//}
// static void	print_map(int **map, t_grid map_size);

// static int	err(char *function_name, const char *msg)
// {
// 	ft_putendl_fd("Error", 2);
// 	ft_putstr_fd(function_name, 2);
// 	ft_putstr_fd(":\t", 2);
// 	perror(msg);
// 	return (EXIT_FAILURE);
// }
int	ft_atoi_mod(const char *str)
{
	long	result;
	long	sign;
	int		digits;

	result = 0;
	sign = 1;
	digits = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (*str >= '0' && *str <= '9' && digits++ < 19)
	{
		result = result * 10 + (*str++ - '0');
		if ((result > LONG_MAX / 10 || (result == LONG_MAX / 10 && *str > '7'))
			&& sign == 1)
			errno = ERANGE;
		if ((result > LONG_MAX / 10 || (result == LONG_MAX / 10 && *str > '8'))
			&& sign == -1)
			errno = ERANGE;
	}
	if (*str && (!(*str >= '0' && *str <= '9')))
		errno = EINVAL;
	return ((int)(sign * result));
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static int	flood_recursive(int **map, int x, int y, t_vars *vars)
{
	if (x >= vars->map_size.x || y >= vars->map_size.y || x < 0 || y < 0
		|| map[y][x] == 1 || map[y][x] == VISITED)
		return (EXIT_SUCCESS);
	if (map[y][x] == 0)
		return (err("flood_recursive", "misplaced player or floor"));
	map[y][x] = VISITED;
	if (flood_recursive(map, x + 1, y, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x - 1, y, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x, y + 1, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x, y - 1, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
instead of infill, flood from the outside. flood from 2.
if we find a 1, visited cell, or outside map boundary - success
if we find a 0, - failure
if we find a 2,
- recurse neighbouring cells until a wall is found.
- if we find a 0 - failure.
Finally, check the whole border for lefover 2
*/
static int	floodfill(int **map, t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < vars->map_size.y)
	{
		x = 0;
		while (x < vars->map_size.x)
		{
			if (map[y][x] == 2)
			{
				if (flood_recursive(map, x, y, vars) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			if (map[y][x] == 0 && (x == 0 || y == 0
				|| x == vars->map_size.x - 1 || y == vars->map_size.y - 1))
				return (err("floodfill", "misplaced player or floor"));
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
	// printf("\n---------flooded result-----------\n");
	// print_map(map, vars->map_size);
	// printf("\nMap size: (%d,%d) Current x: %d, y: %d\n",
	// 	vars->map_size.x, vars->map_size.y, x, y);

static int	fill_map(char *map_data, int **map, t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map_size.y)
	{
		x = -1;
		while (*map_data && *map_data != '\n')
		{
			++x;
			if (*map_data == '0')
				map[y][x] = 0;
			else if (*map_data == '1')
				map[y][x] = 1;
			else if (*map_data == ' ')
				map[y][x] = 2;
			else
				map[y][x] = 0;
			map_data++;
		}
		map_data++;
		while (++x < vars->map_size.x)
			map[y][x] = 2;
	}
	return (EXIT_SUCCESS);
}

static int	init_map(int ***map, int rows, int cols)
{
	int	i;

	*map = malloc(sizeof(int *) * rows);
	if (!(*map))
		return (err("init_map", "malloc failed for map rows"));
	i = 0;
	while (i < rows)
	{
		(*map)[i] = malloc(sizeof(int) * cols);
		if (!(*map)[i])
		{
			while (i > 0)
				free((*map)[--i]);
			free(*map);
			return (err("init_map", "malloc failed for map columns"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	set_player(t_vars *vars, int x, int y, char c)
{
	t_player	*p;
	t_vector2d	dirs[4];
	t_vector2d	planes[4];
	int			idx;

	p = vars->player;
	if (!(p->pos.x == 0 && p->pos.y == 0) && !(p->dir.x == 0 && p->dir.y == 0))
		return (err("load_map", "player already positioned"));
	dirs[0] = (t_vector2d){0, -1};
	dirs[1] = (t_vector2d){0, 1};
	dirs[2] = (t_vector2d){-1, 0};
	dirs[3] = (t_vector2d){1, 0};
	planes[0] = (t_vector2d){0.66, 0};
	planes[1] = (t_vector2d){-0.66, 0};
	planes[2] = (t_vector2d){0, -0.66};
	planes[3] = (t_vector2d){0, 0.66};
	idx = ft_strchr("NSWE", c) - "NSWE";
	p->dir = dirs[idx];
	p->plane = planes[idx];
	p->pos = (t_vector2d){x, y};
	p->move_speed = 0.05;
	p->rot_speed = 0.05;
	return (EXIT_SUCCESS);
}

static int	process_cell(char c, t_vars *vars, int *curr_cols)
{
	printf("%c", c);
	if (ft_strchr("01 ", c))
		(*curr_cols)++;
	else if (c == '\n')
	{
		vars->map_size.y++;
		if (vars->map_size.x < *curr_cols)
			vars->map_size.x = *curr_cols;
		*curr_cols = 0;
	}
	else if (ft_strchr("NSWE", c))
	{
		if (set_player(vars, vars->map_size.y, *curr_cols, c) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*curr_cols)++;
	}
	else
		return (err("load_map", "invalid character in map"));
	return (EXIT_SUCCESS);
}

static int	load_map(char *map_data, t_vars *vars)
{
	int	curr_cols;

	vars->map_size = (t_grid){0, 0};
	curr_cols = 0;
	printf("\nloading...\n");
	while (*map_data)
	{
		if (process_cell(*map_data, vars, &curr_cols) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		map_data++;
	}
	if (vars->player->move_speed == 0 || vars->player->rot_speed == 0)
		return (err("load_map", "player not set"));
	if (curr_cols > 0)
	{
		vars->map_size.y++;
		if (vars->map_size.x < curr_cols)
			vars->map_size.x = curr_cols;
	}
	return (EXIT_SUCCESS);
}

static int	count_strings(char **arr)
{
	int	count;

	count = 0;
	while (*arr++)
		count++;
	return (count);
}

static int	validate_file(char *file, const char *expect_ext)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (ext == NULL)
		return (err("validate_file", "No file extension"));
	if (ft_strcmp(ext, expect_ext) != 0)
		return (err("validate_file", "Invalid file extension"));
	return (EXIT_SUCCESS);
}

static void	remove_trailing(char *line, char delim)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
		i++;
	while (i > 0 && line[i - 1] == delim)
		i--;
	line[i] = '\0';
}

static int	parse_rgb(int *color, char *input)
{
	char	**rgb;
	int		i;
	int		num;

	rgb = ft_split(input, ',');
	if (count_strings(rgb) != 3)
		return (err("parse_rgb", "Invalid RGB format"));
	i = -1;
	while (rgb[++i])
		remove_trailing(rgb[i], ' ');
	i = 0;
	while (rgb[i])
	{
		errno = 0;
		num = ft_atoi_mod(rgb[i]);
		if (num < 0 || num > 255 || errno)
			return (err("parse_rgb", "RGB values must be between 0-255"));
		*color = (*color << 8) | num;
		i++;
	}
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	return (EXIT_SUCCESS);
}

static int	handle_texture_path(char **kv, char **path_ptr)
{
	if (count_strings(kv) != 2)
		return (err("check_elements", "More than one key pair"));
	if (validate_file(kv[1], ".xpm") == EXIT_FAILURE)
		return (err("check_elements", "No .xpm extension found"));
	*path_ptr = ft_strdup(kv[1]);
	return (EXIT_SUCCESS);
}

static void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	process_key(int i, t_texture *tex, char *line)
{
	if (i == 4 && !tex->floor_color)
		return (parse_rgb(&tex->floor_color, &line[2]));
	else if (i == 5 && !tex->ceiling_color)
		return (parse_rgb(&tex->ceiling_color, &line[2]));
	else
		return (err("check_elements", "Already defined"));
}

static int	check_elements(char *line, t_texture *tex, char *path[4])
{
	static char	*keys[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	char		**kv;
	int			i;
	int			status;

	kv = ft_split(line, ' ');
	if (!kv)
		return (err("check_elements", "Failed to split line"));
	status = EXIT_FAILURE;
	i = -1;
	while (keys[++i] && status != EXIT_SUCCESS)
	{
		if (ft_strcmp(kv[0], keys[i]) == 0)
		{
			if (i < 4 && !path[i])
				status = handle_texture_path(kv, &path[i]);
			else
				status = process_key(i, tex, line);
		}
	}
	if (status == EXIT_FAILURE)
		status = err("check_elements", "No valid Key found");
	free_string_array(kv);
	return (status);
}

// static void	print_map(int **map, t_grid map_size)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_size.y)
// 	{
// 		j = 0;
// 		while (j < map_size.x)
// 		{
// 			printf("%d", map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

static _Bool	is_all_elements_loaded(t_vars *vars)
{
	return (vars->texture->ceiling_color && vars->texture->floor_color
		&& vars->path[0] && vars->path[1] && vars->path[2] && vars->path[3]);
}

int	read_elements(int fd, t_vars *vars)
{
	char	*line;
	int		status;

	while (!is_all_elements_loaded(vars))
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			return (err("read_elements", "Failed to read line"));
		}
		if (ft_strcmp(line, "\n") != 0)
		{
			remove_trailing(line, '\n');
			status = check_elements(line, vars->texture, vars->path);
			if (status == EXIT_FAILURE)
			{
				free(line);
				close(fd);
				return (EXIT_FAILURE);
			}
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	skip_blank_lines(int fd, char **map_data)
{
	char	*line;
	_Bool	blank;

	blank = 1;
	while (blank)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			return (err("skip_blank_lines", "Where's the map?"));
		}
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			continue ;
		}
		blank = 0;
		*map_data = ft_strdup(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	read_map_data(int fd, char **map_data)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			return (err("read_map_data", "map is split"));
		}
		temp = *map_data;
		*map_data = ft_strjoin(*map_data, line);
		if (*map_data == NULL)
		{
			free(line);
			return (err("read_map_data", "ft_strjoin failed"));
		}
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

static int	initialize_vars(t_vars *vars)
{
	vars->texture = (t_texture *)calloc(1, sizeof(t_texture));
	vars->player = (t_player *)calloc(1, sizeof(t_player));
	if (!vars->texture || !vars->player)
		return (err("get_input", "Memory allocation failed"));
	return (EXIT_SUCCESS);
}

static int	process_map_data(int fd, char **map_data)
{
	if (skip_blank_lines(fd, map_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (read_map_data(fd, map_data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	setup_map(char *map_data, t_vars *vars)
{
	if (load_map(map_data, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(&vars->map, vars->map_size.y, vars->map_size.x)
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fill_map(map_data, vars->map, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (floodfill(vars->map, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_input(char *file, t_vars *vars)
{
	int		fd;
	char	*map_data;
	int		status;

	map_data = NULL;
	if (initialize_vars(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (validate_file(file, ".cub") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("get_input", strerror(errno)));
	if (read_elements(fd, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_map_data(fd, &map_data) == EXIT_FAILURE)
	{
		free(map_data);
		return (EXIT_FAILURE);
	}
	close(fd);
	status = setup_map(map_data, vars);
	free(map_data);
	return (status);
}

// int	main(int argc, char **argv)
// {
// 	t_vars	vars;
// 	int		status;

// 	if (argc != 2)
// 	{
// 		printf("usage: cub3D <single.cub>\n");
// 		return (1);
// 	}
// 	vars.texture = (t_texture *)calloc(1, sizeof(t_texture));
// 	vars.player = (t_player *)calloc(1, sizeof(t_player));
// 	status = get_input(argv[1], &vars);
// 	printf("-------result-------\n");
// 	printf("paths:\n%s\n%s\n%s\n%s\n", vars.path[0], vars.path[1], vars.path[2],
// 		vars.path[3]);
// 	printf("ceiling: 0x%06X floor: 0x%06X\n", vars.texture->ceiling_color,
// 		vars.texture->floor_color);
// 	printf("player pos: (%f,%f)\n", vars.player->pos.x, vars.player->pos.y);
// 	printf("map size: (%d,%d)\n", vars.map_size.x, vars.map_size.y);
// 	return (status);
// }
