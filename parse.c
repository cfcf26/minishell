#include "minishell.h"


/// @brief 쉘 명령어를 담은 문자열을 실행 가능한 형태의 파싱트리로 변환합니다.
/// @param line 쉘 명령어를 담은 문자열
/// @param result 파싱 결과
/// @return 파싱에 실패한 경우 0이 아닌 값을 리턴
int		parse(char *line, t_list **result)
{
	*result = NULL;

	// TODO: ekwak
	// 파싱중 에러가 발생하면 함수 내에서 출력하고 끝내야합니다. 메인 함수에서 에러를 출력하는 함수는 별도로 만들지 않았습니다.

	// t_ms는 매개변수로 받지 않습니다. 이 값에 접근하기 위해 다음과 같이 접근할 수 있습니다.
	t_ms *ms = data();
	ms->envp;
	ms->err;
	
	return (0);
}
