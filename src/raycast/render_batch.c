/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_batch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:24:13 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 17:57:43 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_batch(t_game *game, int32_t start_x, int32_t i)
{
	int32_t		y;
	uint32_t	*pixels;
	t_wall_tex	*wall;
	int32_t		tex_y;
	uint32_t	color;

	pixels = (uint32_t *)game->img->pixels;
	while (++i < BATCH_SIZE)
	{
		if (start_x + i >= game->mlx->width)
			break ;
		y = game->batch.draw_start[i];
		wall = &game->walls[game->batch.tex_id[i]];
		while (y < game->batch.draw_end[i])
		{
			tex_y = (int)game->batch.tex_pos[i] & (wall->tex->height - 1);
			game->batch.tex_pos[i] += game->batch.step[i];
			color = ((uint32_t *)wall->tex->pixels)[wall->tex->width * tex_y
				+ game->batch.tex_x[i]];
			if (game->batch.is_shaded[i])
				color = apply_wall_shading(color);
			//color = apply_depth_shading(color, game->batch.dist[i]);
			pixels[y * game->mlx->width + (start_x + i)] = color;
			y++;
		}
		//game->z_buffer[(start_x + i)] = game->batch.dist[i];
	}
}

// void	render_batch(t_game *game, int32_t start_x)
// {
// 	int32_t		i;
// 	int32_t		y;
// 	uint32_t	*pixels;
// 	t_wall_tex	*wall;
// 	int32_t		tex_y;
// 	uint32_t	color;

// 	pixels = (uint32_t *)game->img->pixels;
// 	i = -1;
// 	while (++i < BATCH_SIZE)
// 	{
// 		if (start_x + i >= game->mlx->width)
// 			break ;
// 		if (game->batch.tex_id[i] == TEX_VOID)
// 			continue ; // pula o desenho da parede, revelando o vazio
// 		y = game->batch.draw_start[i];
// 		wall = &game->walls[game->batch.tex_id[i]];
// 		while (y < game->batch.draw_end[i])
// 		{
// 			// calc y da textura
// 			tex_y = (int)game->batch.tex_pos[i] & (wall->tex->height - 1);
// 			// somar posição para próximo pixel
// 			game->batch.tex_pos[i] += game->batch.step[i];
// 			color = ((uint32_t *)wall->tex->pixels)[wall->tex->width * tex_y + game->batch.tex_x[i]];
// 			pixels[y * game->mlx->width + (start_x + i)] = color;
// 			y++;
// 		}
// 	}
// }
