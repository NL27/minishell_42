/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:27:17 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/09 20:00:25 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Allowed external Funtions:
readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf
malloc
free
write
access
open
read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit -> useful for exit
getcwd -> useful for PWD
chdir -> useful for CD
stat
lstat
fstat
unlink
execve -> useful for 
dup
dup2
pipe
opendir
readdir
closedir
strerror
perror -> useful for error
isatty
ttyname
ttyslot
ioctl
getenv -> useful for env
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs

Your shell should:
-> Display a prompt when waiting for a new command.
-> Have a working history.
-> Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
-> Not use more than one global variable. Think about it. You will have to explain its purpose.
-> Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
-> Handle '' (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
-> Handle "" (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)
-> Implement redirections:
	-> < should redirect input.
	-> > should redirect output.
	-> << should be given a delimiter then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	-> >> should redirect output in append mode.
-> Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
-> Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
-> Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
-> Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
-> In interactive mode:
	-> ctrl-C displays a new prompt on a new line.		on_key_press 3 stands for Ctrl+C
	-> ctrl-D exits the shell.							on_key_press 4 stands for Ctrl+D
	-> ctrl-\ does nothing.								on_key_press 28 stands for Ctrl+\
-> Your shell must implement the following builtins:
	-> echo with option -n
	-> cd with only a relative or absolute path
	-> pwd with no options
	-> export with no options
	-> unset with no options
	-> env with no options or arguments
	-> exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But that doesn’t mean your own code, yes the code you wrote, can have memory leaks.