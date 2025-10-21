#include <stdio.h>
#include <stdlib.h>
#include "Scheduling.h"

int main(void) {

    printf("Enter number of processes: ");
    int number;
    scanf("%d", &number);

    Process *processes = malloc(sizeof(Process) * number);

    for (int i = 0; i < number; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    Averages avg = FCFS(processes, number);
    printf("=== First Come First Served (FCFS) === \n");
    printChart(processes, avg, number);

    return 0;
}

