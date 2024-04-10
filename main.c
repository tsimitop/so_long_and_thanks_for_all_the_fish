/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/10 19:42:28 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	info;

ft_printf("TODO: fix buffer for set values\n");
	if (argc != 2)
		error_handling("Arguments should be: ./so_long map.ber\n", NULL, NULL);
	// info = ft_calloc(1, sizeof(t_game));
	info.argv_map = argv[1];
	info.moves = 0;
	run_all_checks(argv, &info);
	info.mlx = mlx_init(info.width * TILE_SIZE, info.height * TILE_SIZE, "So long and thanks", true);
	if (!info.mlx)
		error_handling("Failed to allocate mlx", NULL, &info);
	loading_images(&info);
	map_render(&info);
	// mlx_loop_hook(info.mlx, ft_hook, info);
	mlx_key_hook(info.mlx, ft_hook, &info);
	//OR || AND
	// mlx_loop_hook(info.mlx, ft_hook, info.mlx);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
// ft_printf("info->height = %i and info->wodth = %i\n", info.height, info.width);
	ft_printf("You reached the end of the main function...");
	return (EXIT_SUCCESS);
}

void	ft_hook(mlx_key_data_t	cur_key, void *game)
{
	t_game *info;
	t_point	current_position;

	info = (t_game *)game;
// ft_printf("info->split_map[0][0] = %c\n", info->split_map[0][0]);
// ft_printf("info->split_map[info->pawn_position.x][info->pawn_position.y] = %c\n", info->split_map[info->pawn_position.x][info->pawn_position.y]);
	current_position = info->pawn_position;
	if (cur_key.action == MLX_PRESS || cur_key.action == MLX_REPEAT)
	{
		if (cur_key.key == MLX_KEY_ESCAPE)
		{
			free(info);//free anything else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		if (cur_key.key == MLX_KEY_UP || cur_key.key == MLX_KEY_W)
			go_up(info);
		else if (cur_key.key == MLX_KEY_DOWN || cur_key.key == MLX_KEY_S)
			go_down(info);
		else if (cur_key.key == MLX_KEY_LEFT || cur_key.key == MLX_KEY_A)
			go_left(info);
		else if (cur_key.key == MLX_KEY_RIGHT || cur_key.key == MLX_KEY_D)
			go_right(info);
		if (current_position.x != info->pawn_position.x || current_position.y != info->pawn_position.y)
		{
			// ft_printf("info->split_map[info->pawn_position.y][info->pawn_position.x] = info->split_map[%d][%d] =%c\n", info->pawn_position.y, info->pawn_position.x, info->split_map[info->pawn_position.y][info->pawn_position.x]);
			// ft_printf("info->image_pawn->instances[0].y = %i\tinfo->image_pawn->instances[0].x = %i\n", info->image_pawn->instances[0].y, info->image_pawn->instances[0].x);
			// if (info->image_pawn->instances[0].enabled)
				// ft_printf("true\n");
			// else
				// ft_printf("false");
			ft_printf("Moves: %d\n", info->moves);
			current_position = info->pawn_position;
		}
	}
}
