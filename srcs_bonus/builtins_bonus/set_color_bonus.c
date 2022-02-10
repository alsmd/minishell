#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	show_colors(void)
{
	write(2, "\033[1;30mblack\n", 14);
	write(2, "\033[1;31mred\n", 12);
	write(2, "\033[1;32mgreen\n", 14);
	write(2, "\033[1;33myellow\n", 15);
	write(2, "\033[1;34mblue\n", 13);
	write(2, "\033[1;35mmagenta\n", 16);
	write(2, "\033[1;36mcyan\n", 13);
	write(2, "\033[1;37mgrey_light\n", 19);
	write(2, "\033[1;90mdark_grey\n", 18);
	write(2, "\033[1;91mred_light\n", 18);
	write(2, "\033[1;92mgreen_light\n", 20);
	write(2, "\033[1;93myellow_light\n", 21);
	write(2, "\033[1;94mblue_light\n", 19);
	write(2, "\033[1;95mmagenta_light\n", 22);
	write(2, "\033[1;96mcyan_light\n", 19);
	write(2, "\033[1;97mwhite\n", 14);
	write(2, "\033[;1mbold\n", 11);
	write(2, "\033[;7minvert\n", 13);
	write(2, "\033[;0mreset\n", 12);
}

char	*try_normal(char *color)
{
	if (!ft_strncmp(color, "black", -1))
		return (ft_strdup(BLACK));
	if (!ft_strncmp(color, "red", -1))
		return (ft_strdup(RED));
	if (!ft_strncmp(color, "green", -1))
		return (ft_strdup(GREEN));
	if (!ft_strncmp(color, "yellow", -1))
		return (ft_strdup(YELLOW));
	if (!ft_strncmp(color, "blue", -1))
		return (ft_strdup(BLUE));
	if (!ft_strncmp(color, "magenta", -1))
		return (ft_strdup(MAGENTA));
	if (!ft_strncmp(color, "cyan", -1))
		return (ft_strdup(CYAN));
	if (!ft_strncmp(color, "white", -1))
		return (ft_strdup(WHITE));
	if (!ft_strncmp(color, "bold", -1))
		return (ft_strdup(BOLD));
	if (!ft_strncmp(color, "invert", -1))
		return (ft_strdup(INVERT));
	if (!ft_strncmp(color, "reset", -1))
		return (ft_strdup(RESET));
	return (NULL);
}

char	*try_light(char *color)
{
	if (!ft_strncmp(color, "grey_light", -1))
		return (ft_strdup(GREY_LIGHT));
	if (!ft_strncmp(color, "dark_grey", -1))
		return (ft_strdup(DARK_GREY));
	if (!ft_strncmp(color, "red_light", -1))
		return (ft_strdup(RED_LIGHT));
	if (!ft_strncmp(color, "green_light", -1))
		return (ft_strdup(GREEN_LIGHT));
	if (!ft_strncmp(color, "yellow_light", -1))
		return (ft_strdup(YELLOW_LIGHT));
	if (!ft_strncmp(color, "blue_light", -1))
		return (ft_strdup(BLUE_LIGHT));
	if (!ft_strncmp(color, "magenta_light", -1))
		return (ft_strdup(MAGENTA_LIGHT));
	if (!ft_strncmp(color, "cyan_light", -1))
		return (ft_strdup(CYAN_LIGHT));
	return (NULL);
}

char	*get_color(char *color)
{
	char	*color_result;

	color_result = try_normal(color);
	if (!color_result)
		color_result = try_light(color);
	return (color_result);
}

void	set_color(char *color)
{
	if (!color)
	{
		write(2, "color: give a valid color name: use -h to see colors\n", 54);
		g_minishell.exit_code = 1;
	}
	else if (!ft_strncmp(color, "-h", -1))
	{
		show_colors();
		g_minishell.exit_code = 2;
	}
	else
	{
		if (g_minishell.color)
			free(g_minishell.color);
		g_minishell.color = get_color(color);
		if (!g_minishell.color)
		{
			g_minishell.color = ft_strdup(RESET);
			write(2, "\033[;0mInvalid color, try another\n", 33);
			g_minishell.exit_code = 3;
			return ;
		}	
		g_minishell.exit_code = 0;
	}
}
