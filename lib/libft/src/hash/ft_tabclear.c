/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 08:30:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabclear(t_htab *table, void (*del)(void *))
{
	t_hnode	*current;
	t_hnode	*next;
	size_t	i;

	if (!table || !table->buckets)
		return ;
	i = -1;
	while (++i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			next = current->next;
			ft_tabdelone(current, del);
			current = next;
		}
		table->buckets[i] = NULL;
	}
	table->count = 0;
}
