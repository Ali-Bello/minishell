/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:37:57 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/13 00:07:37 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	x;

	x = n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	if (x > 9)
		ft_putnbr_fd(x / 10, fd);
	ft_putchar_fd(x % 10 + 48, fd);
}
