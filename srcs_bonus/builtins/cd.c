#include <minishell.h>

extern t_minishell g_minishell;

void	cd(char **argv)
{
	int		status;
	char	*old_pwd;
	char	*buffer;
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
	{
		buffer = ft_strjoin(ft_strdup("cd: "), argv[1]);
		show_error(buffer, M_INVALID_FILE, 1, 0);
		free(buffer);
	}
	unset("PWD");
	unset("OLDPWD");
	add_variable(ft_strdup("OLDPWD"), old_pwd);
	add_variable(ft_strdup("PWD"), ft_strdup(getcwd(tmp, 500)));
	g_minishell.exit_code = 0;
}
