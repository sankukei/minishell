/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:00:20 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/17 17:00:21 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// defines for token object rules

#define FD 1
#define CMD 2
#define	ARGS 3
#define PIPES 4
#define REDIR 5

// defines to parse the input and create token types

#define INPUT_REDIR_STR "<"
#define HEREDOC_STR "<<"
#define HERESTRING_STR "<<<"
#define REDIR_STR ">"
#define	APPEND_STR ">>"
#define PIPES_STR "|"
