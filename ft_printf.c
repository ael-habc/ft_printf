/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-habc <ael-habc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 09:00:06 by ael-habc          #+#    #+#             */
/*   Updated: 2020/10/17 12:08:11 by ael-habc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//%[parameter][flags][width][.precision][length]type
int len(int n)
{
    int i;

    i = 0;
    while(n>0)
    {
        n /= 10;
        i++;
    }
    return i;
}

void ft_toUpper(char *s)
{
    char *str;
    int i = 0;
    while (s[i])
    {
        if(s[i] >= 'a' && s[i] <= 'z')
                s[i] = s[i] - 32;
        i++;
    }
}

char    *ft_itoa(unsigned int n)
{
    char *str;
    int i;
    i = len(n);
    str = (char*)malloc(sizeof(char) * (i + 1));
    str[i--] = '\0';
    while(n > 0)
    {
        str[i] = n % 10 + '0';
        i--;
        n = n/10;
    }
    return (str);
}

char *ft_itoa_base(unsigned long value, int base)
{
    char *s;
    unsigned long nb;
    unsigned long n;
    int i= 0;
    int count = 0;
    int sign = 0;
    nb = value;
    while (nb > 0)
    {
        nb /= base;
        count++;
    }
    s = (char *)malloc(sizeof(char) * count + 1);
    i = count;
    n = value;
    s[count] = '\0';
    while (i--)
    {
        s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
        n /= base;
    }
    return (s);
}

int     ft_strchr(const char *s, char c)
{
    int i;

    i = -1;
    while  (s[++i])
        if (s[i] == c)
            return (1);
    return (0);
}

void    ft_putc(char c, int *ret, int *i)
{
    write(1, &c, 1);
    *ret += 1;
    *i += 1;
}

char ft_get_type(const char *s, int i)
{
    i++;
    while (!ft_strchr("cspdiouxXf", s[i]) && s[i])
        i++;
    if (s[i])
        return (s[i]);
    return (-1);
}

void handle_c(const char *s, int *ret, int *i, va_list pa)
{
    int c = va_arg(pa, int);
    write(1, &c, 1);
    *ret += 1;
    *i += 2;
}

void handle_d(const char *s, int *ret, int *i, va_list pa)
{
    int n = va_arg(pa, int);
    char *str = ft_itoa(n);
    while(*str)
    {
        write(1, str, 1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_s(const char *s, int *ret, int *i, va_list pa)
{
    char *str = va_arg(pa, char *);
    while (*str)
    {
        write(1, str, 1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_p(const char *s, int *ret, int *i, va_list pa)
{
    char *str;
    unsigned long  c = (unsigned long)va_arg(pa, char *);
    str = ft_itoa_base(c,16);
    write(1,"0x",3);
    while(*str)
    {
        write(1,str,1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_x(const char *s,int *ret, int *i, va_list pa)
{
    int c ;
    char *str;
    
    c = va_arg(pa, int);
    str = ft_itoa_base(c, 16);
    while(*str)
    {
        write(1,str,1);
        *ret += 1;
        str++;
    }
    *i += 2;
    
}

void handle_X(const char *s,int *ret, int *i, va_list pa)
{
    int c ;
    char *str;
    
    c = va_arg(pa, int);
    str = ft_itoa_base(c, 16);
    ft_toUpper(str);
    while(*str)
    {
        write(1,str,1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_o(const char *s,int *ret, int *i, va_list pa)
{
    int c;
    char *str;
    c = va_arg(pa, int);
    str = ft_itoa_base(c,8);
    while (*str)
    {
        write(1, str, 1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_u(const char *s, int *ret, int *i, va_list pa)
{
    unsigned int c;
    char *str;
    c = (unsigned int)va_arg(pa,int);
    str  = ft_itoa(c);
    while (*str)
    {
        write(1, str, 1);
        *ret += 1;
        str++;
    }
    *i += 2;
}

void handle_type(const char *s, int *ret, int *i, va_list pa, char type)
{
    if (type == 'c')
        handle_c(s, ret, i, pa);
    if (type == 's')
        handle_s(s, ret, i, pa);
    if (type == 'd')
        handle_d(s, ret, i, pa);
    if (type == 'p')
        handle_p(s, ret, i, pa);
    if (type == 'i')
        handle_d(s, ret, i, pa);
    if (type == 'x')
        handle_x(s, ret, i, pa);
    if (type == 'X')
        handle_X(s, ret, i, pa);
    if (type == 'o')
        handle_o(s, ret, i, pa);
    if (type == 'u')
        handle_u(s, ret, i, pa);
}   

int ft_printf(const char *s, ...)
{
	va_list pa;
	int     i;
    int     ret;
    char    type;

    va_start(pa, s);
    ret = 0;
    i = 0;
    // test
    while (s[i])
    {
        if (s[i] != '%')
            ft_putc(s[i], &ret, &i);
        else if (s[i] == '%')
        {
            type = ft_get_type(s, i);
            handle_type(s, &ret, &i, pa, type);
        }
    }
    // end test
	va_end(pa);
	return (ret);
}
