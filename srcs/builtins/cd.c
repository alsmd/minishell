#include <minishell.h>

extern t_minishell	g_minishell;

void	change_old_pwd(char *old_pwd)
{
	char	tmp[500];

	unset("PWD");
	unset("OLDPWD");
	add_variable(ft_strdup("OLDPWD"), old_pwd);
	add_variable(ft_strdup("PWD"), ft_strdup(getcwd(tmp, 500)));
}

void	join_show_and_free(char *argv)
{
	char	*buffer;

	buffer = ft_strjoin(ft_strdup("cd: "), argv);
	show_error(buffer, M_INVALID_FILE, 1, 0);
	free(buffer);
}

void	cd(char **argv)
{
	int		status;
	char	*old_pwd;
	char	tmp[500];
	char	*aux;

	old_pwd = ft_strdup(getcwd(tmp, 500));
	status = 0;
	if (argv[1] == 0 || argv[1][0] == '\0' || !ft_strncmp(argv[1], "~", -1))
	{
		aux = get_var_value("HOME");
		status = chdir(aux);
		free(aux);
	}
	else if (argv[2] != 0)
		show_error("cd: ", "too many arguments", 1, 0);
	else
		status = chdir(argv[1]);
	if (status == -1)
		join_show_and_free(argv[1]);
	change_old_pwd(old_pwd);
	g_minishell.exit_code = 0;
}
