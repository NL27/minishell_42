/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:58:11 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/02 21:53:57 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

int	getcmdlen(t_simple_cmd *cmds)
{
	int	len;

	len = 0;
	while (cmds)
	{
		cmds = cmds->next;
		len++;
	}
	return (len);
}

void	child_exit(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(130);
}

int	exec_builtin(t_simple_cmd *simple_cmd)
{
	int		res;
	int		argc;
	char	**argv;
	char	**env;

	res = 0;
	argv = NULL;
	env = env_to_arr();
	argc = init_args(simple_cmd, &argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		res = ft_cd(argc, argv, env);
	else if (ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		res = ft_env(argc, argv, env);
	else if (ft_strcmp(argv[0], "export") == 0)
		res = ft_export(argc, argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		res = ft_unset(argc, argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		res = ft_pwd();
	else if (ft_strcmp(argv[0], "exit") == 0)
		res = ft_exit(argc, argv);
	return (res);
}

int	child_process(t_simple_cmd *simple_cmd)
{
	char	**path;
	char	**args;
	int		argc;
	int		res;
	char	**env;

	res = 0;
	args = NULL;
	env = env_to_arr();
	signal(SIGINT, child_exit);
	if (!check_cmds(simple_cmd->cmd))
	{
		dprintf(2, "minishell: %s: command not found\n", simple_cmd->cmd);
		return (1);
	}
	path = ft_getpath(simple_cmd->cmd);
	argc = init_args(simple_cmd, &args);
	while (execve(*path, args, env) && *path)
		path++;
	perror("err");
	free_dp(args);
	free_dp(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (res);
}



int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	char		*line;
	t_infiles	*infile;

	infile = simple_cmd->infile;
	line = NULL;
	while (infile)
	{
		close(fdin);
		fdin = infile->value;
		if (fdin == -1)
			return (-1);
		// dprintf(2, "fdin %d\n", infile->value);
		infile = infile->next;
	}
	return (fdin);
}

int	get_outfile(t_simple_cmd *simple_cmd, int stdout_init, int *fdout, int *fdin)
{
	int			fdpipe[2];
	t_outfiles	*outfile;

	outfile = simple_cmd->outfile;
	while (outfile && outfile->next)
		outfile = outfile->next;
	if (outfile)
		*fdout = outfile->value;
	else if (simple_cmd->next == NULL)
		*fdout = dup2(stdout_init, *fdout);
	if (simple_cmd->next != NULL)
	{
		if (pipe(fdpipe) == -1)
			return (4);
		*fdout = fdpipe[1];
		*fdin = fdpipe[0];
	}
	if (outfile != NULL)
		dup2(outfile->value, STDOUT_FILENO);
	else
		dup2(*fdout, STDOUT_FILENO);
	close(*fdout);
	return (0);
}

void	init_fds(int fd[4])
{
	fd[STDIN_INIT] = dup(STDIN_FILENO);
	fd[STDOUT_INIT] = dup(STDOUT_FILENO);
	fd[IN] = dup(fd[STDIN_INIT]);
	fd[OUT] = dup(fd[STDOUT_INIT]);
}

void	reset_fds(int fd[4])
{
	dup2(fd[STDIN_INIT], STDIN_FILENO);
	dup2(fd[STDOUT_INIT], STDOUT_FILENO);
	close(fd[STDIN_INIT]);
	close(fd[STDOUT_INIT]);
}

int	exec_cmd(t_simple_cmd *simple_cmd, int fd[4])
{
	int	ret;

	ret = 0;
	fd[IN] = get_infile(simple_cmd, fd[IN]);
	if (fd[IN] == -1 && close(fd[IN]) && close(fd[OUT]))
		return (2);	/* maybe unsafe */
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	close(fd[OUT]);
	get_outfile(simple_cmd, fd[STDOUT_INIT], &fd[OUT], &fd[IN]);
	g_data.state = 1;
	if (is_builtin(simple_cmd->cmd))
		exec_builtin(simple_cmd);
	else
	{
		ret = fork();
		if (ret == 0)
		{
			child_process(simple_cmd);
			exit(1);
		}
	}
	return (ret);
}

int	xecute(void)
{
	int				fd[4];
	t_simple_cmd	*simple_cmd;
	int				ret;

	ret = 0;
	simple_cmd = g_data.cmds;
	if (simple_cmd != NULL && getcmdlen(simple_cmd) != 0)
		init_fds(fd);
	else
		return (2);
	while (simple_cmd != NULL)
	{
		if (simple_cmd->error || !simple_cmd->cmd)
		{
			simple_cmd = simple_cmd->next;
			continue ;
		}
		ret = exec_cmd(simple_cmd, fd);
		if (ret == 2)
			return (2);
		simple_cmd = simple_cmd->next;
	}
	reset_fds(fd);
	waitpid(ret, &g_data.exit_status, 0);
	return (0);
}
