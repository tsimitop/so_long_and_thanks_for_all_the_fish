/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_places.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:50:56 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/14 16:57:39 by tsimitop         ###   ########.fr       */
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
		collectible_case(info, old_y, new_x);
	else if (info->split_map[old_y][new_x] == 'E')
	{
		exit_case(info);
		info->pawn_position.x = new_x;
	}
	else if (info->split_map[old_y][new_x] == '0' \
	|| info->split_map[old_y][new_x] == 'P')
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
		collectible_case(info, new_y, old_x);
	else if (info->split_map[new_y][old_x] == 'E')
	{
		exit_case(info);
		info->pawn_position.y = new_y;
	}
	else if (info->split_map[new_y][old_x] == '0' \
	|| info->split_map[new_y][old_x] == 'P')
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
		collectible_case(info, old_y, new_x);
	else if (info->split_map[old_y][new_x] == 'E')
	{
		info->pawn_position.x = new_x;
		exit_case(info);
	}
	else if (info->split_map[old_y][new_x] == '0' \
	|| info->split_map[old_y][new_x] == 'P')
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
		collectible_case(info, new_y, old_x);
	else if (info->split_map[new_y][old_x] == 'E')
	{
		exit_case(info);
		info->pawn_position.y = new_y;
	}
	else if (info->split_map[new_y][old_x] == '0' \
	|| info->split_map[new_y][old_x] == 'P')
	{
		info->moves += 1;
		info->pawn_position.y = new_y;
		if (info->collected_coins == 1)
			info->user_way_out--;
	}
}
