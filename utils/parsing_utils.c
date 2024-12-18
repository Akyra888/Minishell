/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicpinar <nicpinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:42:49 by nicpinar          #+#    #+#             */
/*   Updated: 2024/12/11 15:02:01 by nicpinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	prev_heredoc(t_parserstate *state)
{
	t_tokentab	*table;
	int			size;

	table = state->table;
	size = table->size;
	if (size > 1)
	{
		if (to_find_str(table->tokens[size -1]->str, "<<") != -1)
			return (1);
	}
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_valid_exp(char c, unsigned int next)
{
	if (!next)
	{
		if (isalpha(c) || c == 95)
			return (1);
		return (0);
	}
	else
	{
		if (isalnum(c) || c == 95)
			return (1);
		return (0);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	to_find_str(char *str, char *to_find)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	quote = 0;
	if (!str || !to_find)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0' && quote == 0)
			return (i + j);
		i++;
	}
	return (-1);
}
