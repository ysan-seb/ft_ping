/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:37:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:37:54 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_printf_uni2(unsigned char *const buf, const unsigned int code)
{
	buf[0] = 0xF0 | (code >> 18);
	buf[1] = 0x80 | ((code >> 12) & 0x3F);
	buf[2] = 0x80 | ((code >> 6) & 0x3F);
	buf[3] = 0x80 | (code & 0x3F);
}

size_t		ft_printf_unicode(unsigned char *const buf, const unsigned int code)
{
	if (code <= 127)
	{
		buf[0] = code;
		return (1);
	}
	if (code <= 0x7FF)
	{
		buf[0] = 0xC0 | (code >> 6);
		buf[1] = 0x80 | (code & 0x3F);
		return (2);
	}
	if (code <= 0xFFFF)
	{
		buf[0] = 0xE0 | (code >> 12);
		buf[1] = 0x80 | ((code >> 6) & 0x3F);
		buf[2] = 0x80 | (code & 0x3F);
		return (3);
	}
	if (code <= 0x10FFFF)
	{
		ft_printf_uni2(buf, code);
		return (4);
	}
	return (0);
}
