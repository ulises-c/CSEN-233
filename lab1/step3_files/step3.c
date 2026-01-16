#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

// Function to copy file using standard C library functions
void copy_file_lib(const char *source, const char *dest)
{
    FILE *src = fopen(source, "rb");
    FILE *dst = fopen(dest, "wb");
    if (!src || !dst)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);
}

// Function to copy file using system calls
void copy_file_sys(const char *source, const char *dest)
{
    int src_fd = open(source, O_RDONLY);
    int dst_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (src_fd < 0 || dst_fd < 0)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        write(dst_fd, buffer, bytes);
    }

    close(src_fd);
    close(dst_fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    const char *source = argv[1];
    const char *dest_lib = "copy_lib_file";
    const char *dest_sys = "copy_sys_file";

    clock_t start, end;
    double cpu_time_used;

    // Copy using library functions
    start = clock();
    copy_file_lib(source, dest_lib);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken using library functions: %f seconds\n", cpu_time_used);

    // Copy using system calls
    start = clock();
    copy_file_sys(source, dest_sys);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken using system calls: %f seconds\n", cpu_time_used);

    return 0;
}
