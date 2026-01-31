/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:20:21 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 08:30:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_tabget(t_htab *table, const char *key)
{
	size_t	i;
	t_hnode	*current;

	if (!table || !table->buckets || !key)
		return (NULL);
	i = ft_djb2(key) % table->size;
	current = table->buckets[i];
	while (current)
	{
		if (ft_strcmp((char *)current->key, (char *)key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
