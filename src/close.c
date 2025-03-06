/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:38:44 by niida             #+#    #+#             */
/*   Updated: 2025/03/06 16:53:29 by sasano           ###   ########.fr       */
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
	printf("init\n");
	free_vars(vars);
	free(vars->ray);
	free_map(vars);
	if (!vars->mlx)
		exit(0);
	while (++i < 4)
		if (vars->tile[i].img)
			mlx_destroy_image(vars->mlx, vars->tile[i].img);
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	free(vars->buffer);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
}

#elif __LINUX__

int	close_win(t_vars *vars)
{
	int	i;

	i = -1;
	free_vars(vars);
	free(vars->ray);
	free_map(vars);
	if (!vars->mlx)
		exit(0);
	while (++i < 4)
		if (vars->tile[i].img)
			mlx_destroy_image(vars->mlx, vars->tile[i].img);
	if (vars->mlx && vars->buffer && vars->buffer->img)
		mlx_destroy_image(vars->mlx, vars->buffer->img);
	free(vars->buffer);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
}
#endif
