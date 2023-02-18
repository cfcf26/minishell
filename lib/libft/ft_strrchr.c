char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (last);
}
