#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

float avg(int array[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

int main()
{
    //int nums[11] = {23, 14, 63, 24, 74, 35, 62, 84, 23, 11, 25};
    int nums[15] = {23, 14, 63, 24, 74, 35, 62, 84, 23, 11, 25, 75, 54, 37};

    int size = sizeof(nums)/sizeof(nums[0]);
    int size_a = size / 2; // length of first half
    int size_b = size - size_a; // length of second half

    int fd[2]; // Used to store two ends of the pipe
    pipe(fd);

    if (fork() == 0) {
        // child

        float avg_a = avg(nums, size_a);
        //printf("child avg: %f\n", avg_a);

        close(fd[0]); // Close reading end of pipe
        write(fd[1], &avg_a, sizeof(avg_a));
    }
    else {
        // parent

        float avg_b = avg(nums + size_a, size_b);
        //printf("parent avg: %f\n", avg_b);

        wait(NULL); // wait for child to finish

        float avg_a;
        close(fd[1]); // Close writing end of pipe
        read(fd[0], &avg_a, sizeof(avg_a));

        float avg_total = (avg_a + avg_b) / 2;
        printf("total avg: %f\n", avg_total);
    }

    return 0;
}