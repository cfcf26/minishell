// int get_errno()
// {
//     static int ft_errno[] = {
//         0, 1, 1,
//     }
// }

// char *get_error_message()
// {

// }

// void error_perror(int error_code)
// {
//     data()->err = get_errno(error_code);
//     perror("> ");
// }

// void non_errno_perror(int error_code)
// {
//     data()->err = get_errno(error_code);
//     printf(get_error_message(error_code));
// }


// void error_handling(int _case)
// {

//     static char *error_message[] = {
//         "No error",
//         "Error 1",
//         "FILE_ACCESS_FAIL"
//     }
//     static int error_case[] = {
//         HERE_DOC, SYNTAX, FILE_ACCESS_FAIL
//     }
    
//     int idx = search_in(error_case, _case, sizeof(error_case) / sizeof(int));
//     if (error_message[idx])
//         perror(error_message[idx]);
//     data()->err = error_code[idx];
// }