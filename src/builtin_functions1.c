#include "../headers/minishell.h"

char	*get_my_env2(t_data *data, char *str)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = data->env;
	if (ft_strncmp(str, "?", 2) == 0)
		return (ft_itoa_stack(data->last_exit_status));
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			j++;
			return (&env[i][j]);
		}
		i++;
	}
	return (NULL);
}

void	cd(char **args)
{
	char	*path;
	int		i;

	i = 0;
	args++;
	while (args[i])
		i++;
	if (i == 0)
	{
		chdir("/home");
		path = getcwd(NULL, 0);
	}
	else if (i == 1)
	{
		chdir(*args);
		path = getcwd(NULL, 0);
		printf("PWD -> %s\n", path);
	}
	else
		write(1, "too many arguments\n", 19);
}

void	pwd(char **args, int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}