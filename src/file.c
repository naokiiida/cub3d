/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:05:55 by niida             #+#    #+#             */
/*   Updated: 2025/03/06 15:55:40 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

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
	vars->map = NULL;
	vars->texture = (t_texture *)calloc(1, sizeof(t_texture));
	vars->player = (t_player *)calloc(1, sizeof(t_player));
	vars->ray = NULL;
	vars->buffer = NULL;
	vars->path[0] = NULL;
	vars->path[1] = NULL;
	vars->path[2] = NULL;
	vars->path[3] = NULL;
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
