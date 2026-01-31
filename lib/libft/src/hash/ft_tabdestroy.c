/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:59:36 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 08:30:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdestroy(t_htab **table, void (*del)(void *))
{
	if (!table || !*table)
		return ;
	ft_tabclear(*table, del);
	if ((*table)->buckets)
		free((*table)->buckets);
	free(*table);
	*table = NULL;
}
