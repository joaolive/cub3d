/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:36:40 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist *lst, void (*del)(void*))
{
	t_dnode	*current;
	t_dnode	*next_node;

	if (!lst)
		return ;
	current = lst->head;
	while (current)
	{
		next_node = current->next;
		ft_dlstdelone(current, del);
		current = next_node;
	}
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}
