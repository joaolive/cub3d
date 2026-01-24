/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:25:21 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/24 17:52:06 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// rotaciona o vetor de direção e o vetor do plano da câmera
static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	// rotacionando a direção
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
	// rotacionando o plano da câmera (plane)
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
}

static void	move_player(t_player *player, t_map *map, double move_x, double move_y)
{
	int	map_grid_x;
	int	map_grid_y;
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = (int)(player->pos_x + move_x);
	map_grid_y = (int)player->pos_y;
	if (map->grid[map_grid_y][new_pos_x] != '1') //TODO depois tenho que alterar para aceitar outros obstáculos
		player->pos_x += move_x;
	new_pos_y = (int)(player->pos_y + move_y);
	map_grid_x = (int)player->pos_x;
	if (map->grid[new_pos_y][map_grid_x] != '1') //TODO mesma coisa do outro
		player->pos_y += move_y;
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
		((game->player.dir_x * fwd) - (game->player.dir_y * side)) * speed,
		((game->player.dir_y * fwd) + (game->player.dir_x * side)) * speed);
	rot = (!!(game->player.mov_flags & FLAG_ROT_R))
		- (!!(game->player.mov_flags & FLAG_ROT_L));
	if (rot)
		rotate_player(&game->player, rot * game->mlx->delta_time * 3.0);
}
