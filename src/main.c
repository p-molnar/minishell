/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 23:20:15 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/11 00:30:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	char	*cmd;

	while (1)
	{
		cmd = readline(PROMPT);
		printf("%s", cmd);
		add_history(cmd);
		free(cmd);
	}

	return (EXIT_SUCCESS);
}
