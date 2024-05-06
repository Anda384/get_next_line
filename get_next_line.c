#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char**backup)
{
	int	read_bytes;
	char *temp;

	read_bytes = 1;
	while (read_bytes)
		{
			read_bytes = read(fd, buf, BUFFER_SIZE);
			if (read_bytes == -1)
				return (0);
			else if (read_bytes == 0)
				break;
			buf[read_bytes] = '\0';
			if (!backup)
				backup = ft_strdup("");
			temp = backup;;
			backup = (ft_strjoin(temp, buf));
			if (!backup)
				return (NULL);
			free (temp);
			temp = NULL;
			if (ft_strchr(buf, '\n'))
				break ;
		}
	return (backup);
}

static char	*extract(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line[i *1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line;
	static char *backup = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_line(fd, buf, &backup);
	free(buf);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract(line);
	return (line);
}
