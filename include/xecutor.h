/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:13:15 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 11:00:52 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XECUTOR_H
# define XECUTOR_H

# include "minishell.h"
# include <stdbool.h>

int		xecute(void);
char	**ft_getpath(char *cmd);
bool	check_cmds(char	*cmd);
bool	is_builtin(char	*cmd);
int		add_env(char *name, char *value);
int		init_args(t_simple_cmd *simple_cmd, char ***arg_array);
char	*ft_strjoin2(char *s1, char *s2);

/* ----- Inbuilts Commands */
int		ft_export(int argc, char *argv[], char *envp[]);
int		ft_env(int argc, char *argv[], char *envp[]);
int		ft_unset(int argc, char *argv[], char *envp[]);
int		ft_cd(int argc, char **argv, char **envp);
int		ft_pwd(void);
int		ft_unset(int argc, char *argv[], char *envp[]);
int		ft_echo(int argc, char **argv);
int		ft_exit(int argc, char **argv);

enum STATE
{
	IDLE = 0,
	EXEC = 1,
	HEREDOC = 2,
};

enum FILE_DESCRIPTORS
{
	STDIN_INIT = 0,
	STDOUT_INIT = 1,
	IN = 2,
	OUT = 3,
};

#endif