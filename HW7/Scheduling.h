#ifndef HW1_SCHEDULING_H
#define HW1_SCHEDULING_H

typedef struct {
    int pid;                // Process ID
    int arrival_time;       // Time when the process arrives in the system
    int burst_time;         // CPU burst time required by the process
    int turnaround_time;    // Time taken from process arrival to its completion
    int waiting_time;       // Time a process spends waiting in the queue
    int response_time;      // Time from process arrival to the first execution (same as waiting time for non-preemptive algorithms)
} Process;

typedef struct {
    double avg_waiting;
    double avg_turnaround;
    double avg_response;
} Averages;

int compareByArrivalTime(const void* a, const void* b);
int compareByBurstTime(const void* a, const void* b);

Averages FCFS(Process*, int size);
Averages SJF(Process*, int size);

Averages getAverages(Process*, int size);

void printChart(Process*, Averages, int size);

#endif