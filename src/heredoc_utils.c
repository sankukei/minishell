/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:32:37 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/06 14:32:40 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_delimiter(char *input, char *target)
{
	int	len;

	len = ft_strlen(target);
	if (ft_strncmp(input, target, len) == 0 && input[len] == '\0')
		return (1);
	return (0);
}

void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	handle_sigint_for_heredoc(int fd, char *input,
	struct sigaction *old, t_mode *mode)
{
	free(input);
	close(fd);
	unlink(".heredoc_buffer");
	sigaction(SIGINT, old, NULL);
	*mode = MODE_MAIN;
	return (-1);
}

int	handle_eof(int fd, char *target,
	struct sigaction *old, t_mode *mode)
{
	printf("minishell: warning: here-document delimited by end-of-file"
		" (wanted `%s')\n", target);
	sigaction(SIGINT, old, NULL);
	*mode = MODE_MAIN;
	close(fd);
	return (open(".heredoc_buffer", O_RDONLY));
}

int	finish_heredoc(int fd, char *input,
	struct sigaction *old, t_mode *mode)
{
	free(input);
	close(fd);
	sigaction(SIGINT, old, NULL);
	*mode = MODE_MAIN;
	return (open(".heredoc_buffer", O_RDONLY));
}
