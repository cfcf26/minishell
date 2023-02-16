export MALLOC_STACK_LOGGING=1
while true; do leaks --list minishell; sleep 2; done;