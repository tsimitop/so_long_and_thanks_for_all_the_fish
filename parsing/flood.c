/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:06:29 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/13 15:03:02 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void static	free_buf_error(char **spl_buf, char c);

void	check_paths(char **spl_buf, t_game *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	fill(spl_buf, info->dimentions, info->pawn_position);
	while (spl_buf[i])
	{
		while (spl_buf[i][j])
		{
			if (spl_buf[i][j] != '1')
				free_buf_error(spl_buf, spl_buf[i][j]);
			j++;
		}
		i++;
		j = 0;
	}
}

void static	free_buf_error(char **spl_buf, char c)
{
	if (c == 'E')
	{
		free_split(spl_buf);
		error_handling("No path to exit", NULL);
	}
	if (c == 'C')
	{
		free_split(spl_buf);
		error_handling("No path to all collectibles", NULL);
	}
}

void	fill(char **spl_buf, t_point size, t_point spot)
{
	if (spot.y < 0 || spot.y >= size.y || spot.x < 0 || spot.x >= size.x
		|| spl_buf[spot.y][spot.x] == '1')
		return ;

	spl_buf[spot.y][spot.x] = '1';
	fill(spl_buf, size, (t_point){spot.x - 1, spot.y});
	fill(spl_buf, size, (t_point){spot.x + 1, spot.y});
	fill(spl_buf, size, (t_point){spot.x, spot.y - 1});
	fill(spl_buf, size, (t_point){spot.x, spot.y + 1});
}
