/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:37:07 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 11:29:37 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->mlx->width)
	{
		calculate_batch(game, x);
		render_batch(game, x, -1);
		x += BATCH_SIZE;
	}
}
