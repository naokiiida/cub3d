/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:44 by niida             #+#    #+#             */
/*   Updated: 2025/02/22 18:39:02 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#ifdef __APPLE__

int	close_win(t_vars *vars)
{
	write(1, "closing...\n", 11);
	mlx_destroy_image(vars->mlx, vars->buffer->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	vars->mlx = NULL;
	free(vars->ray);
	vars->ray = NULL;
	free(vars->player);
	vars->player = NULL;
	free(vars->texture);
	vars->texture = NULL;
	free(vars->buffer);
	vars->buffer = NULL;
	// free(vars);
	// vars = NULL;
	exit(0);
}

int	close_display(t_vars *vars)
{
	(void)vars;
	write(1, "closing...\n", 11);
	return (0);
}
#elif __LINUX__

int	close_win(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->buffer->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	vars->mlx = NULL;
	free(vars->ray);
	vars->ray = NULL;
	free(vars->player);
	vars->player = NULL;
	free(vars->texture);
	vars->texture = NULL;
	free(vars->buffer);
	vars->buffer = NULL;
	free(vars);
	vars = NULL;
	mlx_loop_end(vars->mlx);
	return (0);
}

int	close_display(t_vars *vars)
{
	write(1, "closing...\n", 11);
	mlx_destroy_display(vars->mlx);
	free(vars);
	vars = NULL;
	return (0);
}
#endif
