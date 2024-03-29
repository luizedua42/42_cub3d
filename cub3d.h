/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:13:51 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/15 12:09:38 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Defines
# define RAD 0.0174533
# define WIN_W 800
# define WIN_H 600
# define FOV 60
// Includes
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>

// Structs
typedef struct s_player
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		ang;
}				t_player;

typedef struct s_rays
{
	double		fdist;
	double		ra;
	double		hd;
	double		hx;
	double		hy;
	double		vd;
	double		vx;
	double		vy;
}				t_rays;

typedef struct s_map
{
	char		**map;
	int			x;
	int			y;
}				t_map;

typedef struct s_mlx
{
	void		*p_win;
	void		*p_mlx;
	void		*p_img;
	char		*i_add;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	p1;
	t_map		map;
	t_rays		rays;
}				t_mlx;

// Funcs

int				close_win(t_mlx *mlx);
int				key_press(int key_code, t_mlx *mlx);
void			paint_img(t_mlx *mlx, int color, int x, int y);
void			clear_display(t_mlx *mlx);
void			map_creation(t_map *map);
void			draw_p1line(t_mlx *mlx);
void			draw_rays(t_mlx *mlx, double x2, double y2);
void			v_rays(t_mlx *mlx, char **map);
void			h_rays(t_mlx *mlx, char **map);
void			rays(t_mlx *mlx, char ** map);
void			draw_square(t_mlx *mlx, int map_x, int map_y, int color);
void			ceiling_color(int color, t_mlx* mlx);
void			floor_color(int color, t_mlx* mlx);
void			draw_map(t_map *map,  t_mlx *mlx, char **bitmap);

#endif
