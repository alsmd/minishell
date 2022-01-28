#include <minishell.h>

void	pwd(void)
{
	char	buffer[500];

	printf("%s\n", getcwd(buffer, 500));
}
