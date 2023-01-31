#include "minishell.h"

static void exe(t_token *token)
{
	// ...
	// expanding(token->ud.cmd_type->args[1]);
	// expanding(token->ud.cmd_type->args[2]);
	// expanding(token->ud.cmd_type->args[3]);
	// ...
}

void execute(t_list *parsed_list)
{
	// TODO: yonshin
	iterate_tree(parsed_list, exe, INORDER);
}
