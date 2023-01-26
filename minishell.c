#include "minishell.h"

int main (int argc, char *argv[], char *envp[])
{
	// char *line;
	// int err;

	// signal 처리() // 프로젝트에서 사용할 시그널을 설정. 
	// env_list = envp 처리() // envp list에 envp를 넣어 준다. 
	// while (1)
	// {
	// 	line = reaedline(" > ");
	// 	token_list = lexer(line, &err);
	// 	if (token_list == NULL) // quote가 닫히지 않았을때.
	// 	{
	// 			오류 처리(err);
	// 			continue ;
	// 	}
	// 	parsing_tree = parsing(token_list);
	// 	if (parsing_tree == NULL)
	// 	{
	// 			오류 처리(err);
	// 			continue ; 
	// 	}
	// 	run(parsing_tree, envp, err); // expanding && execute
	// 	free_all(token_list, parsing_tree, env_list);
	// }
	// return (0);
}
