#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000

void *thread_function(void *arg) {
    return NULL;
}

double get_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    struct timespec start, end;
    struct rusage usage;
    pid_t pid;
    int created = 0;

    printf("=== PROCESS BENCHMARK ===\n");

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < COUNT; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            break;
        }

        if (pid == 0) {
            _exit(0);
        }

        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid");
            break;
        }

        created++;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    getrusage(RUSAGE_CHILDREN, &usage);

    printf("Processes created: %d\n", created);
    printf("Creation and completion time: %.6f seconds\n",
           get_time(start, end));
    printf("Child maximum resident memory: %ld KB\n",
           usage.ru_maxrss);

    printf("\n=== THREAD BENCHMARK ===\n");

    pthread_t threads[COUNT];
    created = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < COUNT; i++) {
        int result = pthread_create(&threads[i], NULL,
                                    thread_function, NULL);
        if (result != 0) {
            printf("Thread creation failed at %d\n", i);
            break;
        }
        created++;
    }

    for (int i = 0; i < created; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    getrusage(RUSAGE_SELF, &usage);

    printf("Threads created: %d\n", created);
    printf("Creation and completion time: %.6f seconds\n",
           get_time(start, end));
    printf("Process maximum resident memory: %ld KB\n",
           usage.ru_maxrss);

    return 0;
}