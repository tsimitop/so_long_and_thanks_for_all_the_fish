/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:44:10 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/14 17:19:46 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collectible_case(t_game *info, int y, int x)
{
	info->split_map[y][x] = '0';
	info->coins = info->coins - 1;
	if (info->collected_coins == 0 && info->coins == 0)
	{
		calculate_shortest_route(info, y, x);
		info->user_way_out = info->fastest_way_out;
	}
	info->moves += 1;
	remove_coin_instance(info);
	if (info->collected_coins == 1)
		info->user_way_out--;
}

void	exit_case(t_game *info)
{
	if (info->coins == 0)
	{
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
		info->moves += 1;
}
