/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 12:40:43 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	// char *pwd;

	// printf("%s\n", getwd(pwd));
	if (ft_strcmp(argv[1], "cd") == 0)
	{
		chdir(argv[2]);
		// printf("%s\n", getwd(pwd));
	}
	return (0);
}
