#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != 0)
		size++;
	return (size);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*cursor;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	cursor = result;
	while (*s1)
		*cursor++ = *s1++;
	while (*s2)
		*cursor++ = *s2++;
	*cursor = 0;
	return (result);
}

int main()
{
	char *res = "dadada";
	char *tmp2;
	char tmp[6][9] = { "Hyungwoo", "Yoonjin", "Sieun", "Woojin", "Jiyeon", "Jihoon" };
	int i = 0;

	tmp2 = NULL;
	while (i < 6)
	{
		tmp2 = ft_strjoin(res, tmp[i]);
		res = tmp2;
		free(tmp2);
		i++;
	}
	printf("%s", res);
	system("leaks a.out");
}
