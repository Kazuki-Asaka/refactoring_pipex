/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:51:29 by akazuki           #+#    #+#             */
/*   Updated: 2023/05/14 17:16:27 by rikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parser.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write (fd, s, 1);
		s++;
	}
}