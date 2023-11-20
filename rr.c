#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int TAT;
    int WT;
};

void roundRobin(struct Process processes[], int n, int quantum) {
    int rr_chart[n * n];
    int c_time = 0, index = 0;

    while (1) {
        int flag = 1; // Indicates whether at least one process is remaining

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                flag = 0;

                if (processes[i].remaining_time > quantum) {
                    rr_chart[index++] = processes[i].id;
                    processes[i].remaining_time -= quantum;
                    c_time += quantum;
                } else {
                    rr_chart[index++] = processes[i].id;
                    c_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = c_time;
                }
            }
        }

        if (flag) break; // All processes have completed
    }

    printf("\nGrant Chart (Round Robin): ");
    for (int i = 0; i < index; i++)
        printf("P%d\t", rr_chart[i]);

    printf("\nTurnaround Time (TAT) and Waiting Time (WT) for Round Robin:");
    int total_TAT = 0, total_WT = 0;
    for (int i = 0; i < n; i++) {
        processes[i].TAT = processes[i].completion_time - processes[i].arrival_time;
        processes[i].WT = processes[i].TAT - processes[i].burst_time;
        total_TAT += processes[i].TAT;
        total_WT += processes[i].WT;
        printf("\nProcess %d:\tCompletion Time: %d\tTAT: %d\tWT: %d", processes[i].id, processes[i].completion_time, processes[i].TAT, processes[i].WT);
    }

    printf("\nAverage Turnaround Time (TAT): %f", (float)total_TAT / n);
    printf("\nAverage Waiting Time (WT): %f\n", (float)total_WT / n);
}

int main() {
    int n, quantum;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    struct Process process[n];

    for (int i = 0; i < n; i++) {
        process[i].id = i + 1;
        printf("\nEnter Arrival and Burst time for process %d:\t", process[i].id);
        scanf("%d%d", &process[i].arrival_time, &process[i].burst_time);
        process[i].remaining_time = process[i].burst_time;
    }

    printf("\nEnter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    roundRobin(process, n, quantum);

    return 0;
}
