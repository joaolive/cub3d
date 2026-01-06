/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:28:27 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Frees a list and optionally a content item, returning NULL.
 *
 * @param lst Pointer to the list to destroy.
 * @param del Function to free node contents.
 * @param content Optional content to free.
 * @return Always NULL.
 */
static t_dlist	*ft_cleanup_map(t_dlist **lst, void (*del)(void *), void *cont)
{
	if (cont)
		del(cont);
	ft_dlstdestroy(lst, del);
	return (NULL);
}

/**
 * @brief Creates a new list by applying a function to each element.
 *
 * @param lst Original list.
 * @param f Function to apply to each content.
 * @param del Function to free content on failure.
 * @return New list, or NULL on error.
 */
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_lst;
	t_dnode	*new_node;
	t_dnode	*current;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_dlstinit();
	if (!new_lst)
		return (NULL);
	current = lst->head;
	while (current)
	{
		new_content = f(current->content);
		if (!new_content)
			return (ft_cleanup_map(&new_lst, del, NULL));
		new_node = ft_dlstnew(new_content);
		if (!new_node)
			return (ft_cleanup_map(&new_lst, del, new_content));
		ft_dlstpush_node_back(new_lst, new_node);
		current = current->next;
	}
	return (new_lst);
}
