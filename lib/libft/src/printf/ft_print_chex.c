/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:18:19 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_chex(va_list args)
{
	unsigned int	num;

	num = (unsigned int)va_arg(args, unsigned int);
	return (ft_puthex(num, sizeof(num), 'X'));
}
