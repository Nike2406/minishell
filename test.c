#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <fcntl.h>
#include <string.h>

// DataType Тип контента [0, 9]
// SegIndex Индекс сегмента данных [0, 100000]
// EndFlag Если конец, то 1. Else 0.
// ContentLen Длина контента [2, 5]
// Content actual content

typedef struct s_package
{
	int		data_type;
	int		seg_index;
	int		end_flag;
	int		content_len;
	char	content[6];
	struct s_package	*head;
	struct s_package	*next;
}			t_package;


char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	int		length;
	int		index;

	if (!s1 || !s2)
		return (0);
	length = 0;
	index = 0;
	result = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 1);
	if (result == 0)
	{
		// free(s1);
		// free(s2);
		return (NULL);
	}
	while (*(s1 + length))
		result[index++] = s1[length++];
	length = 0;
	while (*(s2 + length))
		result[index++] = s2[length++];
	result[index] = '\0';
	// free(s1);
	// free(s2);
	return (result);
}

int main()
{
	int		n;
	int		data_p;
	char	*output = "";
	t_package	*pack = NULL;
	t_package	*new = NULL;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		if (pack == NULL)
		{
			pack = (t_package *)malloc(sizeof(t_package));
			if (!pack)
				exit(1);
			pack->head = pack;
			pack->next = NULL;
			scanf("%d %d %d %d %s", &pack->data_type, &pack->seg_index, &pack->end_flag, &pack->content_len, pack->content);
		}
		else
		{
			new = (t_package *)malloc(sizeof(t_package));
			if (!new)
				exit(1);
			new->head = pack->head;
			new->next = NULL;
			scanf("%d %d %d %d %s", &new->data_type, &new->seg_index, &new->end_flag, &new->content_len, new->content);
			pack->next = new;
			pack = pack->next;
		}
	}
	scanf("%d", &data_p);
	pack = pack->head;

	int	x = 0;
	while (pack != NULL)
	{
		if (pack->data_type == data_p)
		{
			if (pack->seg_index == x)
			{
				output = ft_strjoin_free(output, pack->content);
				if (pack->end_flag == 1)
				{
					printf("%s", output);
					exit(0);
				}
				pack = pack->head;
				x++;
				continue;
			}
		}
		pack = pack->next;
	}
	printf("NA");
	exit(1);
}
// int	main() // DataType SegIndex EndFlag ContentLen Content
// {
// 	int	n;
// 	int	res = 0;
// 	unsigned int	mask = 2147483648;

// 	scanf("%u", &n);
// 	while (mask != 0)
// 	{
// 		if ((n & mask) == mask)
// 			res++;
// 		mask >>= 1;
// 	}
// 	printf("%d\n", res);
// 	return (0);
// }