#include <stdio.h>

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

    int length = sizeof(nums)/sizeof(nums[0]);
    float average = avg(nums, length);

    printf("avg: %f\n", average);

    return 0;
}