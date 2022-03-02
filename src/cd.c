/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/02 11:01:14 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

void	ft_end(int dir, char *path, char *oldpath)
{
	if (dir == -1)
		err_handle(3, path);
	else
		add_env("OLDPWD", oldpath);
}

int	ft_cd(int argc, char **argv, char **envp)
{
	int			dir;
	char		*path;
	char		*oldpath;

	dir = 0;
	path = argv[1];
	oldpath = getcwd(NULL, 0);
	if (argc == 1)
		path = "~";
	if (!ft_strcmp(path, "~"))
	{
		path = ft_getenv("HOME");
		dir = chdir(path);
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = ft_getenv("OLDPWD");
		if (path && !chdir(path))
			printf("%s\n", path);
	}
	else
		dir = chdir(path);
	ft_end(dir, path, oldpath);
	return (1);
}
