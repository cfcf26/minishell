# Minishell 개선 제안사항

## 1. 메모리 안전성 개선

### 문제: data.c 의 재귀 호출 및 에러 처리
```c
// 현재 코드 (문제)
t_ms *data(void)
{
    static t_ms *ms;
    char *pwd;
    
    if (ms != NULL)
        return (ms);
    ms = ft_malloc_guard(sizeof(t_ms));
    ft_memset(ms, 0, sizeof(t_ms));
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        exit(1);  // 🚨 갑작스러운 종료
    data()->pwd = pwd;  // 🚨 재귀 호출
    return (ms);
}

// 개선된 코드
t_ms *data(void)
{
    static t_ms *ms;
    char *pwd;
    
    if (ms != NULL)
        return (ms);
    ms = ft_malloc_guard(sizeof(t_ms));
    ft_memset(ms, 0, sizeof(t_ms));
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
    {
        free(ms);
        ms = NULL;
        return (NULL);  // 호출자가 에러 처리
    }
    ms->pwd = pwd;  // 직접 할당
    return (ms);
}
```

### 문제: remove_quote.c 의 초기화 누락
```c
// 현재 코드 (문제)
static char *next(char **str)
{
    char quote;  // 🚨 초기화되지 않음
    int len;
    char *res;
    
    // 개선: 초기화 추가
    quote = 0;
    // ...
}
```

## 2. 보안 취약점 해결

### 문제: 임시 파일 생성 보안
```c
// 현재 코드 (보안 위험)
char *create_random_file(void)
{
    int fd;
    const char material[65] = "abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // ...
    fd = open("/dev/urandom", O_RDONLY);  // 🚨 에러 체크 없음
    // ...
    while (!access(file_name, F_OK))  // 🚨 무한 루프 가능
    {
        // ...
    }
}

// 개선된 코드
char *create_random_file(void)
{
    int fd;
    int retry_count = 0;
    const int MAX_RETRIES = 1000;
    
    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
    {
        // fallback to less secure but working method
        srand(time(NULL));
        fd = -1;
    }
    
    while (!access(file_name, F_OK) && retry_count < MAX_RETRIES)
    {
        retry_count++;
        // ... 파일명 생성
    }
    
    if (retry_count >= MAX_RETRIES)
    {
        if (fd >= 0) close(fd);
        return (NULL);
    }
    // ...
}
```

### 문제: 버퍼 오버플로우 방지
```c
// cpy_without_quote 함수 개선
static char *cpy_without_quote(char *str, int len)
{
    int size;
    int i;
    char *res;
    char quote;
    
    // 🚨 입력 검증 추가
    if (!str || len < 0)
        return (NULL);
    
    res = ft_calloc_guard(1, ft_strlen(str) + 1);
    i = -1;
    size = 0;
    quote = 0;
    
    while (++i < len && str[i])  // 🚨 범위 체크 강화
    {
        // ... 기존 로직
    }
    return (res);
}
```

## 3. 에러 처리 표준화

### 문제: 일관성 없는 에러 코드
```c
// 현재: 혼재된 에러 처리
#define SYNTAX_ERROR 258
#define SUCCESS 0
#define ERROR 1
#define FT_ERROR -1

// 개선: 표준화된 에러 시스템
typedef enum e_error_code
{
    MS_SUCCESS = 0,
    MS_ERROR_MEMORY = 1,
    MS_ERROR_SYNTAX = 2,
    MS_ERROR_FILE = 3,
    MS_ERROR_PERMISSION = 4,
    MS_ERROR_NOT_FOUND = 5,
    MS_ERROR_AMBIGUOUS = 6
} t_error_code;
```

### 문제: 에러 메시지 표준화
```c
// 개선된 에러 처리 함수
int print_standardized_error(const char *cmd, const char *arg, 
                           t_error_code error_code)
{
    const char *error_messages[] = {
        [MS_SUCCESS] = "",
        [MS_ERROR_MEMORY] = "memory allocation failed",
        [MS_ERROR_SYNTAX] = "syntax error",
        [MS_ERROR_FILE] = "file not found",
        [MS_ERROR_PERMISSION] = "permission denied",
        [MS_ERROR_NOT_FOUND] = "command not found",
        [MS_ERROR_AMBIGUOUS] = "ambiguous redirection"
    };
    
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    if (cmd)
    {
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    if (arg)
    {
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putendl_fd(error_messages[error_code], STDERR_FILENO);
    return (error_code);
}
```

## 4. 코드 중복 제거

### 문제: dup2 호출 중복
```c
// 현재 코드 (중복)
static int dup2fd(t_red *red, int fd)
{
    if (red->redir_type == IN && dup2(fd, STDIN_FILENO) == -1)
        return (print_err(red->file, NULL, NULL, errno));
    if (red->redir_type == HEREDOC && dup2(fd, STDIN_FILENO) == -1)
        return (print_err(red->file, NULL, NULL, errno));
    if (red->redir_type == OUT && dup2(fd, STDOUT_FILENO) == -1)
        return (print_err(red->file, NULL, NULL, errno));
    if (red->redir_type == APPEND && dup2(fd, STDOUT_FILENO) == -1)
        return (print_err(red->file, NULL, NULL, errno));
    // ...
}

// 개선된 코드
static int dup2fd(t_red *red, int fd)
{
    int target_fd;
    
    if (red->redir_type == IN || red->redir_type == HEREDOC)
        target_fd = STDIN_FILENO;
    else if (red->redir_type == OUT || red->redir_type == APPEND)
        target_fd = STDOUT_FILENO;
    else
        return (MS_ERROR_SYNTAX);
    
    if (dup2(fd, target_fd) == -1)
        return (print_standardized_error(red->file, NULL, MS_ERROR_FILE));
    
    close(fd);
    return (MS_SUCCESS);
}
```

## 5. 널 포인터 검증 강화

### 문제: 포인터 검증 누락
```c
// syntax_error.c 개선
static int pipe_syntax_error(t_list *node, t_list *next)
{
    t_token *token;
    t_token *next_token;
    
    if (next == NULL || node == NULL)
        return (MS_ERROR_SYNTAX);
    
    token = node->content;
    next_token = next->content;
    
    // 🚨 추가 검증
    if (!token || !next_token)
        return (MS_ERROR_SYNTAX);
    
    if (next_token->type == PIPE)
        return (MS_ERROR_SYNTAX);
    if (!token->ud.str || ft_strlen(token->ud.str) != 1)
        return (MS_ERROR_SYNTAX);
    return (MS_SUCCESS);
}
```

## 6. 매직 넘버 제거

```c
// 상수 정의
#define HEREDOC_PROMPT "pipe heredoc> "
#define HEREDOC_PROMPT_LEN 15
#define TEMP_FILE_PREFIX "/tmp/pipex_tmp"
#define MAX_FILENAME_LENGTH 128
#define RANDOM_MATERIAL_SIZE 62
#define MAX_FILE_RETRIES 1000

// 사용 예시
write(1, HEREDOC_PROMPT, HEREDOC_PROMPT_LEN);
```

## 7. 리소스 관리 개선

### RAII 패턴 도입
```c
// 자동 정리를 위한 매크로
#define CLEANUP_FUNC(func) __attribute__((cleanup(func)))

void cleanup_string(char **str)
{
    if (str && *str)
    {
        free(*str);
        *str = NULL;
    }
}

void cleanup_fd(int *fd)
{
    if (fd && *fd >= 0)
    {
        close(*fd);
        *fd = -1;
    }
}

// 사용 예시
int some_function(void)
{
    CLEANUP_FUNC(cleanup_string) char *temp = NULL;
    CLEANUP_FUNC(cleanup_fd) int fd = -1;
    
    // 함수 종료 시 자동으로 정리됨
    temp = ft_strdup_guard("test");
    fd = open("test", O_RDONLY);
    
    return (process_data(temp, fd));
    // 자동으로 cleanup_string(&temp), cleanup_fd(&fd) 호출
}
```

## 8. 테스트 가능성 개선

### 의존성 주입
```c
// 전역 상태 대신 컨텍스트 전달
typedef struct s_shell_context
{
    char *pwd;
    t_list *envp;
    t_list *unlink_lst;
    int error_code;
} t_shell_context;

// 함수들이 컨텍스트를 받도록 수정
int builtin_cd_ctx(t_shell_context *ctx, t_list *argv);
t_list *remove_quote_ctx(t_shell_context *ctx, char *str);
```

이러한 개선사항들을 단계적으로 적용하면 더욱 안전하고 유지보수가 용이한 코드가 될 것입니다.