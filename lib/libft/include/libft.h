/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:00:00 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 16:03:54 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 1024
# endif

# define MAX_FD 1048576

typedef int	(*t_format_handler)(va_list arg);

typedef struct s_handler
{
	char				specifier;
	t_format_handler	handler_func;
}						t_handler;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dnode
{
	void			*content;
	struct s_dnode	*next;
	struct s_dnode	*prev;
}	t_dnode;

typedef struct s_dlist
{
	t_dnode	*head;
	t_dnode	*tail;
	size_t	size;
}	t_dlist;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_is_numeric(char *str);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t size);
void	ft_bzero(void *s, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void **ptr, size_t cur_sz, size_t new_sz, size_t t_sz);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinv(const char *sep, int count, ...);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putunbr_fd(unsigned int n, int fd);
char	**ft_strdup_matrix(char **matrix);

void	ft_dlstdestroy(t_dlist **lst, void (*del)(void *));
t_dnode	*ft_dlstdetach_node(t_dlist *lst, t_dnode *node);
void	ft_dlstclear(t_dlist *lst, void (*del)(void*));
t_dlist	*ft_dlstconcat(t_dlist *lst1, t_dlist *lst2);
void	ft_dlstdelone(t_dnode *node, void (*del)(void*));
t_dnode	*ft_dlstfind(t_dlist *lst, void *ref, int (*cmp)(void *, void *));
int		ft_dlstforeach_ctx(t_dlist *lst, int (*f)(void *, void *),
			void *context);
int		ft_dlstforeach(t_dlist *lst, int (*f)(void *));
t_dnode	*ft_dlstget_node_at(t_dlist *lst, size_t index);
ssize_t	ft_dlstget_node_index(t_dlist *lst, t_dnode *node);
t_dlist	*ft_dlstinit(void);
int		ft_dlstinsert_at(t_dlist *lst, void *content, size_t index);
int		ft_dlstinsert_node_at(t_dlist *lst, t_dnode *node, size_t index);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));
t_dnode	*ft_dlstnew(void *content);
void	*ft_dlstpeek_at(t_dlist *lst, size_t index);
void	*ft_dlstpeek_back(t_dlist *lst);
void	*ft_dlstpeek_front(t_dlist *lst);
void	*ft_dlstpop_back(t_dlist *lst);
void	*ft_dlstpop_front(t_dlist *lst);
int		ft_dlstpush_back(t_dlist *lst, void *content);
int		ft_dlstpush_front(t_dlist *lst, void *content);
int		ft_dlstpush_node_back(t_dlist *lst, t_dnode *node);
int		ft_dlstpush_node_front(t_dlist *lst, t_dnode *node);
int		ft_dlstremove_at(t_dlist *lst, size_t index, void (*del)(void*));
int		ft_dlstremove_if(t_dlist *lst, int (*cond)(void *),
			void (*del)(void *));
int		ft_dlstremove_node(t_dlist *lst, t_dnode *node, void (*del)(void*));
void	ft_dlstreverse(t_dlist *lst);

char	*ft_get_next_line(int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_printf(const char *arr, ...);
int		ft_handler_format(char specifier, va_list args);
int		ft_print_char(va_list args);
int		ft_print_str(va_list args);
int		ft_print_num(va_list args);
int		ft_print_unum(va_list args);
int		ft_print_lhex(va_list args);
int		ft_print_chex(va_list args);
int		ft_print_ptr(va_list args);
int		ft_print_percent(va_list args);
int		ft_puthex(unsigned long long num, size_t size_in_bytes, char specifier);

#endif
