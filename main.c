/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:27:22 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_leaks(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_game	info;
	int		s_width;
	int		s_height;

	atexit(&check_leaks);
	if (argc != 2)
		error_handling("Arguments should be: ./so_long map.ber\n", NULL);
	info.moves = 0;
	info.collected_coins = 0;
	info.not_rectangular = 0;
	run_all_checks(argv, &info);
	info.mlx = mlx_init(info.width * TILE_SIZE, info.height * TILE_SIZE, \
	"So long and thanks", false);
	if (!info.mlx)
		error_handling("Failed to allocate mlx", NULL);
	mlx_get_monitor_size(0, &s_width, &s_height);
	if (info.width * TILE_SIZE > s_width || info.height * TILE_SIZE > s_height)
		error_handling("Cannot fit map on screen!!!", NULL);
	loading_images(&info);
	map_render(&info);
	mlx_key_hook(info.mlx, ft_hook, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
	final_free(&info);
	return (EXIT_SUCCESS);
}

void	ft_hook(mlx_key_data_t	cur_key, void *game)
{
	t_game	*info;
	t_point	current_position;

	info = (t_game *)game;
	current_position = info->pawn_position;
	if (cur_key.action == MLX_PRESS || cur_key.action == MLX_REPEAT)
	{
		if (cur_key.key == MLX_KEY_ESCAPE)
			esc_key_result(info);
		if (cur_key.key == MLX_KEY_UP || cur_key.key == MLX_KEY_W)
			go_up(info);
		else if (cur_key.key == MLX_KEY_DOWN || cur_key.key == MLX_KEY_S)
			go_down(info);
		else if (cur_key.key == MLX_KEY_LEFT || cur_key.key == MLX_KEY_A)
			go_left(info);
		else if (cur_key.key == MLX_KEY_RIGHT || cur_key.key == MLX_KEY_D)
			go_right(info);
		if (current_position.x != info->pawn_position.x \
		|| current_position.y != info->pawn_position.y)
		{
			ft_printf("Moves: %d\n", info->moves);
			current_position = info->pawn_position;
		}
	}
}

void	esc_key_result(t_game *info)
{
	free(info->initial_map);
	free_split(info->split_map);
	mlx_close_window(info->mlx);
	exit(EXIT_SUCCESS);
}
