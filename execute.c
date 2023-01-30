#include "minishell.h"

static void exe(t_token *token)
{
	// ...
	expanding(token->ud.cmd_type->args[1]);
	expanding(token->ud.cmd_type->args[2]);
	expanding(token->ud.cmd_type->args[3]);
	// ...
}

void execute(t_tree *parsed_tree)
{
	// TODO: yonshin
	iterate_tree(parsed_tree, exe, INORDER);
}
