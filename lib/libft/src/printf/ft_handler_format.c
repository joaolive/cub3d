/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:44:43 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initialize_dispath_table(t_handler table[])
{
	table[0] = (t_handler){'c', &ft_print_char};
	table[1] = (t_handler){'s', &ft_print_str};
	table[2] = (t_handler){'p', &ft_print_ptr};
	table[3] = (t_handler){'d', &ft_print_num};
	table[4] = (t_handler){'i', &ft_print_num};
	table[5] = (t_handler){'u', &ft_print_unum};
	table[6] = (t_handler){'x', &ft_print_lhex};
	table[7] = (t_handler){'X', &ft_print_chex};
	table[8] = (t_handler){'%', &ft_print_percent};
	table[9] = (t_handler){'\0', NULL};
}

//cspdiuxX%
int	ft_handler_format(char specifier, va_list args)
{
	t_handler			dispath_table[10];
	size_t				i;

	ft_initialize_dispath_table(dispath_table);
	i = 0;
	while (dispath_table[i].specifier)
	{
		if (dispath_table[i].specifier == specifier)
			return (dispath_table[i].handler_func(args));
		i++;
	}
	return (0);
}
