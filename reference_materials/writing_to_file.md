Example of code used for writing to file:
```c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


// file will be dump.txt
int main()
{

    int fd = open("dump.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("error in open");
        exit(1);
    }
    write(fd, "This is message i attempt to write to dump file\n", 60);
    printf("attempt completed");
     exit(1);
}
```