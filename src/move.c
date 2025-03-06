/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:35:01 by niida             #+#    #+#             */
/*   Updated: 2025/03/06 19:33:17 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Scale direction or plane vector by move speed and direction (+1 or -1)
 * Check collision
 */
void	move_player(int **map, t_player *p, int dir, t_vector2d v)
{
	t_vector2d	movement;
	t_vector2d	next_pos;

	movement = vector_scale(v, p->move_speed * dir);
	next_pos = vector_add(p->pos, movement);
	if (!map[(int)next_pos.y][(int)p->pos.x])
		p->pos.y = next_pos.y;
	if (!map[(int)p->pos.y][(int)next_pos.x])
		p->pos.x = next_pos.x;
}

void	key_rotate(t_player *p, int direction)
{
	p->dir = vector_rotate(p->dir, p->rot_speed * direction);
	p->plane = vector_rotate(p->plane, p->rot_speed * direction);
}

int	key_press(int key, t_vars *vars)
{
	if (key == KEY_W)
		move_player(vars->map, vars->player, 1, vars->player->dir);
	if (key == KEY_S)
		move_player(vars->map, vars->player, -1, vars->player->dir);
	if (key == KEY_A)
		move_player(vars->map, vars->player, -1, vars->player->plane);
	if (key == KEY_D)
		move_player(vars->map, vars->player, 1, vars->player->plane);
	if (key == KEY_LEFT)
		key_rotate(vars->player, -1);
	if (key == KEY_RIGHT)
		key_rotate(vars->player, 1);
	printf("pos: %lf,%lf\tdir: %lf,%lf\tplane: %lf,%lf\n",
		vars->player->pos.x, vars->player->pos.y,
		vars->player->dir.x, vars->player->dir.y,
		vars->player->plane.x, vars->player->plane.y);
	raycasting(vars);
	if (key == KEY_ESC)
		close_win(vars);
	return (0);
}

// int	key_release(int key, t_vars *vars)
// {
// 	printf("key release: %d\n", key);
// 	if (vars->win == NULL)
// 		return (1);
// 	if (key == KEY_Q)
// 		close_win(vars);
// 	return (0);
// }
