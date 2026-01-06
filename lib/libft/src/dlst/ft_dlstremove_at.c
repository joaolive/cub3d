/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:40:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Removes the node at the specified index from the list.
 *
 * @param lst List to modify.
 * @param index Index of the node to remove (0-based).
 * @param del Function to free the node's content.
 * @return 1 on success, 0 on error.
 */
int	ft_dlstremove_at(t_dlist *lst, size_t index, void (*del)(void*))
{
	if (!lst || index >= lst->size)
		return (0);
	return (ft_dlstremove_node(lst, ft_dlstget_node_at(lst, index), del));
}
