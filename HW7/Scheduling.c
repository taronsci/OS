#include "Scheduling.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareByArrivalTime(const void* a, const void* b) {
    Process* p1 = (Process*) a;
    Process* p2 = (Process*) b;
    return p1->arrival_time - p2->arrival_time;
}

int compareByBurstTime(const void* a, const void* b) {
    Process* p1 = (Process*) a;
    Process* p2 = (Process*) b;
    return p1->burst_time - p2->burst_time;
}

Averages FCFS(Process *processes, int size) {
    qsort(processes, size, sizeof(Process), compareByArrivalTime);

    int time_passed = 0;

    for (int i = 0; i < size; i++) {
        if (time_passed < processes[i].arrival_time) {
            time_passed = processes[i].arrival_time;
        }

        processes[i].waiting_time = time_passed - processes[i].arrival_time;
        processes[i].response_time = time_passed - processes[i].arrival_time;
        time_passed += processes[i].burst_time;
        processes[i].turnaround_time = time_passed - processes[i].arrival_time;
    }

    return getAverages(processes, size);
}

Averages SJF(Process *processes, int size) {
    qsort(processes,size,sizeof(Process), compareByArrivalTime);

    int time_passed = 0;
    int done[size];
    memset(done, 0, sizeof(done));

    int count = 0;

    while (count < size) {
        int i = -1;
        int min_burst = INT_MAX;

        // find next job
        for (int j = 0; j < size; j++) {
            if (!done[j] && processes[j].arrival_time <= time_passed) {
                if (processes[j].burst_time < min_burst) {
                    min_burst = processes[j].burst_time;
                    i = j;
                }
            }
        }

        // if there is no job yet, jump to next job
        if (i == -1) {
            time_passed = processes[count].arrival_time;
            continue;
        }

        processes[i].waiting_time = time_passed - processes[i].arrival_time;
        processes[i].response_time = time_passed - processes[i].arrival_time;
        time_passed += processes[i].burst_time;
        processes[i].turnaround_time = time_passed - processes[i].arrival_time;

        done[i] = 1;
        count++;
    }

    return getAverages(processes, size);
}

Averages getAverages(Process *processes, int size) {
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;

    for (int i = 0; i < size; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= size;
    avg_turnaround_time /= size;

    Averages res = {
        .avg_waiting = avg_waiting_time,
        .avg_turnaround = avg_turnaround_time,
        .avg_response = avg_waiting_time
    };

    return res;
}


void printChart(Process *p, Averages avg, int size) {
    printf("Gantt Chart:");
    printf("|");
    for (int i = 0; i < size; i++) {
        printf("  P%d  |", p[i].pid);
    }
    printf("\n");

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time,
               p[i].response_time);
    }

    printf("\n");
    printf("Average Waiting Time: %f\n", avg.avg_waiting);
    printf("Average Turnaround Time: %f\n", avg.avg_turnaround);
    printf("Average Response Time: %f\n", avg.avg_response);
}