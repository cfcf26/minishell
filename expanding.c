#include "minishell.h"

t_list	*expanding(char *str)
{
	// TODO: juykang

	// envp 는 매개변수로 받지 않습니다. 이 값에 접근하기 위해 다음과 같이 접근할 수 있습니다.
	t_ms *ms = data();
	ms->envp;
}
