/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:00:00 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/06 12:00:00 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_wall_textures(t_game *game)
{
	int				i;
	mlx_texture_t	*tex;

	i = 0;
	while (i < 4)
	{
		if (!game->tex_paths[i])
			return (1);
		tex = mlx_load_png(game->tex_paths[i]);
		if (!tex)
			return (1);
		game->walls[i].tex = tex;
		game->walls[i].width_mask = tex->width - 1;
		game->walls[i].height_mask = tex->height - 1;
		i++;
	}
	return (0);
}

int	load_assets(t_game *game)
{
	if (!game)
		return (1);
	if (!game->mlx)
		return (1);
	game->assets = ft_tabinit(64);
	if (!game->assets)
		return (1);
	if (load_images(game, "p_0", "./assets/player/p_0.png", 5))
		return (1);
	if (load_wall_textures(game))
		return (1);
	return (0);
}
