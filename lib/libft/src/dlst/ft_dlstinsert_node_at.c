/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert_node_at.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:42:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Inserts an existing node at the specified index in the list.
 *
 * @param lst List where the node will be inserted.
 * @param node Node to insert.
 * @param index Index to insert the node at (0-based).
 * @return 1 on success, 0 on error.
 */
int	ft_dlstinsert_node_at(t_dlist *lst, t_dnode *node, size_t index)
{
	t_dnode	*node_at_index;

	if (!lst || !node || index > lst->size)
		return (0);
	if (index == 0)
		return (ft_dlstpush_node_front(lst, node));
	if (index == lst->size)
		return (ft_dlstpush_node_back(lst, node));
	node_at_index = ft_dlstget_node_at(lst, index);
	node->prev = node_at_index->prev;
	node->next = node_at_index;
	node_at_index->prev->next = node;
	node_at_index->prev = node;
	lst->size++;
	return (1);
}
