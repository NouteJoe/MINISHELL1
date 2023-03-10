/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:16:38 by mfusil            #+#    #+#             */
/*   Updated: 2022/03/12 11:37:03 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	x;

	x = 0;
	if (c >= '0' && c <= '9')
	{
		x = 1;
	}
	return (x);
}
