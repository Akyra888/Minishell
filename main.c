/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicpinar <nicpinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:06:04 by nicpinar          #+#    #+#             */
/*   Updated: 2024/10/01 19:06:04 by nicpinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	exit_shell(char *line)
{
	if (line)
		free(line);
	rl_clear_history();
	exit(0);
}

char	*ft_readline(int type)
{
	char	*line;

	if (type == 0)
		line = readline("minishell> ");
	else
		line = readline("> ");
	if (g_sigint_received == SIGINT)
	{
		g_sigint_received = 0;
		if (type == 1)
			return (NULL);
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	if (!ft_signal())
		return (0);
	rl_event_hook = check_signal;
	while (1)
	{
		line = ft_readline(0);
		if (line == NULL)
			exit_shell(NULL);
		if (ft_strcmp(line, "exit") == 0)
			exit_shell(line);
		if (*line != '\0')
		{
			add_history(line);
			parsing_main(line, envp);
		}
		free(line);
	}
	return (0);
}
