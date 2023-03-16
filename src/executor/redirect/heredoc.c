/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:50:14 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/16 18:05:04 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void	open_heredoc(char *delimiter)
{
	if (delimiter)
		ft_putendl_fd("good luck", 2);
}
