/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:28:26 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handling(char *str, int *fd)
{
	if (fd)
		close(*fd);
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	free_info_error_handling(char *str, int *fd, t_game *info)
{
	if (fd)
		close(*fd);
	if (info->split_map)
		free_split(info->split_map);
	if (info->initial_map)
		free(info->initial_map);
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	final_free(t_game *info)
{
	if (info->split_map)
		free_split(info->split_map);
	if (info->initial_map)
		free(info->initial_map);
}

void	free_init_map_error_handle(char *str, int *fd, t_game *info)
{
	if (fd)
		close(*fd);
	if (info->initial_map)
		free(info->initial_map);
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	remove_coin_instance(t_game *info)
{
	int	i;

	i = 0;
	while (i <= info->init_coins)
	{
		if (info->image_coin->instances[i].y == \
		info->image_pawn->instances[0].y && \
		info->image_coin->instances[i].x == info->image_pawn->instances[0].x)
		{
			info->image_coin->instances[i].enabled = false;
			break ;
		}
		else
			i++;
	}
}
