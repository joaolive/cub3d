/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_batch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:29:16 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 17:56:47 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_game *game, int32_t x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->mlx->width - 1;
	game->ray.dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	game->ray.dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	game->ray.map.x = (int)game->player.pos.x;
	game->ray.map.y = (int)game->player.pos.y;
	game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
	game->ray.step.x = 1 - ((game->ray.dir.x < 0) << 1);
	game->ray.side_dist.x = (game->ray.step.x * (game->ray.map.x - game->player.pos.x)
			+ (game->ray.step.x > 0)) * game->ray.delta_dist.x;
	game->ray.step.y = 1 - ((game->ray.dir.y < 0) << 1);
	game->ray.side_dist.y = (game->ray.step.y * (game->ray.map.y - game->player.pos.y)
			+ (game->ray.step.y > 0)) * game->ray.delta_dist.y;
}

static void	perform_dda(t_game *game)
{
	int	hit;
	int	move_x;

	hit = 0;
	while (hit == 0)
	{
		move_x = game->ray.side_dist.x < game->ray.side_dist.y;
		game->ray.side_dist.x += game->ray.delta_dist.x * move_x;
		game->ray.side_dist.y += game->ray.delta_dist.y * !move_x;
		game->ray.map.x += game->ray.step.x * move_x;
		game->ray.map.y += game->ray.step.y * !move_x;
		game->ray.side = !move_x;
		hit = game->map.grid[game->ray.map.y][game->ray.map.x] > '0';
	}
}

static void	calc_wall_geometry(t_game *game, int32_t i)
{
	double	dists[2];
	int		screen_h;
	int		line_h;
	int32_t	raw_y;

	game->batch.is_shaded[i] = game->ray.side == 0 && game->ray.dir.x > 0;
	dists[0] = game->ray.side_dist.x - game->ray.delta_dist.x;
	dists[1] = game->ray.side_dist.y - game->ray.delta_dist.y;
	screen_h = game->mlx->height;
	game->ray.perp_dist = dists[game->ray.side];
	line_h = (int32_t)(screen_h / (game->ray.perp_dist + 1e-10));
	game->ray.line_height = line_h;
	raw_y = (screen_h >> 1) - (line_h >> 1);
	game->batch.draw_start[i] = raw_y & ~(raw_y >> 31);
	raw_y = (screen_h >> 1) + (line_h >> 1);
	game->batch.draw_end[i] = (screen_h - 1) + ((raw_y - screen_h + 1)
			& ((raw_y - screen_h + 1) >> 31));
	game->batch.dist[i] = (float) game->ray.perp_dist;
}

static void	tex_info(t_game *game, t_ray *ray, t_batch *batch, int i)
{
	t_wall_tex		*wall;
	double			wall_x;
	const double	pos[2] = {game->player.pos.y, game->player.pos.x};
	const double	dir[2] = {ray->dir.y, ray->dir.x};
	static int		ids[4] = {TEX_WEST, TEX_EAST, TEX_NORTH, TEX_SOUTH};

	batch->tex_id[i] = ids[(ray->side << 1)
		| (((double *)&ray->dir.x)[ray->side] > 0)];
	wall = &game->walls[batch->tex_id[i]];
	wall_x = pos[ray->side] + ray->perp_dist * dir[ray->side];
	wall_x -= floor(wall_x);
	batch->tex_x[i] = (int)(wall_x * (double)wall->tex->width);
	if (ray->side ^ (((double *)&ray->dir.x)[ray->side] > 0))
		batch->tex_x[i] = (wall->tex->width - batch->tex_x[i] - 1);
	batch->step[i] = 1.0 * wall->tex->height / ray->line_height;
	batch->tex_pos[i] = (batch->draw_start[i] - (game->mlx->height >> 1)
			+ (ray->line_height >> 1)) * batch->step[i];
}

void	calculate_batch(t_game *game, int32_t start_x)
{
	int32_t	i;
	int32_t	screen_x;

	i = -1;
	while (++i < BATCH_SIZE)
	{
		screen_x = start_x + i;
		if (screen_x >= game->mlx->width)
			break ;
		setup_ray(game, screen_x);
		perform_dda(game);
		calc_wall_geometry(game, i);
		tex_info(game, &game->ray, &game->batch, i);
	}
}
