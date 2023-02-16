// #include "ft_signal.h"

// static void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	heredoc_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	data()->err = 1;
// 	exit(1);
// }

// void	init_signal(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, sigint_handler);
// }