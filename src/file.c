/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:05:55 by niida             #+#    #+#             */
/*   Updated: 2025/02/24 21:00:33 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
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

int	err(char *function_name, const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(function_name, 2);
	ft_putstr_fd(":\t", 2);
	perror(msg);
	return (EXIT_FAILURE);
}

// int flood_recursive(int **map, int x, int y, t_vars *vars)
// {
// 	if (x > vars->map_size.x || y > vars->map_size.y || x < 0 || y < 0)
// 		return (EXIT_FAILURE);
// 	if (map[x][y] == 1)
// 		return (EXIT_SUCCESS);
// 	if (map[x][y] == 2)
// 	{
// 		map[x][y] = 1;
// 		flood_recursive(map, x + 1, y, vars);
// 		flood_recursive(map, x - 1, y, vars);
// 		flood_recursive(map, x, y + 1, vars);
// 		flood_recursive(map, x, y - 1, vars);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int floodfill(int **map, t_vars *vars)
// {
// 	int x;
// 	int y;

// 	x = 0;
// 	y = 0;
// 	flood_recursive(map, x, y, vars);
// 	return (EXIT_SUCCESS);
// }
{
	int	x;
	int	y;

	y = -1;
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x && *mapData)
		{
			if (*mapData == '\n')
				mapData++;
			if (*mapData == '0')
				map[y][x] = 0;
			else if (*mapData == '1')
				map[y][x] = 1;
			else if (*mapData == ' ')
				map[y][x] = 2;
			else
				map[y][x] = 0;
			mapData++;
		}
	}
	return (EXIT_SUCCESS);
}

int	init_map(int **map, int rows, int cols)
{
	int	i;

	map = malloc(sizeof(int *) * rows);
	if (!map)
		return (err("load_map", "malloc failed for map rows"));
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(int) * cols);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (err("load_map", "malloc failed for map columns"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_player(t_player *player, int x, int y, char c)
{
	if ((player->pos.x == 0 && player->pos.y == 0) && (player->dir.x == 0
			&& player->dir.y == 0))
		return (err("load_map", "player not positioned"));
	if (c == 'N')
		player->dir = (t_vector2d){0, 1};
	else if (c == 'S')
		player->dir = (t_vector2d){0, -1};
	else if (c == 'W')
		player->dir = (t_vector2d){-1, 0};
	else if (c == 'E')
		player->dir = (t_vector2d){1, 0};
	player->pos = (t_vector2d){x, y};
	return (EXIT_SUCCESS);
}

static int	process_char(char c, t_grid *grid, int *curr_cols, t_player *player)
{
	if (ft_strchr("01 ", c))
		(*curr_cols)++;
	else if (c == '\n')
	{
		grid->y++;
		if (grid->x < *curr_cols)
			grid->x = *curr_cols;
		*curr_cols = 0;
	}
	else if (ft_strchr("NSWE", c))
	{
		if (set_player(player, grid->y, grid->x, c) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*curr_cols)++;
	}
	else
		return (err("load_map", "invalid character in map"));
	return (EXIT_SUCCESS);
}

int	load_map(char *mapData, int **map, t_player *player)
{
	t_grid	grid;
	int		curr_cols;

	grid = (t_grid){0, 0};
	curr_cols = 0;
	while (*mapData)
	{
		if (process_char(*mapData, &grid, &curr_cols, player) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		mapData++;
	}
	if (init_map(map, grid.y, grid.x) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (fill_map(mapData, map, grid));
}

int	count_strings(char **arr)
{
	int	count;

	count = 0;
	while (*arr++)
		count++;
	return (count);
}

int	parse_rgb(int *color, char *input)
{
	char	**rgb;
	int		i;
	int		num;

	rgb = ft_split(input, ',');
	if (count_strings(rgb) != 3)
		return (err("parse_rgb", "Invalid RGB format"));
	i = 0;
	while (rgb[i])
	{
		num = ft_atoi(rgb[i]);
		if (num < 0 || num > 255)
			return (err("parse_rgb", "RGB values must be between 0-255"));
		*color = (*color << 8) | num;
		i++;
	}
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	return (EXIT_SUCCESS);
}

int	check_elements(char *line, t_texture *tex, char *path[4])
{
	char		**kv;
	static char	*keys[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;

	kv = ft_split(line, ' ');
	if (count_strings(kv) != 2)
		return (err("check_elements", "Invalid element format"));
	i = -1;
	while (keys[++i])
	{
		if (strcmp(kv[0], keys[i]) == 0)
		{
			if (i < 4)
				path[i] = ft_strdup(kv[1]);
			else if (i == 5)
				parse_rgb(&tex->floor_color, kv[1]);
			else
				parse_rgb(&tex->ceiling_color, kv[1]);
		}
	}
	i = 0;
	while (kv[i])
		free(kv[i++]);
	return (EXIT_SUCCESS);
}

void	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	line[--i] = '\0';
}

int	validate_file(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (ext == NULL)
		return (err("validate_file", "No file extension"));
	if (strcmp(ext, ".cub") != 0)
		return (err("validate_file", "Invalid file extension"));
	return (EXIT_SUCCESS);
}

int	get_input(char *file, t_vars *vars)
{
	char	*line;
	int		fd;
	_Bool	all_elements;
	_Bool	map_done;
	_Bool	blank;
	char	*mapData;
	int		**map;

	fd = -1;
	all_elements = 0;
	if (validate_file(file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("-----fopen-----\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("get_input", strerror(errno)));
	printf(" fd=%d\n", fd);
	while (!all_elements)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
		{
			close(fd);
			return (err("get_input", "Failed to read line"));
		}
		if (strcmp(line, "\n") == 0)
			continue ;
		remove_newline(line);
		if (check_elements(line, vars->texture, vars->path) == EXIT_FAILURE)
		{
			free(line);
			close(fd);
			return (err("get_input", "Failed to parse elements"));
		}
		free(line);
		all_elements = vars->texture->ceiling_color
			&& vars->texture->floor_color && vars->path[0] && vars->path[1]
			&& vars->path[2] && vars->path[3];
	}
	blank = 1;
	while (blank)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
		{
			close(fd);
			return (err("get_input", "Where's the map?"));
		}
		if (strcmp(line, "\n") == 0)
			continue ;
		blank = 0;
	}
	mapData = NULL;
	while (!map_done)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		if (strcmp(line, "\n") == 0)
		{
			close(fd);
			return (err("get_input", "map is split"));
		}
		mapData = ft_strjoin(mapData, line);
	}
	close(fd);
	if (load_map(mapData, map, vars->player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(mapData);
	// if (floodfill(map, vars) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_vars	vars;
	int		status;

	vars.texture = (t_texture *)calloc(1, sizeof(t_texture));
	vars.player = (t_player *)calloc(1, sizeof(t_player));
	status = get_input("./cub3D_map_tester/maps/test_valid_map.cub", &vars);
	printf("-------result-------\n");
	printf("paths:\n%s\n%s\n%s\n%s\n", vars.path[0], vars.path[1], vars.path[2],
		vars.path[3]);
	printf("ceiling: 0x%06X floor: 0x%06X\n", vars.texture->ceiling_color,
		vars.texture->floor_color);
	printf("player pos: (%f,%f)\n", vars.player->pos.x, vars.player->pos.y);
	return (status);
}
