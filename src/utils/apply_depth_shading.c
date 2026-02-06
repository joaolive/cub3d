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

#define FOG_START 2.0f
#define FOG_END 15.0f

uint32_t	apply_depth_shading(uint32_t rgba, float dist)
{
	uint32_t	factor;

	if (dist <= FOG_START)
		return (rgba);
	if (dist >= FOG_END)
		return (0x000000);
	factor = (uint32_t)((1.0f - (dist - FOG_START)
		/ (FOG_END - FOG_START)) * 256.0f);
	return (lerp(rgba, 0x000000, factor));
}
