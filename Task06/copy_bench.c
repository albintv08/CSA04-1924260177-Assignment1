
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define FILE_SIZE (1024 * 1024)

int main(void) {
    const size_t sizes[] = {1, 64, 512, 4096, 16384};
    char *buffer;
    int fd;
    struct timespec start, end;

    fd = open("/dev/zero", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        size_t bufsize = sizes[i];
        size_t total = 0;
        buffer = malloc(bufsize);

        if (!buffer) {
            perror("malloc");
            close(fd);
            return 1;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);

        while (total < FILE_SIZE) {
            size_t amount = bufsize;
            if (amount > FILE_SIZE - total)
                amount = FILE_SIZE - total;

            ssize_t n = read(fd, buffer, amount);
            if (n <= 0) {
                perror("read");
                free(buffer);
                close(fd);
                return 1;
            }
            total += (size_t)n;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double elapsed =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Buffer: %5zu bytes | Read calls: %7zu | Time: %.6f seconds\n",
               bufsize, total / bufsize, elapsed);

        free(buffer);

        if (lseek(fd, 0, SEEK_SET) < 0) {
            perror("lseek");
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
