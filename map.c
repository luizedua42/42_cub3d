/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:51:57 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/10 11:58:26 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_creation(t_map *map, t_mlx *mlx)
{
	char	**bitmap;
	int i;

	i = 8;
	bitmap = calloc(9, sizeof(char *));
	while (i < 0)
	{
		bitmap[i] = calloc(9, sizeof(char));
	}
	bitmap[0] = "11111111";
	bitmap[1] = "10010001";
	bitmap[2] = "10010001";
	bitmap[3] = "10010001";
	bitmap[4] = "10000001";
	bitmap[5] = "10000101";
	bitmap[6] = "10000001";
	bitmap[7] = "11111111";
	map->x = 0;
	map->y = 0;
	ceiling_color(0xFFFF, mlx);
	floor_color(0xFFAAFF, mlx);
	// while (map->y <= 7)
	// {
	// 	map->x = 0;
	// 	while (map->x <= 7)
	// 	{
	// 		if (bitmap[map->y][map->x] == '1')
	// 			draw_square(mlx, map->x * 64, map->y * 64, 0xFFFFFF);
	// 		map->x++;
	// 	}
	// 	map->y++;
	// }
	return (bitmap);
}

void draw_square(t_mlx *mlx, int map_x, int map_y, int color)
{
	int y = 0;
	while (y < 63)
	{
		int x = 0;
		while (x < 63)
		{
			paint_img(mlx, color, map_x + x, map_y + y);
			x++;
		}
		y++;
	}
}