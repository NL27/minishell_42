/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:22:51 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 12:40:01 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// string can be in "qotes" or without
// if string includes '$PWD' return print current working directory with rest of string
// if option '-n' do not print a newline
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int i;

	i = 1;
	if ((ft_strcmp(argv[0], "-n")) == 0)
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			i++;
		}
	}
	else
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}
