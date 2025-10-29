/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:36:14 by sasano            #+#    #+#             */
/*   Updated: 2025/03/31 15:44:26 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

static int	load_image(t_vars *vars, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &img->img_width,
			&img->img_height);
	if (!img->img)
		return (err("load_image", "mlx_xpm_file_to_image failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (EXIT_SUCCESS);
}

static int	load_images(t_vars *vars)
{
	int	k;
	int	status;

	k = -1;
	while (++k < 4)
	{
		status = load_image(vars, &vars->tile[k], vars->path[k]);
		if (status == EXIT_FAILURE)
		{
			while (k > 0)
				mlx_destroy_image(vars->mlx, vars->tile[--k].img);
			return (err("load_images", "failed tile"));
		}
	}
	return (EXIT_SUCCESS);
}

static int	init_buffer(t_vars *vars)
{
	vars->buffer = (t_img *)calloc(1, sizeof(t_img));
	if (!vars->buffer)
		return (err("init_buffer", "failed to allocate buffer"));
	vars->buffer->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->buffer->img)
	{
		free(vars->buffer);
		vars->buffer = NULL;
		return (err("init_buffer", "failed mlx_new_image"));
	}
	vars->buffer->addr = mlx_get_data_addr(vars->buffer->img,
			&vars->buffer->bits_per_pixel, &vars->buffer->line_length,
			&vars->buffer->endian);
	return (EXIT_SUCCESS);
}

static int	cleanup(t_vars *vars, char *func, const char *msg)
{
	if (vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		free(vars->mlx);
		vars->mlx = NULL;
	}
	return (err(func, msg));
}

int	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (err("init", "failed mlx_init"));
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->win)
	{
		free(vars->mlx);
		vars->mlx = NULL;
		return (err("init", "failed mlx_new_window"));
	}
	vars->ray = (t_ray *)calloc(1, sizeof(t_ray));
	if (!vars->ray)
		return (cleanup(vars, "init", "failed to allocate ray"));
	if (init_buffer(vars) == EXIT_FAILURE)
		return (cleanup(vars, "init_buffer", "failed to initialize buffer"));
	if (load_images(vars) == EXIT_FAILURE)
		return (cleanup(vars, "load_images", "failed to load images"));
	printf("init\n");
	return (EXIT_SUCCESS);
}
