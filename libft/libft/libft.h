/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:44:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 17:33:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
**	string.h:
**			+NULL  +size_t
**	stdlib.h:
**			+malloc  +free
**	unistd.h:
**			+write
*/
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int				ft_printf(const char *format, ...);
int				get_next_line(int fd, char **line);

/*
**	MEMORY
*/
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_realloc(void *str, size_t size);

/*
**	NUMBERS
*/
void			ft_swap(int *a, int *b);
int				ft_nbrlen_base(int nbr, int base);
int				ft_getnbr(const char *str);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
long long		ft_atoll(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_base(int value, int base);
char			*ft_imaxtoa_base(long long value, int base, char set);
char			*ft_uimaxtoa_base(long long value, int base, char set);

/*
**	IS .. WHAT?
*/
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isalpha_str(char *str);
int				ft_issticky(char *path);
int				ft_isexec(char *path);

/*
**	STR
*/
size_t			ft_strlen(const char *s);
size_t			ft_wstrlen(const wchar_t *wstr);
size_t			ft_wchar_size(const wchar_t wchar);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			*ft_strxtrim(char const *s, char x);
char			*ft_strxtrim_quote(char const *str, char x);
char			**ft_strsplit(char const *s, char c);
char			**ft_strsplit_quote(char const *s, char c);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t b);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, char *src, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, \
		size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/*
**	TAB
*/
size_t			ft_tablen(char **tab);
char			**ft_tabnew(size_t size);
char			**ft_tabcpy(char **dst, char **src);
char			**ft_tabdup(char **tab);
char			**ft_tabndup(char **tab, size_t b);
char			**ft_tabcat(char **tab, char *str);
char			**ft_tabpop(char **tab, size_t pop);
void			ft_free_tab(char **tab);

/*
**	PUT
*/
int				ft_putchar(char c);
int				ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_puttab(char **tab);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
**	LIST
*/
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** MATH
*/
int				ft_abs(int num);
long			ft_pow(int n, int p);

/*
** OTHERS
*/
char			*ft_convert_base(unsigned int num, unsigned int base);

#endif
