/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:13:51 by luizedua          #+#    #+#             */
/*   Updated: 2023/12/14 15:43:21 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Defines
# define RAD 0.0174533
# define WIN_W 1024
# define WIN_H 512
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
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		ang;
}				t_player;

typedef struct s_rays
{
	float		fdist;
	float		ra;
	float		hd;
	float		hx;
	float		hy;
	float		vd;
	float		vx;
	float		vy;
}				t_rays;

typedef struct s_map
{
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
char			**map_creation(t_map *map, t_mlx *mlx);
void			draw_p1line(t_mlx *mlx);
void			draw_rays(t_mlx *mlx, float x2, float y2);
void 			v_rays(t_mlx *mlx, char **map);
void			h_rays(t_mlx *mlx, char **map);
void			rays(t_mlx *mlx, char ** map);
void			draw_square(t_mlx *mlx, int map_x, int map_y, int color);

#endif
