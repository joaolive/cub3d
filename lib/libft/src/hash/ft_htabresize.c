/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htabresize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:20:46 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 09:05:58 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_htabresize(t_htab *tab, size_t new_size)
{
	t_hnode	**new_buckets;
	t_hnode	*node;
	size_t	new_idx;
	size_t	i;

	if (new_size <= tab->size)
		return (1);
	new_buckets = ft_calloc(new_size, sizeof(t_hnode *));
	if (!new_buckets)
		return (1);
	i = -1;
	while (++i < tab->size)
	{
		while (tab->buckets[i])
		{
			node = ft_hnodedetach(&tab->buckets[i]);
			new_idx = ft_djb2(node->key) % new_size;
			node->next = new_buckets[new_idx];
			new_buckets[new_idx] = node;
		}
	}
	free(tab->buckets);
	tab->buckets = new_buckets;
	tab->size = new_size;
	return (0);
}
