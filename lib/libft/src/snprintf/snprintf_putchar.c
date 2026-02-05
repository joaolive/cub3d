/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_putchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:03:06 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:27:35 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	snprintf_putchar(t_buffer *buffer, char c)
{
	if (buffer->size > 0 && buffer->written < (buffer->size - 1))
		buffer->str[buffer->written] = c;
	buffer->written++;
}
