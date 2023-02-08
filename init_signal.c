#include "minishell.h"


void	init_signal(void)
{
	signal(SIGINT, SIG_IGN);  // 컨씨
	signal(SIGQUIT, SIG_IGN); //컨 역슬레쉬
}
