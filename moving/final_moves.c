/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:25:39 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:26:07 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_shortest_route(t_game *info, int y, int x)
{
	int	move_counter;

	move_counter = 0;
	calc_moves_to_exit_y(info, y, &move_counter);
	calc_moves_to_exit_x(info, x, &move_counter);
	info->collected_coins = 1;
	info->fastest_way_out = move_counter;
	return (move_counter);
}

void	calc_moves_to_exit_y(t_game *info, int y, int *move_counter)
{
	if (y < info->exit_position.y)
	{
		while (y < info->exit_position.y)
		{
			(*move_counter)++;
			y++;
		}
	}
	else if (y > info->exit_position.y)
	{
		while (y > info->exit_position.y)
		{
			(*move_counter)++;
			y--;
		}
	}
}

void	calc_moves_to_exit_x(t_game *info, int x, int (*move_counter))
{
	if (x < info->exit_position.x)
	{
		while (x < info->exit_position.x)
		{
			(*move_counter)++;
			x++;
		}
	}
	else if (x > info->exit_position.x)
	{
		while (x > info->exit_position.x)
		{
			(*move_counter)++;
			x--;
		}
	}
}
