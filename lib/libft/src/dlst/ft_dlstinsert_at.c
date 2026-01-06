/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:41:07 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Inserts a new node with given content at the specified index.
 *
 * @param lst List where the node will be inserted.
 * @param content Content to store in the new node.
 * @param index Index to insert the node at (0-based).
 * @return 1 on success, 0 on error.
 */
int	ft_dlstinsert_at(t_dlist *lst, void *content, size_t index)
{
	t_dnode	*node;

	if (!lst || index > lst->size)
		return (0);
	node = ft_dlstnew(content);
	if (!node)
		return (0);
	return (ft_dlstinsert_node_at(lst, node, index));
}
