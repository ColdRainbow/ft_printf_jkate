/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkate <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 02:14:33 by jkate             #+#    #+#             */
/*   Updated: 2021/01/12 22:27:04 by jkate            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

/* think about func name */

void	ft_printf_format(const char *line, va_list ap)
{
	char		*str;
	t_format	*format;

	str = NULL;
	format = get_format_struct();
	if (!(parse_specifiers(format, ap, line)))
		return ;
	if (format->type == 's' || format->type == 'c')
		parse_cs(format, &str, ap);
	else
		parse_dipouxx(format, &str, ap);
	if (str) //проверяем созданную строку пока что воть так
	{
		printf("%s", str);
		fflush(stdout);
		free(str);
	}
	return ;
}

int		ft_printf(const char *line, ...)
{
	va_list ap;
	int		i;
	int		amount;

	i = 0;
	amount = 0;
	if (!line)
		return (0);
	va_start(ap, line);
	while (line[i])
	{
		if (line[i] == '%')
		{
			clear_format_struct();
			ft_printf_format(line + i + 1, ap);
			i += set_index(0);
			amount += set_amount(0);
			set_amount(-1);
		}
		else
		{
			write(1, &line[i], 1);
			amount++;
		}
		i++;
	}
	return (amount);
}

// Дашка - какашка

//СТРОКИ: 
//точность работает только тогда, когда она меньше длины числа и игнорируется для символа
//ширина дополняет пробелами справа/слева, если она больше длины числа
//минус ставит пробелы справа и работает только при наличии ширины
//ноль не используется

//ТОЧНОСТЬ:
//СОВПАДАЮТ 1 и 4, 2 и 3
//a > b < c, a > c
//14) если ширина больше длины слова и больше точности, но точность меньше длины слова 
//-> отрезать от слова кол-во символов до точности, 
//-> добавить количество пробелов до ширины
//
//a > b > c
//23) если ширина больше длины слова и больше точности, но точность больше длины слова
//-> вывести слово
//-> добавить количество пробелов до ширины
//
//a < b > c, a > c
//23) если ширина больше длины слова и меньше точности, но точность больше длины слова
//-> вывести слово
//-> добавить количество пробелов до ширины
//
//a > b < c, a < c
//14) если ширина меньше длины слова и больше точности, но точность меньше длины слова
//-> отрезать от слова кол-во символов до точности,
//-> добавить количество пробелов до ширины
//
//a < b < c
//5) если ширина меньше длины слова и меньше точности, но точность меньше длины слова
//-> игнорируем ширину, отрезаем от слова кол-во символов до точности
//
//a < b > c, a < c
//6) если ширина меньше длины слова и меньше точности, но точность больше длины слова
//-> выводим слово
//a = b
//7) ширина равна точности
//выводим слово по точности

//* a > b > c 
//* a > b < c, a > c 
//* a > b < c, a < c 
//* a < b < c 
//* a < b > c, a < c 
//* a < b > c, a > c

/*если точность есть (включая ноль, или если просто стоит точка (это тоже ноль (%.s))), то строка обрезается по точности 
if (precison == -1) // точноть не задана
	str_len = str_len;
else
	str_len = precision;

if (width < str_len)
{
	//нам похуй
}
if (width > str_len)
{
	width = width - str_len;
}
amount = width + str_len;
calloc бла бла бла....*/