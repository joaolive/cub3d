/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:45:39 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/07 11:27:11 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"

// --- BITMASKS DE MOVIMENTO ---
#define FLAG_MOVE_N (1 << 0) // 0000 0001
#define FLAG_MOVE_S (1 << 1) // 0000 0010
#define FLAG_MOVE_W (1 << 2) // 0000 0100
#define FLAG_MOVE_E (1 << 3) // 0000 1000
#define FLAG_ROT_L (1 << 4) // 0001 0000
#define FLAG_ROT_R (1 << 5) // 0010 0000

// --- ÍNDICES DE TEXTURA ---
#define TEX_EAST 0
#define TEX_WEST 1
#define TEX_NORTH 2
#define TEX_SOUTH 3

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		pitch;
	uint8_t	mov_flags;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		px;
	int		py;
	char	pdir;
}	t_map;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	uint32_t		width_mask; // se width é 64, mask é 63
	uint32_t		height_mask;
}	t_wall_tex;

typedef struct s_tex
{
	t_wall_tex	walls[4]; // [0]=N, [1]=S, [2]=W, [3]=E
	uint32_t	floor; // RGBA hex
	uint32_t	ceiling; // RGBA hex
}	t_tex;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x; // ponto exato onde o raio bateu na parede (0 a 1)
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side; // 0 = vertical, 1 = horizontal
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_player	player;
	t_tex		tex;
	t_ray		ray;
	double		delta_time;
}	t_game;

