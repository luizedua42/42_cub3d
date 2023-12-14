/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:01:11 by luizedua          #+#    #+#             */
/*   Updated: 2023/12/14 16:02:41 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float distance(float x1, float x2, float y1, float y2);
void paint_walls(t_mlx *mlx, int map_x, int map_y);
void	draw_walls(t_mlx *mlx, int r);
void draw_lines(t_mlx *mlx, int map_x, int map_y, int color, float offr);

void h_rays(t_mlx *mlx, char **map)
{
	int mx,my;
	float rx,ry, xo, yo;

	mlx->rays.hd = 10000;
	mlx->rays.hx = mlx->p1.x;
	mlx->rays.hy = mlx->p1.y;
	float aTan=-1/tan(mlx->rays.ra);
	if (mlx->rays.ra > M_PI)
	{
		ry = (((int)mlx->p1.y >> 6) << 6) - 0.0001;
		rx = (mlx->p1.y - ry) * aTan+mlx->p1.x; 
		yo = -64;
		xo = -yo * aTan;
	}
	if (mlx->rays.ra < M_PI)
	{
		ry = (((int)mlx->p1.y >> 6) << 6) + 64;
		rx = (mlx->p1.y - ry) * aTan + mlx->p1.x;
		yo = 64;
		xo = -yo * aTan;
	}
	if (mlx->rays.ra == 0 || mlx->rays.ra == M_PI)
	{
		rx = mlx->p1.x;
		ry = mlx->p1.y;
	}
	while (true)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
		{
			mlx->rays.hx = rx;
			mlx->rays.hy = ry;
			mlx->rays.hd = distance(mlx->p1.x, mlx->rays.hx, mlx->p1.y, mlx->rays.hy);
			break;
		}
		rx += xo;
		ry += yo;
	}
}

void v_rays(t_mlx *mlx, char **map)
{
	int mx,my;
	float rx,ry, xo, yo;

	mlx->rays.vd = 10000;
	mlx->rays.vx = mlx->p1.x;
	mlx->rays.vy = mlx->p1.y;
	float nTan=-tan(mlx->rays.ra);
	if (mlx->rays.ra > (M_PI / 2) && mlx->rays.ra < (3 * M_PI / 2))
	{
		rx = (((int)mlx->p1.x >> 6) << 6) - 0.0001;
		ry = (mlx->p1.x - rx) * nTan+mlx->p1.y; 
		xo = -64;
		yo = -xo * nTan;
	}
	if (mlx->rays.ra < (M_PI / 2) || mlx->rays.ra > (3 * M_PI / 2))
	{
		rx = (((int)mlx->p1.x >> 6) << 6) + 64;
		ry = (mlx->p1.x - rx) * nTan + mlx->p1.y;
		xo = 64;
		yo = -xo * nTan;
	}
	if (mlx->rays.ra == (M_PI / 2) || mlx->rays.ra == (3 * M_PI / 2))
	{
		rx = mlx->p1.x;
		ry = mlx->p1.y;
	}
	while (true)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
		{
			mlx->rays.vx = rx;
			mlx->rays.vy = ry;
			mlx->rays.vd = distance(mlx->p1.x, mlx->rays.vx, mlx->p1.y, mlx->rays.vy);
			break;
		}
		rx += xo;
		ry += yo;
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

	dx = x2  - mlx->p1.x;
	dy = y2  - mlx->p1.y;
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

float distance(float x1, float x2, float y1, float y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	rays(t_mlx *mlx, char ** map)
{
	int r = -1;
	mlx->rays.ra = mlx->p1.ang - RAD * 30;
	if(mlx->rays.ra < 0)
		mlx->rays.ra += 2 * M_PI;
	if (mlx->rays.ra > 2 * M_PI)
		mlx->rays.ra -= 2*M_PI;
	while (++r < 60)
	{
		h_rays(mlx, map);
		v_rays(mlx, map);
		if(mlx->rays.hd > mlx->rays.vd)
		{
			draw_rays(mlx, mlx->rays.vx, mlx->rays.vy);
			mlx->rays.fdist = mlx->rays.vd;
		}
		if (mlx->rays.hd < mlx->rays.vd)
		{
			draw_rays(mlx, mlx->rays.hx, mlx->rays.hy);
			mlx->rays.fdist = mlx->rays.hd;
		}
		draw_walls(mlx, r);
		mlx->rays.ra += RAD;
		if(mlx->rays.ra < 0)
			mlx->rays.ra = RAD * 359;
		if (mlx->rays.ra > 2 * M_PI)
			mlx->rays.ra = RAD - RAD;
	}
}

void	draw_walls(t_mlx *mlx, int r)
{
	float lineh;
	float lineo;
	
	lineh = ((8*8)*WIN_H)/mlx->rays.fdist;
	if (lineh > WIN_H)
		lineh =	WIN_H;
	lineo = (((float)WIN_H) - lineh) / 2;
	draw_lines(mlx, r*8+512, lineh+lineo, 0xFF0000, lineo);
}

void draw_lines(t_mlx *mlx, int map_x, int map_y, int color, float off)
{
	(void)off;
	int y = 0;
	while (y < map_y - off)
	{
		int x = map_x;
		while (x < map_x + 8)
		{
			if (map_x < WIN_W &&  map_y <= WIN_H)
				paint_img(mlx, color, x, off +  y);
			x++;
		}
		y++;
	}
}