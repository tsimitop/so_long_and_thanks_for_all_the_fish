/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:49:46 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/02 22:56:49 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/tsimitop/Documents/Testing/so_long_and_thanks_for_all_the_fish/so_long.h"

int	main(int argc, char **argv)
{
	t_game	*node;

	node = ft_calloc(1, sizeof(t_game));
	if (argc == 2)
	{
		check_map_file_chars_shape(argv);
		map_height_width(argv, node);
	}
	else
		ft_printf("Arguments should be: ./so_long map.ber\n"); //If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way, and return "Error\n" followed by 
	ft_printf("You reached the end of the main function...");
	return (0);
}

void	check_map_file_chars_shape(char **argv)
{
	int	fd;
	int esc;
	int coin;
	int pawn;

	if (ft_strncmp(".ber", argv[1] + (ft_strlen(argv[1]) - 4), 5) != 0)
		error_handling("Wrong file extention. Map should be of type .ber");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_handling("Unable to open file or file does not exist");
	esc = 0;
	coin = 0;
	pawn = 0;
	check_map_empty_rect(fd, &esc, &coin, &pawn);
	if (coin < 1)
		error_handling("You need at least one collectable in your map");
	if (esc != 1)
		error_handling("You need one exit per map, no more, no less");
	if (pawn != 1)
		error_handling("One player is required to play, no more, no less");
}

void	check_map_empty_rect(int fd, int *esc, int *coin, int *pawn)
{
	int		gnl_len;
	char	*gnl;
	int		new_line;

	gnl = get_next_line(fd);
	if (!gnl)
		error_handling("Map appears to be empty");
	gnl_len = ft_strlen(gnl);
	while (gnl != NULL)
	{
		check_exit_coin_pawn(gnl, esc, coin, pawn);
		if (gnl[ft_strlen(gnl) - 1] != '\n')
			new_line = 1;
		else
			new_line = 0;
		if (gnl_len != (ft_strlen(gnl) + new_line))
		{
			close(fd);
			error_handling("Map should be rectangular");
		}
		gnl = get_next_line(fd);
	}
	//map wall accesibility?
	close(fd);
}

void	check_exit_coin_pawn(char *str, int *esc, int *coin, int *pawn)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && str[i] != 'P' \
			&& str[i] != 'E' && str[i] != '\n')
			error_handling("Invalid character in map.");
		if (str[i] == 'C')
			(*coin)++;
		else if (str[i] == 'E')
			(*esc)++;
		else if (str[i] == 'P')
			(*pawn)++;
		i++;
	}
}

void	error_handling(char *str)
{
	ft_printf("\033[0;31mError\033[0m\n");
	ft_printf("%s\n", str);
	exit(0);
}

void	map_height_width(char **argv, t_game *node)
{
	int		x; //width; //x columns
	int		y; //height; //y rows
	int		fd;
	char	*gnl;

	fd = open(argv[1], O_RDONLY);
	gnl = get_next_line(fd);
	x = ft_strlen(gnl);
	y = 0;
	while (gnl != NULL)
	{
		gnl = get_next_line(fd);
		y++;
	}
	if (x < 2 || y < 2 || x > 20 || y > 20)
	{
		free(node);
		error_handling("Height and width should not exeed 20 neither be < 2");
	}
	else
	{
		node->width = x + 1;
// ft_printf("node->width = %i\n", node->width);
		node->height = y;
// ft_printf("node->height = %i\n", node->height);
// exit(0);
	}
	close(fd);
	check_edges(node, argv);
}

void	check_edges(t_game *node, char **argv)
{
	char	array[node->width][node->height];
	int		rows;
	int		columns;
	int		bytes_read;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	
	rows = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, node->buffer, 500);
		if (bytes_read == -1)
			error_handling("couldnt read from file");
	}
// ft_printf("bytes_read = %i\n", bytes_read);
	while (i < node->height)
	{
		j = 0;
		while(j < node->width - 1)
		{
			array[i][j] = node->buffer[k];
if (i == 0)
{
	ft_printf("array[i][j] = %c\t", array[i][j]);
	ft_printf("j = %i\n", j);
}
// ft_printf("node->buffer[k] = %c | array[i][j] = %c | k = %i\n", node->buffer[k], array[i][j], k); //seems to copy properly
// ft_printf("i =  %i\t", i);
// ft_printf("j =  %i\n", j);
			j++;
			k++;
		}
		i++;
// if (i == 10)
	// exit(0);
	}
ft_printf("____________________________________________________\n");
// exit(0);
rows = 0;
columns = 0;
	while (rows < node->height - 1)
	{
ft_printf("____________________________________________________\n");
		columns = 0;
		while (rows == 0 && columns < node->width - 1) // && array[rows][columns] != '\n'
		{
ft_printf("array[rows][columns] = %c | rows = %i | columns = %i\n", array[rows][columns], rows, columns);
ft_printf("BONJOUR\n");
			if (array[rows][columns] != '1' && array[rows][columns] != '\n')
				error_handling("Your map should be surrouded by walls");
			columns++;
		}
		if (rows > 0 && rows < node->height - 1) // && columns < node->width
		{
ft_printf("HEY\n");
ft_printf("array[rows][columns] = %c | rows = %i | columns = %i\n", array[rows][columns], rows, columns);
ft_printf("HEY\n");
			if (array[rows][0] != '1' || array[rows][node->width - 2] != '1')
				error_handling("Your map should be surrouded by walls");
		}
		while (rows == node->height - 1 && columns < node->width - 1)
		{
ft_printf("HALLO\n");
			if (array[rows][columns] != '1')
				error_handling("Your map should be surrouded by walls");
			columns++;
		}
		rows++;
	}
ft_printf("_________________fin check edges_____________________________\n");
}
