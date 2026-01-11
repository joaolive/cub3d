/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:48:17 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/09 16:10:20 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fill_block(uint64_t *buffer, uint64_t pattern, uint64_t size)
{
	uint64_t	i;

	i = 0;
	while ((i + 8) <= size)
	{
		buffer[i] = pattern;
		buffer[i + 1] = pattern;
		buffer[i + 2] = pattern;
		buffer[i + 3] = pattern;
		buffer[i + 4] = pattern;
		buffer[i + 5] = pattern;
		buffer[i + 6] = pattern;
		buffer[i + 7] = pattern;
		i += 8;
	}
	while (i < size)
		buffer[i++] = pattern;
}

void	render_bg(t_game *game)
{
	uint64_t	*buffer;
	uint64_t	ceiling_pattern;
	uint64_t	floor_pattern;
	uint32_t	color;
	uint64_t	total_qwords;
	uint64_t	half_qwords;

	buffer = (uint64_t *)game->img->pixels;
	color = game->tex.ceiling;
	ceiling_pattern = ((uint64_t)color << 32) | color;
	color = game->tex.floor;
	floor_pattern = ((uint64_t)color << 32) | color;
	total_qwords = (game->img->width * game->img->height) / 2;
	half_qwords = total_qwords / 2;
	fill_block(buffer, ceiling_pattern, half_qwords);
	fill_block(buffer + half_qwords, floor_pattern, total_qwords - half_qwords);
}
