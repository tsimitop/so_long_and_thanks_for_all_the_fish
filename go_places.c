/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_places.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:50:56 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/14 15:45:35 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_left(t_game *info)
{
	int	old_y;
	int	new_x;

	old_y = info->pawn_position.y;
	new_x = info->pawn_position.x - 1;
	if (info->split_map[old_y][new_x] == '1')
		return ;
	info->pawn_position.x = new_x;
	info->image_pawn->instances[0].x = info->pawn_position.x * TILE_SIZE;
	if (info->split_map[old_y][new_x] == 'C')
	{
		info->split_map[old_y][new_x] = '0';
		info->coins = info->coins - 1;
		if (info->collected_coins == 0 && info->coins == 0)
		{
			calculate_shortest_route(info, old_y, new_x);
			info->user_way_out = info->fastest_way_out;
		}
		info->moves += 1;
		remove_coin_instance(info);
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
	else if (info->split_map[old_y][new_x] == 'E')
	{
		if (info->coins == 0)
		{
			// free(info);
			//free anthing else
// ft_printf("info->user_way_out = %i\n", info->user_way_out);

			if (info->user_way_out != 0)
				ft_printf("You lost! You didn't take the fastest way out!\n");
			else
				ft_printf("Congratulations, you won!\n");
			free(info->initial_map);
			free_split(info->split_map);
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.x = new_x;
		}
	}
	else if (info->split_map[old_y][new_x] == '0' || info->split_map[old_y][new_x] == 'P')
	{
		info->moves += 1;
		info->pawn_position.x = new_x;
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
}

void	go_up(t_game *info)
{
	int	old_x;
	int	new_y;

	old_x = info->pawn_position.x;
	new_y = info->pawn_position.y - 1;
	if (info->split_map[new_y][old_x] == '1')
		return ;
	info->pawn_position.y = new_y;
	info->image_pawn->instances[0].y = info->pawn_position.y * TILE_SIZE;
	if (info->split_map[new_y][old_x] == 'C')
	{
		info->split_map[new_y][old_x] = '0';
		info->coins = info->coins - 1;
		if (info->collected_coins == 0 && info->coins == 0)
		{
			calculate_shortest_route(info, new_y, old_x);
			info->user_way_out = info->fastest_way_out;
		}
		info->moves += 1;
		remove_coin_instance(info);
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
	else if (info->split_map[new_y][old_x] == 'E')
	{
		if (info->coins == 0)
		{
			// free(info);
			//free anthing else
// ft_printf("info->user_way_out = %i\n", info->user_way_out);
			if (info->user_way_out != 0)
				ft_printf("You lost! You didn't take the fastest way out!\n");
			else
				ft_printf("Congratulations, you won!\n");
			free(info->initial_map);
			free_split(info->split_map);
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.y = new_y;
		}
	}
	else if (info->split_map[new_y][old_x] == '0' || info->split_map[new_y][old_x] == 'P')
	{
		info->moves += 1;
		info->pawn_position.y = new_y;
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
}

void	go_right(t_game *info)
{
	int	old_y;
	int	new_x;

	old_y = info->pawn_position.y;
	new_x = info->pawn_position.x + 1;
	if (info->split_map[old_y][new_x] == '1')
		return ;
	info->pawn_position.x = new_x;
	info->image_pawn->instances[0].x = info->pawn_position.x * TILE_SIZE;
	if (info->split_map[old_y][new_x] == 'C')
	{
		info->split_map[old_y][new_x] = '0';
		info->coins = info->coins - 1;
		if (info->collected_coins == 0 && info->coins == 0)
		{
			calculate_shortest_route(info, old_y, new_x);
			info->user_way_out = info->fastest_way_out;
		}
		info->moves += 1;
		remove_coin_instance(info);
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
	else if (info->split_map[old_y][new_x] == 'E')
	{
		if (info->coins == 0)
		{
			// free(info);
			//free anthing else
// ft_printf("info->user_way_out = %i\n", info->user_way_out);

			if (info->user_way_out != 0)
				ft_printf("You lost! You didn't take the fastest way out!\n");
			else
				ft_printf("Congratulations, you won!\n");
			free(info->initial_map);
			free_split(info->split_map);
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.x = new_x;
		}
	}
	else if (info->split_map[old_y][new_x] == '0' || info->split_map[old_y][new_x] == 'P')
	{
		info->moves += 1;
		info->pawn_position.x = new_x;
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
}

void	go_down(t_game *info)
{
	int	old_x;
	int	new_y;

	old_x = info->pawn_position.x;
	new_y = info->pawn_position.y + 1;
	if (info->split_map[new_y][old_x] == '1')
		return ;
	info->pawn_position.y = new_y;
	info->image_pawn->instances[0].y = info->pawn_position.y * TILE_SIZE;
	if (info->split_map[new_y][old_x] == 'C')
	{
		info->split_map[new_y][old_x] = '0';
		info->coins = info->coins - 1;
		if (info->collected_coins == 0 && info->coins == 0)
		{
			calculate_shortest_route(info, new_y, old_x);
			info->user_way_out = info->fastest_way_out;
		}
		info->moves += 1;
		remove_coin_instance(info);
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
	else if (info->split_map[new_y][old_x] == 'E')
	{
		if (info->coins == 0)
		{
			// free(info);
			//free anthing else
// ft_printf("info->user_way_out = %i\n", info->user_way_out);
			if (info->user_way_out != 0)
				ft_printf("You lost! You didn't take the fastest way out!\n");
			else
				ft_printf("Congratulations, you won!\n");
			free(info->initial_map);
			free_split(info->split_map);
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.y = new_y;
		}
	}
	else if (info->split_map[new_y][old_x] == '0' || info->split_map[new_y][old_x] == 'P')
	{
		info->moves += 1;
		info->pawn_position.y = new_y;
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
}
