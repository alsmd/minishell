#include <minishell.h>

void exec_builtin(t_node *cmd)
{
	// printf("%s\n", cmd->argv[0]);
	// printf("%s\n", cmd->argv[1]);
	// if (!(ft_strncmp(cmd->argv[0], "exit",-1)))
	// 	return (TRUE);
	// if (!(ft_strncmp(cmd->argv[0], "cd", -1)))
	// 	return (TRUE);
	// if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
	// 	return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "export", -1)))
	{
		export(cmd->argv[1]);

	}
	if (!(ft_strncmp(cmd->argv[0], "env", -1)))
	{
		env();

	}
	if (!(ft_strncmp(cmd->argv[0], "unset", -1)))
	{
		unset(cmd->argv[1]);
	}
}