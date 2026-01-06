/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 08:55:22 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:12 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_clean_up(char *stash, char *buffer)
{
	free(buffer);
	free(stash);
	return (NULL);
}

static char	*ft_get_leftovers(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	len_total;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	len_total = 0;
	while (stash[len_total])
		len_total++;
	new_stash = ft_substr(stash, i + 1, len_total - (i + 1));
	free(stash);
	return (new_stash);
}

static char	*ft_get_newline(char *stash)
{
	char	*newline;
	size_t	i;

	if (!*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	newline = ft_substr(stash, 0, i);
	return (newline);
}

static char	*ft_get_read_line(char *stash, int fd)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	if (!stash)
		stash = ft_calloc(sizeof(char), 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !stash)
		return (ft_clean_up(stash, buffer));
	bytes_read = 1;
	while (bytes_read > 0 && (!ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_clean_up(stash, buffer));
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (ft_clean_up(stash, buffer));
		free(stash);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	stash[fd] = ft_get_read_line(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = ft_get_newline(stash[fd]);
	stash[fd] = ft_get_leftovers(stash[fd]);
	return (line);
}
