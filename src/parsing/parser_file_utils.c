#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

char	*trim_whitespace(char *str)
{
	int	start;
	int	end;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(str, start, end - start + 1));
}

static int read_lines_into_array(int fd, char ***result_ptr)
{
    char    *line;
    char    **result;
    int     count;

    result = ft_calloc(1000, sizeof(char *));
    if (!result)
    {
        close(fd);
        return (-1);
    }
    count = 0;
    while (1)
    {
        line = ft_get_next_line(fd);
        if (!line)
            break ;
        result[count] = line;
        count++;
        if (count >= 999)
            break ;
    }
    result[count] = NULL;
    close(fd);
    *result_ptr = result;
    return (0);
}

char	**read_file_to_array(const char *filename)
{
	int		fd;
	char	**result;
    int     status;

	if (!filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
    result = NULL;
    status = read_lines_into_array(fd, &result);
    if (status == -1)
    {
        return (NULL);
    }
	return (result);
}

void	free_file_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;

	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_lines(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;

	while (arr[count])
		count++;
	return (count);
}
