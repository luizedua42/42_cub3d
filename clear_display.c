/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:48:30 by luizedua          #+#    #+#             */
/*   Updated: 2023/12/11 13:48:35 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_display(t_mlx *mlx)
{
	int x;
	int y;
	
	y = 0;
	while(y < WIN_H)
	{
		x = 0;
		while(x < WIN_W)
		{
			paint_img(mlx, 0x0, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->p_win, mlx->p_img, 0, 0);
}