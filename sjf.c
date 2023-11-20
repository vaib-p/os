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

void sort(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sjf(struct Process processes[], int n) {
    int grant_chart[100];
    int c_time = 0;

    while (1) {
        int selected_process = -1, min_time = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= c_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_time || min_time == -1) {
                    selected_process = i;
                    min_time = processes[i].remaining_time;
                }
            }
        }

        if (selected_process == -1) {
            break;
        } else {
            grant_chart[c_time] = processes[selected_process].id;
            processes[selected_process].remaining_time--;
            c_time++;
        }

        if (processes[selected_process].remaining_time == 0 && processes[selected_process].burst_time > 0) {
            processes[selected_process].completion_time = c_time;
            processes[selected_process].remaining_time = -1;
        }
    }

    //Grant Chart
    printf("\nGrant Chart: ");
    for (int i = 0; i < c_time; i++) {
        printf("%d\t", grant_chart[i]);
    }
}

int main() {
    int n;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    struct Process process[n];

    for (int i = 0; i < n; i++) {
        process[i].id = i + 1;
        printf("\nEnter Arrival time for process %d:\t", process[i].id);
        scanf("%d", &process[i].arrival_time);

        printf("\nEnter Burst time for process %d:\t", process[i].id);
        scanf("%d", &process[i].burst_time);

        process[i].remaining_time = process[i].burst_time;
    }

    sort(process, n);
    sjf(process, n);
    
    // Turnaround Time  and Waiting Time 
    int total_TAT = 0, total_WT = 0;
    for (int i = 0; i < n; i++) {
        process[i].TAT = process[i].completion_time - process[i].arrival_time;
        process[i].WT = process[i].TAT - process[i].burst_time;

        total_TAT += process[i].TAT;
        total_WT += process[i].WT;

        printf("\nProcess %d:\tCompletion Time: %d\tTAT: %d\tWT: %d",
               process[i].id, process[i].completion_time, process[i].TAT, process[i].WT);
    }

    // average Turnaround Time  and Waiting Time 
    float avg_TAT = (float)total_TAT / n;
    float avg_WT = (float)total_WT / n;

    printf("\n\nAverage Turnaround Time (TAT): %f", avg_TAT);
    printf("\nAverage Waiting Time (WT): %f", avg_WT);

    return 0;
}
