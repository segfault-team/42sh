/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:22:01 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:34:00 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
**	stdarg:
**
**	stdlib:
**
**	wchar:
**
**	locale:
*/

# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>
# include <locale.h>
# include "libft.h"

# define PAD_RIGHT	1
# define PAD_ZERO	2

typedef struct		s_lmod
{
	int				hh;
	int				h;
	int				ll;
	int				l;
	int				j;
	int				z;
}					t_lmod;

typedef struct		s_flags
{
	int				width;
	int				sharp;
	int				pad;
	char			padchar;
	int				precision;
	int				zero;
	int				minus;
	int				plus_sign;
	int				space;
}					t_flags;

typedef struct		s_args
{
	char			*str;
	char			ch;
	wchar_t			*wstr;
	wchar_t			wchar;
	long long		nbr;
	long long		u_nbr;
	void			*ptr;
}					t_args;

typedef struct		s_struct
{
	const char		*format;
	va_list			args;
	int				pc;
	t_args			stargs;
	t_flags			flags;
	t_lmod			lmod;
}					t_struct;

int					ft_printf(const char *format, ...);

/*
** PARSE
*/
void				parse_flags(t_struct *st);
int					parse_lenght_modifier(t_struct *st);
int					parse_args(t_struct *st);

/*
**  CONVERSION ARG
*/
int					conversion_di(t_struct *st);
int					conversion_oux(t_struct *st);

/*
** ARGUMENTS
*/
int					a_int(t_struct *st);
int					a_hex(t_struct *st, char set);
int					a_uint(t_struct *st);
int					a_octal(t_struct *st);
int					a_str(t_struct *st);
int					a_char(t_struct *st, int va);
int					a_wstr(t_struct *st);
int					a_wchar(t_struct *st);
int					a_ptr(t_struct *st);

/*
** FORMATS 00-01
*/
void				form_percent(t_struct *st);
void				form_minus(t_struct *st);
void				form_plus(t_struct *st);
void				form_zero(t_struct *st);
void				form_width(t_struct *st);
void				form_precision(t_struct *st);
void				form_space(t_struct *st);
void				form_sharp(t_struct *st);

/*
** HANDLE_WCHAR
*/
int					handle_wchar(wchar_t wchar);

/*
** PRECISION
*/
void				padding_left(t_struct *st, int limit);
void				padding_right(t_struct *st, int limit);

/*
** SET
*/
void				reset_lmod(t_struct *st);
void				reset_flags(t_struct *st);
void				set_init_st(t_struct *st, const char *format);

/*
** LENGHT
*/
int					str_lenght(t_struct *st);
int					wstr_lenght(t_struct *st);
int					nbr_lenght(long long nbr, int base);
int					unbr_lenght(long long nbr, int base);

#endif
