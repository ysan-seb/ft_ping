/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:41:36 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 20:08:09 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_env
{
	FILE			*file;
	char			*str;
	int				family;
	int				fd;
	char			result[4000];
	size_t			size;
	size_t			index;
	int				i;
	char			type;
	int				nb_arg;
	int				flag_plus;
	int				flag_diese;
	int				flag_moins;
	int				flag_space;
	int				flag_zero;
	int				precision;
	int				field_width;
	int				neg;
	int				m_h;
	int				m_hh;
	int				m_l;
	int				m_ll;
	int				m_j;
	int				m_z;
	va_list			pa;
}					t_env;

int					ft_printf(const char *restrict format, ...);
int					ft_fprintf(FILE *stream, const char *restrict format, ...);
int					ft_dprintf(int fd, const char *restrict format, ...);
int					ft_sprintf(char *restrict str,
		const char *restrict format, ...);
int					ft_vprintf(const char *restrict format,
		va_list ap);
int					ft_vdprintf(int fd, const char *restrict format,
		va_list ap);
void				ft_printf_b(t_env *e);
char				*ft_stoa_base(long long nb, int base);
char				*ft_utoa_base(unsigned long long nb, int base);
void				ft_printf_parser(t_env *e, char *format);
int					ft_printf_precision(t_env *e, char *format);
int					ft_printf_length(t_env *e, char *format);
size_t				ft_printf_unicode(unsigned char *const buffer,
		const unsigned int code);
int					ft_printf_conversion(t_env *e, char c);
void				ft_printf_s(t_env *e);
void				ft_printf_smaj(t_env *e);
void				ft_printf_p(t_env *e);
void				ft_printf_di(t_env *e);
void				ft_printf_dmaj(t_env *e);
void				ft_printf_omaj(t_env *e);
void				ft_printf_o(t_env *e);
void				ft_printf_u(t_env *e);
void				ft_printf_umaj(t_env *e);
void				ft_printf_x(t_env *e);
void				ft_printf_xmaj(t_env *e);
void				ft_printf_c(t_env *e);
void				ft_printf_cmaj(t_env *e);
void				ft_printf_modulo(t_env *e);
void				ft_printf_add_to_buffer(t_env *e, char *s, int start);
void				ft_printf_buffer_flush(t_env *e);
int					ft_toupper(int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_isdigit(int c);
void				ft_putstr(char const *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *s);
void				ft_strdel(char **as);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
char				*ft_strnew(size_t size);
char				*ft_strdup(const char *s1);
char				*ft_itoa(int n);
char				*remove_min(t_env *e, char *tmp);
void				ft_printf_putflags(t_env *e, char *s);
char				*getspace(t_env *e, char *space, char *s);
char				*ft_strjoin_free(char *s1, char *s2, int rm);

#endif
