/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_places.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:50:56 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/09 20:20:18 by tsimitop         ###   ########.fr       */
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
		// put_element(info, old_y, new_x, "png_folder/floor.png"); // c = floor;
		info->coins = info->coins - 1;
		info->moves += 1;
	}
	else if (info->split_map[old_y][new_x] == 'E')
	{
		if (info->coins == 0)
		{
			free(info);
			//free anthing else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.x = new_x;
		}
	}
	else if (info->split_map[old_y][new_x] == '0')
	{
		info->moves += 1;
		info->pawn_position.x = new_x;
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
	else if (info->split_map[new_y][old_x] == 'C')
	{
		info->pawn_position.y = new_y;
		// put_element(info, new_y, old_x, "png_folder/floor.png"); // c = floor;
		info->coins = info->coins - 1;
		info->moves += 1;
	}
	else if (info->split_map[new_y][old_x] == 'E')
	{
		if (info->coins == 0)
		{
			free(info);
			//free anthing else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.y = new_y;
		}
	}
	else if (info->split_map[new_y][old_x] == '0')
	{
		info->moves += 1;
		info->pawn_position.y = new_y;
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
	else if (info->split_map[old_y][new_x] == 'C')
	{
		info->pawn_position.x = new_x;
		// put_element(info, old_y, new_x, "png_folder/floor.png"); // c = floor;
		info->coins = info->coins - 1;
		info->moves += 1;
	}
	else if (info->split_map[old_y][new_x] == 'E')
	{
		if (info->coins == 0)
		{
			free(info);
			//free anthing else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.x = new_x;
		}
	}
	else if (info->split_map[old_y][new_x] == '0')
	{
		info->moves += 1;
		info->pawn_position.x = new_x;
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
	else if (info->split_map[new_y][old_x] == 'C')
	{
		info->pawn_position.y = new_y;
		// put_element(info, new_y, old_x, "png_folder/floor.png"); // c = floor;
		info->coins = info->coins - 1;
		info->moves += 1;
	}
	else if (info->split_map[new_y][old_x] == 'E')
	{
		if (info->coins == 0)
		{
			free(info);
			//free anthing else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		else
		{
			info->moves += 1;
			info->pawn_position.y = new_y;
		}
	}
	else if (info->split_map[new_y][old_x] == '0')
	{
		info->moves += 1;
		info->pawn_position.y = new_y;
	}
}
