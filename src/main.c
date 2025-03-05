/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:40:44 by naokiiida         #+#    #+#             */
/*   Updated: 2025/03/05 16:32:30 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_n_err(char *function_name, const char *msg, char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (err(function_name, msg));
}

void	free_vars(t_vars *vars)
{
	free(vars->path[0]);
	free(vars->path[1]);
	free(vars->path[2]);
	free(vars->path[3]);
	free(vars->player);
	free(vars->texture);
	free(vars->map);
}

// ゲームの初期化
// hookの設定　キー入力、キー解放、ウィンドウの閉じるボタン
// フレームごとに呼び出される関数
// loopの開始update
int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
	{
		printf("usage: cub3D <single.cub>\n");
		return (0);
	}
	if (get_input(argv[1], &vars) == EXIT_FAILURE)
	{
		free_vars(&vars);
		return (EXIT_FAILURE);
	}
	if (init(&vars) == EXIT_FAILURE)
	{
		free_vars(&vars);
		return (EXIT_FAILURE);
	}
	mlx_hook(vars.win, EVENT_KEY_PRESS, M_KEY_PRESS, &key_press, &vars);
	mlx_hook(vars.win, EVENT_KEY_RELEASE, M_KEY_RELEASE, &key_release, &vars);
	mlx_hook(vars.win, EVENT_KEY_EXIT, M_STRUCTURE_NOTIFY, &close_win, &vars);
	mlx_loop_hook(vars.mlx, &raycasting, &vars);
	mlx_loop(vars.mlx);
	close_display(&vars);
	return (EXIT_SUCCESS);
}
