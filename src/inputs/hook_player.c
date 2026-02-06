/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:25:21 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 09:33:02 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_speed) - player->dir.y * sin(rot_speed);
	player->dir.y = old_dir_x * sin(rot_speed) + player->dir.y * cos(rot_speed);

	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_speed) - player->plane.y * sin(rot_speed);
	player->plane.y = old_plane_x * sin(rot_speed) + player->plane.y * cos(rot_speed);
}

static void	move_player(t_player *player, t_map *map, double move_x, double move_y)
{
	t_ivec	map_grid;
	t_ivec	new_pos;

	new_pos.x = (int)(player->pos.x + move_x);
	map_grid.y = (int)player->pos.y;
	if (map->grid[map_grid.y][new_pos.x] != '1')
		player->pos.x += move_x;
	new_pos.y = (int)(player->pos.y + move_y);
	map_grid.x = (int)player->pos.x;
	if (map->grid[new_pos.y][map_grid.x] != '1')
		player->pos.y += move_y;
}

void	hook_player(t_game *game)
{
	double	speed;
	int		fwd;
	int		side;
	int		rot;

	speed = game->mlx->delta_time * 3.0;
	fwd = (!!(game->player.mov_flags & FLAG_MOVE_W))
		- (!!(game->player.mov_flags & FLAG_MOVE_S));
	side = (!!(game->player.mov_flags & FLAG_MOVE_D))
		- (!!(game->player.mov_flags & FLAG_MOVE_A));
	speed *= (1.0 - (0.292893 * ((fwd != 0) & (side != 0))));
	move_player(&game->player, &game->map,
		((game->player.dir.x * fwd) - (game->player.dir.y * side)) * speed,
		((game->player.dir.y * fwd) + (game->player.dir.x * side)) * speed);
	rot = (!!(game->player.mov_flags & FLAG_ROT_R))
		- (!!(game->player.mov_flags & FLAG_ROT_L));
	if (rot)
		rotate_player(&game->player, rot * game->mlx->delta_time * 3.0);
}
