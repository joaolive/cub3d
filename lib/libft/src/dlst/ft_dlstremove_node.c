/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:20:04 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Removes a specific node from the list and frees its content.
 *
 * @param lst List to modify.
 * @param node Node to remove.
 * @param del Function to free the node's content.
 * @return 1 on success, 0 on error.
 */
int	ft_dlstremove_node(t_dlist *lst, t_dnode *node, void (*del)(void*))
{
	t_dnode	*detach_node;

	if (!lst || !node)
		return (0);
	detach_node = ft_dlstdetach_node(lst, node);
	if (!detach_node)
		return (0);
	ft_dlstdelone(detach_node, del);
	return (1);
}
