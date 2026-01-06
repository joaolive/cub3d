/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstconcat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:18:33 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstconcat(t_dlist *lst1, t_dlist *lst2)
{
	if (!lst1 || !lst2)
		return (NULL);
	if (!lst2->head)
		return (lst1);
	if (!lst1->head)
	{
		lst1->head = lst2->head;
		lst1->tail = lst2->tail;
		lst1->size = lst2->size;
	}
	else
	{
		lst1->tail->next = lst2->head;
		lst2->head->prev = lst1->tail;
		lst1->tail = lst2->tail;
		lst1->size += lst2->size;
	}
	lst2->head = NULL;
	lst2->tail = NULL;
	lst2->size = 0;
	return (lst1);
}
