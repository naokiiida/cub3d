/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:45:52 by niida             #+#    #+#             */
/*   Updated: 2025/02/22 18:46:00 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

t_vector2d	vector_add(t_vector2d v1, t_vector2d v2)
{
	t_vector2d	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_vector2d	vector_scale(t_vector2d v, double scale)
{
	t_vector2d	result;

	result.x = v.x * scale;
	result.y = v.y * scale;
	return (result);
}

t_vector2d	vector_rotate(t_vector2d v, double angle)
{
	t_vector2d	result;
	double		cos_angle;
	double		sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	result.x = v.x * cos_angle - v.y * sin_angle;
	result.y = v.x * sin_angle + v.y * cos_angle;
	return (result);
}
