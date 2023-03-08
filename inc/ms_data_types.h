/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_data_types.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 15:01:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/08 12:04:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DATA_TYPES_H
# define MS_DATA_TYPES_H
# include <libft.h>

typedef int	t_token_type;

typedef struct s_token_list
{
	char				*content;
	char				*prompt_ptr;
	t_token_type		type;
	struct s_token_list	*next;	
}	t_token_list;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_shell_data
{
	char			*prompt;
	t_token_list	*tokens;
	t_list			*env_vars;
	t_list			*shell_vars;
}	t_shell_data;

#endif
