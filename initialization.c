/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:27:42 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/07 18:43:16 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_init(t_game *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	info->split_map = ft_split(info->buffer, '\n');
	if (!info->split_map)
		error_handling("Split failed", NULL, info);
	while (info->split_map[i])
	{
		while (info->split_map[i][j])
		{
			put_image(info, info->split_map[i][j], i, j); //// just testing
			// put_image(info, info->split_map[i][j], i, j);
			j++;
		}
		i++;
		j = 0;
	}
}

void	put_image(t_game *info, char c, int i, int j)
{
	// if (c == '0')
	// 	floor;
	if (c == '0')
		put_element(info, i, j, "png_folder/floor.png");
	else if (c == '1')
		put_element(info, i, j, "png_folder/wall.png");
	else if (c == 'E')
		put_element(info, i, j, "png_folder/exit.png");
	else if (c == 'C')
		put_element(info, i, j, "png_folder/collectible.png");
	else if (c == 'P')
		put_element(info, i, j, "png_folder/player.png");
		// put_element(info, i, j, "png_folder/wall.png");
}

void	put_element(t_game *info, int i, int j, char *str)
{
	mlx_texture_t	*png;
	mlx_image_t		*img;

	i *= 32;
	j *= 32;
	png = mlx_load_png(str);
	if (!png)
		error_handling("PNG", NULL, info);
	img = mlx_texture_to_image(info->mlx, png);
	if (!img)
		error_handling("PNG", NULL, info);
	if (mlx_image_to_window(info->mlx, img, i, j))
		error_handling("Image", NULL, info);
	mlx_delete_texture(png);
}
