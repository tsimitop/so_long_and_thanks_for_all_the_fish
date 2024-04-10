/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:42:50 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/10 19:40:42 by tsimitop         ###   ########.fr       */
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
		if (coin < 1)
			error_handling("You need at least one collectable in your map", NULL, info);
		if (esc != 1)
			error_handling("You need one exit per map, no more, no less", NULL, info);
		if (pawn != 1)
			error_handling("One player is required to play, no more, no less", NULL, info);
	}
	assign_values(info, &esc, &coin);
	check_walls_paths(spl_buf, info);
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
			if (spl_buf[y][x] == 'P')
			{
				info->pawn_position.x = x;
				info->pawn_position.y = y;
			}
			x++;
		}
		y++;
	}

	info->dimentions.x = info->width;
	info->dimentions.y = info->height;
	check_walls(spl_buf, info);
	check_paths(spl_buf, info);
}

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
			if (spl_buf[0][j] != '1' || spl_buf[i][0] != '1' || spl_buf[i][info->width - 1] != '1' || spl_buf[info->height - 1][j] != '1')
				error_handling("Your map should be surrouded by walls", NULL, info);
			j++;
		}
		j = 0;
		i++;
	}
}


void	check_map_file_cont(char **argv, t_game *info)
{
	int	fd;

	if (ft_strncmp(".ber", argv[1] + (ft_strlen(argv[1]) - 4), 5) != 0)
		error_handling("Wrong file type. Map should be of type .ber", NULL, info);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_handling("Unable to open file or file does not exist", NULL, info);
	fill_buffer_check_rect_empty(fd, info);
}

void	fill_buffer_check_rect_empty(int fd, t_game *info)
{
	int		gnl_len;
	char	*gnl;
	int		new_line;
	int		count_height;

	count_height = 0;
	gnl = get_next_line(fd);
	if (!gnl)
		error_handling("Map appears to be empty", NULL, info);
	ft_strlcpy(info->buffer, gnl, 4000);
	gnl_len = ft_strlen(gnl);
	info->width = gnl_len - 1;
	if (info->width > 40)
		error_handling("Map should not have width larger than 40", &fd, info);
	while (gnl != NULL)
	{
		count_height++;
		new_line = check_rect(gnl);
		if (gnl_len != (ft_strlen(gnl) + new_line))
			error_handling("Map should be rectangular", &fd, info);// add fd and condition if NULL inside function
		gnl = get_next_line(fd);
		if (gnl)
			ft_strlcat(info->buffer, gnl, 4000);
	}
	info->height = count_height;
	if (info->height > 40)
		error_handling("Map should not have height larger than 20", &fd, info);
	close(fd);
}

int	check_rect(char *gnl)
{
	int new_line;

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
	spl_buf = ft_split(info->buffer, '\n');
	if (!spl_buf)
		error_handling("Split failed", NULL, info);
	info->split_map = ft_split(info->buffer, '\n');
	while (spl_buf[i])
	{
		check_exit_coin_pawn(spl_buf[i], esc, coin, pawn);
		i++;
	}
	return (spl_buf);
}

void	check_exit_coin_pawn(char *str, int *esc, int *coin, int *pawn)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && str[i] != 'P' \
			&& str[i] != 'E' && str[i] != '\n')
			error_handling("Invalid character in map.", NULL, NULL); //fix ret to free node
		if (str[i] == 'C')
			(*coin)++;
		else if (str[i] == 'E')
			(*esc)++;
		else if (str[i] == 'P')
			(*pawn)++;
		i++;
	}
}

void	error_handling(char *str, int *fd, t_game *info)
{
	// if (info)
	// 	free(info);
	(void)info;
	if (fd)
		close(*fd);
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}
