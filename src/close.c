/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:44 by niida             #+#    #+#             */
/*   Updated: 2025/02/25 23:11:13 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include "libft.h"

int	err(char *function_name, const char *msg)
{
	if (!msg)
		return (EXIT_SUCCESS);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(function_name, 2);
	ft_putstr_fd(":\t", 2);
	perror(msg);
	return (EXIT_FAILURE);
}

#ifdef __APPLE__

int	close_win(t_vars *vars)
{
	int	i;

	i = -1;
	write(1, "closing...\n", 11);
	while (++i < 4)
		free(vars->tile[i].img);
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	vars->mlx = NULL;
	free(vars->map);
	vars->map = NULL;
	free(vars->ray);
	vars->ray = NULL;
	free(vars->player);
	vars->player = NULL;
	free(vars->texture);
	vars->texture = NULL;
	free(vars->buffer);
	vars->buffer = NULL;
	exit(0);
}

int	close_display(t_vars *vars)
{
	(void)vars;
	return (0);
}
#elif __LINUX__

int	close_win(t_vars *vars)
{
	int	i;

	i = -1;
	write(1, "closing...\n", 11);
	mlx_loop_end(vars->mlx);
	while (++i < 4)
		free(vars->tile[i].img);
	return (0);
}

int	close_display(t_vars *vars)
{
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	vars->mlx = NULL;
	free(vars->map);
	vars->map = NULL;
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
	return (0);
}
#endif
