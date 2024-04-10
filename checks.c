/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/10 16:03:15 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_buffer(t_game *info)
{
	int i;

	i = 0;
	while (info->buffer[i] != '\0')
	{
		ft_printf("%c", info->buffer[i]);
		i++;
	}
	// exit(0);
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
// print_spl_buf(info->split_map);