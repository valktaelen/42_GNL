# But du projet

Coder une fonction qui retourne la ligne suivante d'un fichier.

# Fonctionnement

```c
char	*get_next_line(int fd);
```

`get_next_line` prend en paramêtre un descripteur de fichier (fd) et renvoie
la ligne suivante ou `NULL` si la fin du fichier est atteinte.

`dir_gnl` est le dossier où se trouve get_next_line.

- Exemple de main get_next_line
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "dir_gnl/get_next_line.h"

int main()
{
	char	*line;
	int		fd = open("README.md", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	printf("%s", line);
	close(fd);
	return 0;
}
```

**Attention get_next_line ne marche que pour un fichier**

## Bonus

La version bonus permet de gerer plusieurs fichier

- Exemple de main get_next_line (version bonus)
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "dir_gnl/get_next_line_bonus.h"

int main()
{
	char	*line;
	int		fd = open("README.md", O_RDONLY);
	int		fd2 = open(".gitignore", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	printf("%s", line);
	while ((line = get_next_line(fd2)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("%s", line);
	close(fd2);
	return 0;
}
```


## Compilation

À la compilation, on peut choisir de combien d'octet on lit le fichier.
Pour cela, il faut compiler avec l'option (flag) `-D` pour redéfinir la taille qui a défaut est à 42.

Par exemple `-D BUFFER_SIZE=4242`.

`srcs` sont les sources.

```bash
gcc dir_gnl/get_next_line.c srcs
```

- Partie bonus
```bash
gcc dir_gnl/get_next_line_bonus.c srcs
```