/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:42:50 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/05 13:36:28 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/tsimitop/Documents/Testing/so_long_and_thanks_for_all_the_fish/so_long.h"

int	main(int argc, char **argv)
{
	t_game	*info;

	info = ft_calloc(1, sizeof(t_game));
	if (argc == 2)
	{
		run_all_checks(argv, info);
		// map_height_width(argv, node);
	}
	else
		ft_printf("Arguments should be: ./so_long map.ber\n"); //If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way, and return "Error\n" followed by 
	ft_printf("You reached the end of the main function...");
	return (0);
}

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
			error_handling("You need at least one collectable in your map", NULL);
		if (esc != 1)
			error_handling("You need one exit per map, no more, no less", NULL);
		if (pawn != 1)
			error_handling("One player is required to play, no more, no less", NULL);
	}
	assign_values(info, &esc, &coin, &pawn);
	check_walls_paths(spl_buf, info);
}

void	assign_values(t_game *info, int *esc, int *coin, int *pawn)
{
	info->escape = *esc;
	info->coins = *coin;
	info->pawn = *pawn;
}

void	check_walls_paths(char **spl_buf, t_game *info)
{
	check_walls(spl_buf, info);
	// check_paths(spl_buf);
}

void	check_walls(char **spl_buf, t_game *info)
{
	int	i;
	int	j;
(void)info;
	i = 0;
	j = 0;
	while (spl_buf[i] != NULL && spl_buf[i][j] != '\0')
	{
		while (spl_buf[i][j] != '\0')
		{
			if (spl_buf[0][j] != '1' || spl_buf[i][0] != '1' || spl_buf[i][info->width - 1] != '1' || spl_buf[info->height - 1][j] != '1')
				error_handling("Your map should be surrouded by walls", NULL);
			j++;
		}
		j = 0;
		i++;
	}
}

// void	check_paths(char **spl_buf)
// {

// }

void	check_map_file_cont(char **argv, t_game *info)
{
	int	fd;

	if (ft_strncmp(".ber", argv[1] + (ft_strlen(argv[1]) - 4), 5) != 0)
		error_handling("Wrong file type. Map should be of type .ber", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_handling("Unable to open file or file does not exist", NULL);
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
		error_handling("Map appears to be empty", NULL);
	ft_strlcpy(info->buffer, gnl, 450);
	gnl_len = ft_strlen(gnl);
	info->width = gnl_len - 1;
	while (gnl != NULL)
	{
		count_height++;
		new_line = check_rect(gnl);
		if (gnl_len != (ft_strlen(gnl) + new_line))
			error_handling("Map should be rectangular", &fd);// add fd and condition if NULL inside function
		gnl = get_next_line(fd);
		if (gnl)
			ft_strlcat(info->buffer, gnl, 450);
	}
	info->height = count_height;
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
		error_handling("Split failed", NULL);
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

void	error_handling(char *str, int *fd)
{
	if (fd)
		close(*fd);
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(0);
}
