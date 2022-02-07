/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/07 21:32:50 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../include/minishell.h"

bool	is_space(char c)
{
	if (c == WSPACE || c == TAB || c == NEWLINE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == LESS || c == GREAT || c == PIPE || c == ASSIGN)
		return (true);
	return (false);
}

bool shall_split(char *line)
{
	if (*(line + 1) == '\0')
		return (true);
	if (is_space(*(line + 1)))
		return (true);
	if (!is_operator(*line) && is_operator(*(line + 1)))
		return (true);
	if (is_operator(*(line)) && !is_operator(*(line + 1)))
		return (true);
	else
		return (false);
}

int	split_input(char *line)
{
	t_token *token;

	token = &g_data.tokens;
	token->value = NULL;
	while(*line != '\0')
	{
		if (!is_space(*line))
		{
			token->value = ft_append_char(token->value, *line);
			if(shall_split(line))
			{
				if(is_operator(*line))
					token->type = OPERATOR;
				else
					token->type = TOKEN;
				if (*(line + 1) != '\0')
				{
					token->next = malloc(sizeof(t_token));
					if (token->next == NULL)
						return (2);
					token = token->next;
					token->value = NULL;
				}
			}
		}
		line++;
	}
	token->next = NULL;
	return (0);
}

int	parse_redir()
{
	t_token	*token;

	token = &g_data.tokens;
	while(token)
	{
		token = token->next;
	}
	return (0);
}

int	get_state(char pos, char reset)
{
	static int 	state = 0;

	if (reset == RESET)
	{
		state = 0;
		return (state);
	}
	if (pos == QUOTE && state == QUOTE)
		state = 0;
	else if (pos == QUOTE && state == 0)
		state = QUOTE;
	if (pos == DQUOTE && state == DQUOTE)
		state = 0;
	else if (pos == DQUOTE && state == 0)
		state = DQUOTE;
	return (state);
}

char	*strip_quotes(char *line)
{
	char	*stripped;
	int		state;

	stripped = NULL;
	state = get_state(*line, RESET);
	while(*line)
	{
		state = get_state(*line, NO_RESET);
		if (*line == '$' && state != QUOTE)
			stripped = ft_append_char(stripped, '$');
		if (*line == '$' && state == QUOTE)
		{
			stripped = ft_append_char(stripped, '\\');
			stripped = ft_append_char(stripped, '$');
		}
		if (*line != '$' && ((*line != QUOTE && *line != DQUOTE) 
			|| (state != *(line) && state != 0)))
			stripped = ft_append_char(stripped, *line);
		line++;
	}
	return (stripped);
}

int	quotes_matched(char *line)
{
	get_state(*line, RESET);
	while(*line)
	{
		get_state(*line, NO_RESET);
		line++;
	}
	if (get_state(*line, NO_RESET) == 0)
		return (true);
	else
		return (false);
}

int	lex(char *line)
{
	char	*stripped;
	t_token *temp;
	
	while (!quotes_matched(line))
		line = ft_strjoin(line, readline("> "));
	printf("line: %s\n", line);
	stripped = strip_quotes(line);
	split_input(line);
	printf("split: \n");
	// return 0;
	temp = &g_data.tokens;
	while (temp != NULL)
	{
		printf("%d: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	return (0);
}
