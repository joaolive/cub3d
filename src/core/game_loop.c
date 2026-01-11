/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 10:01:18 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/11 15:48:44 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	render_bg(game);
}

