/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_node_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:15:49 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds an existing node at the front of the list.
 *
 * @param lst List to modify.
 * @param node Node to add.
 * @return 1 on success, 0 on error.
 */
int	ft_dlstpush_node_front(t_dlist *lst, t_dnode *node)
{
	if (!lst || !node)
		return (0);
	node->prev = NULL;
	node->next = lst->head;
	if (lst->size == 0)
		lst->tail = node;
	else
		lst->head->prev = node;
	lst->head = node;
	lst->size++;
	return (1);
}
