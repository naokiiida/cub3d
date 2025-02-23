/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:35:01 by niida             #+#    #+#             */
/*   Updated: 2025/02/22 20:38:08 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**
 * Scale direction or plane vector by move speed and direction (+1 or -1)
 * Check collision
 */
void	move_player(int map[ROWS][COLS], t_player *p, int dir, t_vector2d v)
{
	t_vector2d	movement;
	t_vector2d	next_pos;

	movement = vector_scale(v, p->move_speed * dir);
	next_pos = vector_add(p->pos, movement);
	if (map[(int)next_pos.y][(int)p->pos.x] == MAP_WALL
		|| map[(int)p->pos.y][(int)next_pos.x] == MAP_WALL)
	{
		printf("\033[1;31mreached wall\033[0m\n");
		return ;
	}
	p->pos.x = next_pos.x;
	p->pos.y = next_pos.y;
}

void	key_rotate(t_player *p, int direction)
{
	double	angle;

	angle = p->rot_speed * direction;
	p->dir = vector_rotate(p->dir, angle);
	p->plane = vector_rotate(p->plane, angle);
}

int	key_press(int key, t_vars *vars)
{
	if (key == KEY_W)
		move_player(vars->map, vars->player, 1, vars->player->dir);
	if (key == KEY_S)
		move_player(vars->map, vars->player, -1, vars->player->dir);
	if (key == KEY_A)
		move_player(vars->map, vars->player, 1, vars->player->plane);
	if (key == KEY_D)
		move_player(vars->map, vars->player, -1, vars->player->plane);
	if (key == KEY_LEFT)
		key_rotate(vars->player, 1);
	if (key == KEY_RIGHT)
		key_rotate(vars->player, -1);
	if (key == KEY_ESC)
		close_win(vars);
	printf("key press: %d\t", key);
	printf("player at: x=%f, y=%f\n", vars->player->pos.x, vars->player->pos.y);
	printf("tex_x: %d\n", vars->texture->tex_x);
	printf("plane{%f, %f}, vector{%f, %f}\n", vars->player->plane.x,
		vars->player->plane.y, vars->player->dir.x, vars->player->dir.y);
	mlx_clear_window(vars->mlx, vars->win);
	raycasting(vars);
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
