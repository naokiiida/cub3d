/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:44 by niida             #+#    #+#             */
/*   Updated: 2025/03/05 23:11:26 by niida            ###   ########.fr       */
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
	free_vars(vars);
	while (++i < 4)
		if (vars->tile[i].img)
			free(vars->tile[i].img);
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	free(vars->ray);
	free(vars->buffer);
	exit(0);
}

int	close_display(t_vars *vars)
{
	write(1, "closing...\n", 11);
	free_map(vars);
	if (vars->mlx)
		free(vars->mlx);
	return (0);
}
#elif __LINUX__

int	close_win(t_vars *vars)
{
	int	i;

	i = -1;
	free_vars(vars);
	while (++i < 4)
		if (vars->tile[i].img)
			free(vars->tile[i].img);
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	free(vars->ray);
	free(vars->buffer);
	mlx_loop_end(vars->mlx);
	return (0);
}

//mlx_destroy_display() is only on linux
int	close_display(t_vars *vars)
{
	write(1, "closing...\n", 11);
	free_map(vars);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	return (0);
}
#endif
