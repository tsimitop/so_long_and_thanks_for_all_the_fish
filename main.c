/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/13 14:21:02 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	info;
	int screen_width; // put in struct
	int screen_height;

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
	mlx_get_monitor_size(0, &screen_width, &screen_height);
	if (info.width * TILE_SIZE > screen_width || info.height * TILE_SIZE > screen_height)
		error_handling("Cannot fit image on screen!!!", NULL, NULL);
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
			ft_printf("Moves: %d\n", info->moves);
			current_position = info->pawn_position;
		}
	}
}
