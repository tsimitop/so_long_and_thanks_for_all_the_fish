/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/10 19:31:47 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remove_coin_instance(t_game *info)
{
	int	i;

	i = 0;
	while (i <= info->init_coins)
	{
// ft_printf("info->image_coin->instances[i].y: %i == info->image_pawn->instances[0].y: %i\n", info->image_coin->instances[i].y, info->image_pawn->instances[0].y);
// ft_printf("info->image_coin->instances[i].x: %i == info->image_pawn->instances[0].x: %i\n", info->image_coin->instances[i].x, info->image_pawn->instances[0].x);

		if (info->image_coin->instances[i].y == info->image_pawn->instances[0].y &&\
		 info->image_coin->instances[i].x == info->image_pawn->instances[0].x)
		{
			info->image_coin->instances[i].enabled = false;
			break ;
		}
		else
			i++;
	}
}

void	print_buffer(t_game *info)
{
	int i;

	i = 0;
	while (info->buffer[i] != '\0')
	{
		ft_printf("%c", info->buffer[i]);
		i++;
	}
}

void print_spl_buf(char **spl_buf)
{
	int y = 0;
	int x = 0;
	while (spl_buf[y])
	{
		x = 0;
		while (spl_buf[y][x])
		{
			ft_printf("%c", spl_buf[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}
