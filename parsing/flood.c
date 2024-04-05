/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:06:29 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/05 20:03:55 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_paths(char **spl_buf, t_game *info)
{
	int		i;
	int		j;
	int		e_counter;
	int		c_counter;

	i = 0;
	j = 0;
	e_counter = 0; //remove
	c_counter = 0;
	fill(spl_buf, info->dimentions, info->pawn_position);
	while (spl_buf[i])
	{
		while (spl_buf[i][j])
		{
			if (spl_buf[i][j] != '1')
			{
				// if (spl_buf[i][j] == 'E')
				// 	e_counter++;
				// else if (spl_buf[i][j] == 'C')
				// 	c_counter++;
				free_buf_error(spl_buf, spl_buf[i][j]);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	free_buf_error(char **spl_buf, char c)
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

void	fill(char **spl_buf, t_point size, t_point cur)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| spl_buf[cur.y][cur.x] == '1')
		return ;

	spl_buf[cur.y][cur.x] = '1';
	fill(spl_buf, size, (t_point){cur.x - 1, cur.y});
	fill(spl_buf, size, (t_point){cur.x + 1, cur.y});
	fill(spl_buf, size, (t_point){cur.x, cur.y - 1});
	fill(spl_buf, size, (t_point){cur.x, cur.y + 1});
}
