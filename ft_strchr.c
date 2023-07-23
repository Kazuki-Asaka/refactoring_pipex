/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikeda <rikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:12:05 by rikeda            #+#    #+#             */
/*   Updated: 2023/05/14 17:45:59 by rikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parser.h"

int 	ft_strchr ( const  char *s, int c)
{
	if ((char)c == '\0')
	{
		while (*s != '\0')
			s++;
		return (1);
	}
	if (*s != '\0')
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
				return (1);
			else
				s++;
		}
		return (0);
	}
	else
		return (0);
}