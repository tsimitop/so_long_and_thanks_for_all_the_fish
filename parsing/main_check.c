/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:17:34 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:24:01 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	run_all_checks(char **argv, t_game *info)
{
	int		esc;
	int		coin;
	int		pawn;
	char	**spl_buf;

	esc = 0;
	coin = 0;
	pawn = 0;
	check_map_file_cont(argv, info);
	spl_buf = split_buffer(info, &esc, &coin, &pawn);
	if (!spl_buf)
		return ;
	if (spl_buf && (coin < 1 || esc != 1 || pawn != 1))
	{
		free_split(spl_buf);
		free_split(info->split_map);
		if (coin < 1)
			error_handling("Put at least one collectable in your map", NULL);
		if (esc != 1)
			error_handling("Put one exit per map, no more, no less", NULL);
		if (pawn != 1)
			error_handling("One player allowed, no more, no less", NULL);
	}
	assign_values(info, &esc, &coin);
	check_walls_paths(spl_buf, info);
}

void	check_map_file_cont(char **argv, t_game *info)
{
	int		fd;
	int		read_int;
	char	buffer[1];

	if (ft_strncmp(".ber", argv[1] + (ft_strlen(argv[1]) - 4), 5) != 0)
		error_handling("Wrong file type. Map should be of type .ber", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_handling("Unable to open file or file does not exist", NULL);
	read_int = read(fd, buffer, 1);
	if (read_int == 0)
		error_handling("Map appears to be empty", &fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_handling("Unable to open file or file does not exist", NULL);
	fill_buffer_check_rect_empty(fd, info);
}

void	assign_values(t_game *info, int *esc, int *coin)
{
	info->escape = *esc;
	info->coins = *coin;
	info->init_coins = *coin;
}

void	check_walls_paths(char **spl_buf, t_game *info)
{
	int		y;
	int		x;

	y = 0;
	while (spl_buf[y])
	{
		x = 0;
		while (spl_buf[y][x])
		{
			set_exit_pawn_positions(info, spl_buf[y][x], x, y);
			x++;
		}
		y++;
	}
	info->dimentions.x = info->width;
	info->dimentions.y = info->height;
	check_walls(spl_buf, info);
	check_paths(spl_buf, info);
}

void	set_exit_pawn_positions(t_game *info, char c, int x, int y)
{
	if (c == 'E')
	{
		info->exit_position.x = x;
		info->exit_position.y = y;
	}
	if (c == 'P')
	{
		info->pawn_position.x = x;
		info->pawn_position.y = y;
	}
}
