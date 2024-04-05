/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:49:46 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/05 11:40:00 by tsimitop         ###   ########.fr       */
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
	ft_strlcpy(node->buffer, gnl, 450);
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
		ft_strlcat(node->buffer, gnl, 450);
	}
	//map wall accesibility?
	close(fd);
}

array = ft_split(node->buffer, '\n');

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

// ft_printf("ft_strlen(1111111111111111111) = %i\n", ft_strlen("1111111111111111111"));
	fd = open(argv[1], O_RDONLY);
	gnl = get_next_line(fd);
	x = ft_strlen(gnl);
	y = 0;
	while (gnl != NULL)
	{
		gnl = get_next_line(fd);
		y++;
	}
	if (x < 2 || y < 2 || x + 1 > 20 || y > 20)
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
