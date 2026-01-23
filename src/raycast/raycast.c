/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:37:07 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/23 18:28:27 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->mlx->width)
	{
		// calcula os dados para 8 raios
		calculate_batch(game, x);
		// desenha os 8 raios baseados nos dados calculados
		render_batch(game, x);
		//avança o bloco
		x += BATCH_SIZE;
	}
}
