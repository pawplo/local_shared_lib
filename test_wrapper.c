#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

static char *program_name = "test";

void put_before_to_env(const char *name, const char *value)
{
    char *value_old = getenv(name);

    if (value_old) {
        char *new_value = malloc(strlen(value) + 1 + strlen(value_old) + 1);
        if (!new_value) {
            perror("malloc() !!!");
            exit(1);
        }

        strcat(new_value, value);
        strcat(new_value, ":");
        strcat(new_value, value_old);
        setenv(name, new_value, 1);
    } else {
        setenv(name, value, 1);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    static const char *proc_self_exe = "/proc/self/exe";

    int ret;
    struct stat sb;
    ssize_t size;

    char *buf;

    size_t program_name_len = strlen(program_name);

    if (stat(proc_self_exe, &sb) == -1) {
        perror("stat() !!!");
        exit(1);
    }
    buf = malloc(sb.st_size + program_name_len + 1);

    if (buf == NULL) {
        perror("malloc() !!!");
        exit(1);
    }

    size = readlink(proc_self_exe, buf, sb.st_size + 1);

    if (size < 0) {
        perror("readlink() !!!");
        exit(1);
    }

    buf[sb.st_size] = '\0';
    //printf("program path [%s]\n", buf);

    int i = 0;
    while (buf[i])
        i++;

    i--;
    while (buf[i] != '/')
        i--;

    buf[i] = '\0';

    put_before_to_env("LD_LIBRARY_PATH", buf);

    buf[i] = '/';
    i++;

    strncpy(buf + i, program_name, program_name_len + 1);
    //printf("wrapped program path=[%s]\n", buf);

    //ret = fork();
    //printf("fork() [%d]\n", ret);

    //if (ret == 0) {
        argv[0] = program_name;
        ret = execve(buf, argv, environ);
        //printf("execve() [%d]\n", ret);

    //} //else if (ret > 0) {
    //}

    return 0;
}
