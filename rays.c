/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:05 by luizedua          #+#    #+#             */
/*   Updated: 2023/12/13 14:59:44 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void h_rays(t_mlx *mlx, char **map)
{
	int r,mx,my;
	float rx,ry, ra, xo, yo;
	
	ra = mlx->p1.ang;
	for(r=0;r<1;r++)
	{
		float aTan=-1/tan(ra);
		if (ra > M_PI)
		{
			ry = (((int)mlx->p1.y >> 6) << 6) - 0.0001;
			rx = (mlx->p1.y - ry) * aTan+mlx->p1.x; 
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < M_PI)
		{
			ry = (((int)mlx->p1.y >> 6) << 6) + 64;
			rx = (mlx->p1.y - ry) * aTan + mlx->p1.x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == M_PI)
		{
			rx = mlx->p1.x;
			ry = mlx->p1.y;
		}
		while (true)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
				break;
			rx += xo;
			ry += yo;
		}
		draw_rays(mlx, rx, ry);
	}
}

void v_rays(t_mlx *mlx, char **map)
{
	int r,mx,my;
	float rx,ry, ra, xo, yo;
	
	ra = mlx->p1.ang;
	for(r=0;r<1;r++)
	{
		float nTan=-tan(ra);
		if (ra > (M_PI / 2) && ra < (3 * M_PI / 2))
		{
			rx = (((int)mlx->p1.x >> 6) << 6) - 0.0001;
			ry = (mlx->p1.x - rx) * nTan+mlx->p1.y; 
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < (M_PI / 2) || ra > (3 * M_PI / 2))
		{
			rx = (((int)mlx->p1.x >> 6) << 6) + 64;
			ry = (mlx->p1.x - rx) * nTan + mlx->p1.y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == (M_PI / 2) || ra == (3 * M_PI / 2))
		{
			rx = mlx->p1.x;
			ry = mlx->p1.y;
		}
		while (true)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
				break;
			rx += xo;
			ry += yo;
		}
		draw_rays(mlx, rx, ry);
	}
}

void	draw_rays(t_mlx *mlx, float x2, float y2)
{
	float	step;
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	i;

	dx = x2 - mlx->p1.x;
	dy = y2 - mlx->p1.y;
	step = 0;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = mlx->p1.x;
	y = mlx->p1.y;
	i = 0;
	while (i <= (int)step)
	{
		if (x < 0 || y < 0 || x > WIN_W || y >  WIN_H)
			break ;
		paint_img(mlx, 0xFF, x, y);
		x += dx;
		y += dy;
		i++;
	}
}
