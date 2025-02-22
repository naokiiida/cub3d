/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:35:01 by niida             #+#    #+#             */
/*   Updated: 2025/02/22 17:13:16 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	key_press(int key, t_vars *vars)
{
	printf("key press: %d\t", key);
	if (key == KEY_W)
		vars->player->pos.y -= 1;
	if (key == KEY_S)
		vars->player->pos.y += 1;
	if (key == KEY_A)
		vars->player->pos.x -= 1;
	if (key == KEY_D)
		vars->player->pos.x += 1;
	if (key == KEY_ESC)
		close_win(vars);
	raycasting(vars);
	printf("player at: x=%f, y=%f\n", vars->player->pos.x, vars->player->pos.y);
	printf("tex_x: %d\n", vars->texture->tex_x);
	return (0);
}

int	key_release(int key, t_vars *vars)
{
	printf("key release: %d\n", key);
	if (vars->win == NULL)
		return (1);
	if (key == KEY_Q)
		close_win(vars);
	return (0);
}

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
