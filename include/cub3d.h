/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:45:39 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 18:31:17 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"

// --- WINDOW ---
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define WIN_TITLE "Cub3d"

// Tamanho do bloco
#define BATCH_SIZE 8

// --- BITMASKS DE MOVIMENTO ---
#define FLAG_MOVE_W (1 << 0) // 0000 0001
#define FLAG_MOVE_S (1 << 1) // 0000 0010
#define FLAG_MOVE_A (1 << 2) // 0000 0100
#define FLAG_MOVE_D (1 << 3) // 0000 1000
#define FLAG_ROT_L (1 << 4) // 0001 0000
#define FLAG_ROT_R (1 << 5) // 0010 0000

// --- ÍNDICES DE TEXTURA ---
#define TEX_EAST 0
#define TEX_WEST 1
#define TEX_NORTH 2
#define TEX_SOUTH 3
#define TEX_VOID 255

typedef struct s_keymap
{
	keys_t	key;
	uint8_t	value;
}	t_keymap;

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ivec
{
	int32_t	x;
	int32_t	y;
}	t_ivec;

typedef struct s_player
{
	mlx_image_t	*img;
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	// int32_t		pitch;
	uint8_t		mov_flags;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int32_t		width;
	int32_t		height;
}	t_map;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	uint32_t		width_mask; // se width é 64, mask é 63
	uint32_t		height_mask;
}	t_wall_tex;

typedef struct	s_batch
{
	float		step[BATCH_SIZE];
	float		tex_pos[BATCH_SIZE];
	float		dist[BATCH_SIZE];
	int32_t		draw_start[BATCH_SIZE];
	int32_t		draw_end[BATCH_SIZE];
	uint16_t	tex_x[BATCH_SIZE];
	uint8_t		tex_id[BATCH_SIZE];
	uint8_t		is_shaded[BATCH_SIZE];
}	t_batch;

typedef struct s_ray
{
	t_vec		dir;
	t_vec		side_dist;
	t_vec		delta_dist;
	t_ivec		map;
	t_ivec		step;
	double		perp_dist;
	double		wall_x; // ponto exato onde o raio bateu na parede (0 a 1)
	int32_t		line_height;
	uint8_t		side; // 0 = vertical, 1 = horizontal
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_htab		*assets;
	t_map		map;
	t_player	player;
	t_batch		batch;
	t_ray		ray;
	t_wall_tex	walls[4]; // [0]=N, [1]=S, [2]=W, [3]=E
	double		delta_time;
	uint32_t	floor; // RGBA hex
	uint32_t	ceiling; // RGBA hex
}	t_game;

// core
int			init_window(t_game *game);
void		game_loop(void *param);

// render
void		render_bg(t_game *game);

//raycast
void		raycast(t_game *game);
void		render_batch(t_game *game, int32_t start_x, int32_t i);
void		calculate_batch(t_game *game, int32_t start_x);

// input
void		key_handler(mlx_key_data_t key, void *param);
void		player_controls(mlx_key_data_t key, t_game *game);
void		hook_player(t_game *game);

// player
void		render_player(t_game *game);

// utils
mlx_image_t	*load_image(mlx_t *mlx, char *path);
uint32_t	apply_depth_shading(uint32_t rgba, float dist);
uint32_t	apply_wall_shading(uint32_t rgba);
uint32_t	lerp(uint32_t color, uint32_t fog_color, uint32_t t);

// mock
void		init_mock_map(t_game *game);
