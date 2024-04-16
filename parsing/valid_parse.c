/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:42:50 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:23:26 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	info_map_init(char *gnl, t_game *info, int fd);

void	fill_buffer_check_rect_empty(int fd, t_game *info)
{
	int		gnl_len;
	char	*gnl;
	int		new_line;

	info->height = 0;
	gnl = get_next_line(fd);
	info_map_init(gnl, info, fd);
	gnl_len = ft_strlen(gnl);
	info->width = gnl_len - 1;
	while (gnl)
	{
		info->height++;
		new_line = check_rect(gnl);
		if (gnl_len != (ft_strlen(gnl) + new_line))
		{
			free(gnl);
			free_init_map_error_handle("Map should be rectangular", &fd, info);
		}
		free(gnl);
		gnl = get_next_line(fd);
		if (gnl)
			fill_initial_map(info, gnl, fd);
	}
	close(fd);
}

static void	info_map_init(char *gnl, t_game *info, int fd)
{
	info->initial_map = ft_strjoin("", gnl);
	if (!info->initial_map)
	{
		free(gnl);
		error_handling("info->initial_map not allocated", &fd);
	}
}

void	fill_initial_map(t_game *info, char *gnl, int fd)
{
	char	*temp;

	temp = info->initial_map;
	info->initial_map = ft_strjoin(temp, gnl);
	if (!info->initial_map)
	{
		close(fd);
		free(temp);
		free(gnl);
		free_info_error_handling("info->initial_map not allocated", &fd, info);
	}
	free(temp);
}

int	check_rect(char *gnl)
{
	int	new_line;

	new_line = 0;
	if (gnl[ft_strlen(gnl) - 1] != '\n')
		new_line = 1;
	else
		new_line = 0;
	return (new_line);
}

char	**split_buffer(t_game *info, int *esc, int *coin, int *pawn)
{
	char	**spl_buf;
	int		i;

	i = 0;
	spl_buf = ft_split(info->initial_map, '\n');
	if (!spl_buf)
		error_handling("Split failed", NULL);
	info->split_map = ft_split(info->initial_map, '\n');
	while (spl_buf[i])
	{
		check_exit_coin_pawn(spl_buf[i], esc, coin, pawn);
		i++;
	}
	return (spl_buf);
}
