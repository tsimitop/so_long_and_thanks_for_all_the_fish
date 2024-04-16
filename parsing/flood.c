/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:06:29 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:21:51 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void static	free_buf_error(char **spl_buf, char c);

void	check_walls(char **spl_buf, t_game *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (spl_buf[i] != NULL && spl_buf[i][j] != '\0')
	{
		while (spl_buf[i][j] != '\0')
		{
			if (spl_buf[0][j] != '1' || spl_buf[i][0] != '1' || \
			spl_buf[i][info->width - 1] != '1' || \
			spl_buf[info->height - 1][j] != '1')
			{
				free_split(spl_buf);
				free_split(info->split_map);
				error_handling("Your map should be surrouded by walls", NULL);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

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
	free_split(spl_buf);
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

void	check_exit_coin_pawn(char *str, int *esc, int *coin, int *pawn)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && str[i] != 'P' \
			&& str[i] != 'E' && str[i] != '\n')
			error_handling("Invalid character in map.", NULL);
		if (str[i] == 'C')
			(*coin)++;
		else if (str[i] == 'E')
			(*esc)++;
		else if (str[i] == 'P')
			(*pawn)++;
		i++;
	}
}
