/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 09:46:23 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/02 17:55:27 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*load_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		printf("Erro ao carregar textura: %s\n", path);
		return (NULL);
	}
	return (texture);
}

static uint8_t	load(t_game *game, char *key, char *path, uint32_t count)
{
	mlx_texture_t	*tex;
	char			*key_idx;
	char			*path_idx;
	uint8_t			i;

	key_idx = key + ft_strlen(key) -1;
	path_idx = ft_strrchr(path, '.') - 1;
	i = -1;
	while (++i < count)
	{
		*key_idx = i + '0';
		*path_idx = i + '0';
		tex = load_texture(path);
		if (!tex || ft_htabinsert(game->assets, key, tex))
		{
			//ft_terminate(game); // TODO
			return (1);
		}
	}
	return (0);
}

uint8_t	load_textures(t_game *game, char *key, char *path, uint32_t count)
{
	char	*k;
	char	*p;
	uint8_t	res;

	k = ft_strdup(key);
	p = ft_strdup(path);
	res = 0;
	if (k && p)
		res = load(game, k, p, count);
	free(k);
	free(p);
	return (res);
}
