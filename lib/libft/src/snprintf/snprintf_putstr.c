/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_putstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:03:06 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/03 18:34:32 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	snprintf_putstr(t_buffer *buffer, char *str)
{
	while (*str)
		snprintf_putchar(buffer, *str++);
}
