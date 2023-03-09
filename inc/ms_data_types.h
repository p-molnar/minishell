/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_data_types.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 15:01:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/09 13:49:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DATA_TYPES_H
# define MS_DATA_TYPES_H

typedef int	t_token_type;

typedef struct s_token_list
{
	char				*content;
	char				*prompt_ptr;
	t_token_type		type;
	struct s_token_list	*next;
}	t_token_list;

typedef struct s_command_list
{
	int						symbol;
	struct s_token_list		*token;
	struct s_command_list	*next;	
}	t_command_list;

typedef struct s_var_list
{
	char	*name;
	char	*val;
}	t_var_list;

#endif
