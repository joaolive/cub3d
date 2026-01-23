/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_batch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:29:16 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/23 18:28:14 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->mlx->width - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->step_x = 1 - ((ray->ray_dir_x < 0) << 1);
	ray->side_dist_x = (ray->step_x * (ray->map_x - game->player.pos_x)
			+ (ray->step_x > 0)) * ray->delta_dist_x;
	ray->step_y = 1 - ((ray->ray_dir_y < 0) << 1);
	ray->side_dist_y = (ray->step_y * (ray->map_y - game->player.pos_y)
			+ (ray->step_y > 0)) * ray->delta_dist_y;
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	int	hit;
	int	move_x;

	hit = 0;
	while (hit == 0)
	{
		move_x = ray->side_dist_x < ray->side_dist_y;
		ray->side_dist_x += ray->delta_dist_x * move_x;
		ray->side_dist_y += ray->delta_dist_y * !move_x;
		ray->map_x += ray->step_x * move_x;
		ray->map_y += ray->step_y * !move_x;
		ray->side = !move_x;
		hit = map->grid[ray->map_y][ray->map_x] > '0';
	}
	ray->hit_type = 0;
}

static void	calc_wall_geometry(t_game *game, t_ray *ray, int i)
{
	double	dists[2];
	int		screen_h;
	int		line_h;
	int		raw_y;

	dists[0] = ray->side_dist_x - ray->delta_dist_x;
	dists[1] = ray->side_dist_y - ray->delta_dist_y;
	ray->perp_wall_dist = dists[ray->side];
	screen_h = game->mlx->height;
	line_h = (int)(screen_h / ray->perp_wall_dist);
	ray->line_height = line_h;
	raw_y = (screen_h >> 1) - (line_h >> 1);
	ray->draw_start = raw_y & ~(raw_y >> 31);
	raw_y = (screen_h >> 1) + (line_h >> 1);
	ray->draw_end = (screen_h - 1) + ((raw_y - screen_h + 1)
			& ((raw_y - screen_h + 1) >> 31));
	game->batch.dist[i] = (float) ray->perp_wall_dist;
	game->batch.draw_start[i] = ray->draw_start;
	game->batch.draw_end[i] = ray->draw_end;
}

static void	tex_info(t_game *game, t_ray *ray, t_batch *batch, int i)
{
	t_wall_tex		*wall;
	double			wall_x;
	const double	pos[2] = {game->player.pos_y, game->player.pos_x};
	const double	dir[2] = {ray->ray_dir_y, ray->ray_dir_x};
	static int		ids[4] = {TEX_WEST, TEX_EAST, TEX_NORTH, TEX_SOUTH};

	if (ray->hit_type == -1)
	{
		batch->tex_id[i] = TEX_VOID;
		return ;
	}
	batch->tex_id[i] = ids[(ray->side << 1)
		| (((double *)&ray->ray_dir_x)[ray->side] > 0)];
	wall = &game->tex.walls[batch->tex_id[i]];
	wall_x = pos[ray->side] + ray->perp_wall_dist * dir[ray->side];
	wall_x -= floor(wall_x);
	batch->tex_x[i] = (int)(wall_x * (double)wall->tex->width);
	if (ray->side ^ (((double *)&ray->ray_dir_x)[ray->side] > 0))
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
		setup_ray(game, &game->ray, screen_x);
		perform_dda(&game->ray, &game->map);
		calc_wall_geometry(game, &game->ray, i);
		tex_info(game, &game->ray, &game->batch, i);
	}
}
