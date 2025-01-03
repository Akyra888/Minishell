/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicpinar <nicpinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:24:28 by nicpinar          #+#    #+#             */
/*   Updated: 2024/12/08 14:30:43 by nicpinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	handle_heredoc_analyse(t_tokentab *table, t_parserstate *state)
// {
// 	int	i;

// 	i = 0;
// 	while (table->tokens[i])
// 	{
// 		if (table->tokens[i]->type == HEREDOC)
// 		{
// 			if (analyse_heredoc(table, table->tokens, i, state))
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	analyse_heredoc(t_tokentab *table, t_token **token,
	int i, t_parserstate *state)
{
	if (token[i]->type == HEREDOC)
	{
		if (i + 1 == table->size)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (token[i + 1]->type == REDAPP || token[i + 1]->type == REDIN
			|| token[i + 1]->type == REDOUT || token[i + 1]->type == HEREDOC)
		{		
			printf("minishell: syntax error near unexpected token `%s'\n",
				token[i + 1]->str);
			return (1);
		}
		else if (token[i + 1]->type == DELIMITER
			|| token[i + 1]->type == DELIMITER_Q)
		{
			if (gen_heredoc_prompt(token[i], token[i + 1], state) == 1)
				return (1);
		}
	}
	return (0);
}

static int	analyse_pipe(t_tokentab *table, t_token **token, int i)
{
	if (token[i]->type == PIPE)
	{
		if (i == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		else if (i + 1 < table->size)
		{
			if (token[i + 1]->type == PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
	}
	return (0);
}

static int	analyse_redirections(t_tokentab *table, t_token **token, int i)
{
	if (token[i]->type == REDIN || token[i]->type == REDOUT
		|| token[i]->type == REDAPP)
	{
		if (i + 1 == table->size)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (token[i + 1]->type != FILENAME)
		{		
			printf("minishell: syntax error near unexpected token `%s'\n",
				token[i + 1]->str);
			return (1);
		}
	}
	return (0);
}

int	analyse_tokens(t_tokentab *table, t_parserstate *state)
{
	int				i;
	t_token			**token;

	i = 0;
	token = table->tokens;
	while (i < table->size)
	{
		if (analyse_redirections(table, token, i))
			return (1);
		if (analyse_pipe(table, token, i))
			return (1);
		if (analyse_heredoc(table, token, i, state))
			return (1);
		i++;
	}
	return (0);
}
