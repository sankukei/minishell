/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:57:28 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/17 00:57:56 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	setup_sigint(struct sigaction *sa,
	struct sigaction *old, t_mode *mode)
{
	*mode = MODE_HEREDOC;
	*get_sigint_flag() = 0;
	sigaction(SIGINT, NULL, old);
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = sigint_heredoc_handler;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}
