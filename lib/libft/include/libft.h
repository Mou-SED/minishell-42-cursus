/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:38:32 by moseddik          #+#    #+#             */
/*   Updated: 2022/02/26 00:15:52 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t size);
void		*ft_memmove(void *dest, void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_d_list
{
	struct s_d_list	*prev;
	void			*content;
	struct s_d_list	*next;
}		t_d_list;

int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del) (void *));
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_d_list	*ft_d_lstnew(void *content);
int			ft_d_lstsize(t_d_list *lst);
void		ft_d_lstadd_front(t_d_list **alst, t_d_list *new);
void		ft_d_lstadd_back(t_d_list **alst, t_d_list *new);
t_d_list	*ft_d_lstlast(t_d_list *lst);
void		ft_d_lstdelone(t_d_list *lst, void (*del) (void *));
void		ft_d_lstclear(t_d_list **lst, void (*del)(void *));
void		ft_d_lstiter(t_d_list *lst, void (*f)(void *));

#endif
