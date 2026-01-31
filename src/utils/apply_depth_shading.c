/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_depth_shading.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:12:19 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 15:18:58 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// (1.0 - (dist - start) / (end - start)) * 256
uint32_t	apply_depth_shading(uint32_t rgba, float dist)
{
	const float	fog_start = 2.0f;
	const float	fog_end = 15.0f;
	uint32_t	factor;

	if (dist <= fog_start)
		return (rgba);
	if (dist >= fog_end)
		return (0x000000);
	factor = (uint32_t)((1.0f - (dist - fog_start)
		/ (fog_end - fog_start)) * 256.0f);
	return (lerp(rgba, 0x000000, factor));
}
