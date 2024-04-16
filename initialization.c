/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:27:42 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/16 20:06:56 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_render(t_game *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	render_map_base(info);
	while (info->split_map[i])
	{
		while (info->split_map[i][j])
		{
			put_coin_pawn(info, info->split_map[i][j], j, i);
			j++;
		}
		i++;
		j = 0;
	}
}

void	render_map_base(t_game *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info->split_map[i])
	{
		while (info->split_map[i][j])
		{
			put_wall_floor(info, info->split_map[i][j], j, i);
			j++;
		}
		i++;
		j = 0;
	}
}

void	put_coin_pawn(t_game *info, char c, int i, int j)
{
	if (c == 'C')
	{
		if (mlx_image_to_window(info->mlx, info->image_coin, \
		i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL);
	}
	else if (c == 'P')
	{
		if (mlx_image_to_window(info->mlx, info->image_pawn, \
		i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL);
	}
}

void	put_wall_floor(t_game *info, char c, int i, int j)
{
	if (c == '0' || c == 'C' || c == 'P')
	{
		if (mlx_image_to_window(info->mlx, info->image_floor, \
		i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL);
	}
	else if (c == '1')
	{
		if (mlx_image_to_window(info->mlx, info->image_wall, \
		i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL);
	}
	else if (c == 'E')
	{
		if (mlx_image_to_window(info->mlx, info->image_exit, \
		i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL);
	}
}

static mlx_image_t	*load_image(char *str, t_game *info)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(str);
	if (!texture)
		error_handling("texture", NULL);
	img = mlx_texture_to_image(info->mlx, texture);
	if (!img)
		error_handling("texture", NULL);
	mlx_delete_texture(texture);
	mlx_resize_image(img, TILE_SIZE, TILE_SIZE);
	return (img);
}

void	loading_images(t_game *info)
{
	info->image_pawn = load_image("png_folder/player.png", info);
	info->image_floor = load_image("png_folder/floor.png", info);
	info->image_wall = load_image("png_folder/wall.png", info);
	info->image_exit = load_image("png_folder/exit.png", info);
	info->image_coin = load_image("png_folder/collectible.png", info);
}
