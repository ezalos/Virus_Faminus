#include "head.h"


char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	int		i;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size1 = strlen(s1);
	size2 = strlen(s2);
	if (!(str = malloc(size1 + size2 + 1)))
		return (NULL);
	i = -1;
	while (++i < size1)
		str[i] = s1[i];
	i = -1;
	while (++i < size2)
		str[i + size1] = s2[i];
	str[size1 + size2] = '\0';
	return (str);
}
