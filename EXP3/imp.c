#include <stdio.h>
#include "header.h"

// FCFS
void calculate_fcfs(int n, float at[], float bt[], float ct[], float tat[], float wt[]) {

    int completed[10] = {0};
    float current_time = 0;

    for (int count = 0; count < n; count++) {

        int next = -1;
        float min_at = 99999;

        for (int i = 0; i < n; i++) {

            if (!completed[i] && at[i] < min_at) {

                min_at = at[i];
                next = i;
            }
        }

        if (current_time < at[next])
            current_time = at[next];

        current_time += bt[next];

        ct[next] = current_time;
        tat[next] = ct[next] - at[next];
        wt[next] = tat[next] - bt[next];

        completed[next] = 1;
    }
}

// SJF
void calculate_sjf(int n, float at[], float bt[], float ct[], float tat[], float wt[]) {

    int completed[10] = {0};
    float current_time = 0;
    int count = 0;

    while (count < n) {

        int index = -1;
        float min_bt = 99999;
        float min_at = 99999;

        for (int i = 0; i < n; i++) {

            if (at[i] <= current_time && completed[i] == 0) {

                if (bt[i] < min_bt) {

                    min_bt = bt[i];
                    index = i;
                }
            }

            if (!completed[i] && at[i] < min_at)
                min_at = at[i];
        }

        if (index == -1) {

            current_time = min_at;
        }
        else {

            current_time += bt[index];

            ct[index] = current_time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            completed[index] = 1;
            count++;
        }
    }
}

// SRTF
void calculate_srtf(int n, float at[], float bt[], float ct[], float tat[], float wt[]) {

    float rt[10];
    int completed = 0;
    float current_time = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    while (completed < n) {

        int index = -1;
        float min_rt = 99999;
        float min_at = 99999;

        for (int i = 0; i < n; i++) {

            if (at[i] <= current_time && rt[i] > 0) {

                if (rt[i] < min_rt) {

                    min_rt = rt[i];
                    index = i;
                }
            }

            if (rt[i] > 0 && at[i] < min_at)
                min_at = at[i];
        }

        if (index == -1) {

            current_time = min_at;
            continue;
        }

        rt[index]--;
        current_time++;

        if (rt[index] <= 0) {

            ct[index] = current_time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            completed++;
        }
    }
}
// Round Robin
void calculate_rr(int n, float at[], float bt[], float ct[], float tat[], float wt[], float quantum) {

    float rt[10];
    int queue[100];
    int front = 0, rear = 0;
    int in_queue[10] = {0};
    int completed = 0;

    float current_time = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    float min_at = at[0];

    for (int i = 1; i < n; i++)
        if (at[i] < min_at)
            min_at = at[i];

    current_time = min_at;

    for (int i = 0; i < n; i++) {

        if (at[i] <= current_time) {

            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n) {

        if (front == rear) {

            float next = 99999;

            for (int i = 0; i < n; i++)
                if (rt[i] > 0 && at[i] < next)
                    next = at[i];

            current_time = next;

            for (int i = 0; i < n; i++) {

                if (at[i] <= current_time && rt[i] > 0 && !in_queue[i]) {

                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }

            continue;
        }

        int p = queue[front++];

        float start = current_time;

        float execute = (rt[p] > quantum) ? quantum : rt[p];

        rt[p] -= execute;
        current_time += execute;

        for (int i = 0; i < n; i++) {

            if (at[i] > start && at[i] <= current_time && rt[i] > 0 && !in_queue[i]) {

                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (rt[p] > 0) {

            queue[rear++] = p;
        }
        else {

            ct[p] = current_time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];

            completed++;
            in_queue[p] = 0;
        }
    }
}

// Preemptive Priority
void calculate_priority(int n, float at[], float bt[], int pr[], float ct[], float tat[], float wt[]) {

    int completed[10] = {0};
    float remaining_time[10];

    for (int i = 0; i < n; i++)
        remaining_time[i] = bt[i];

    float current_time = 0;
    int count = 0;

    while (count < n) {

        int index = -1;
        int priority = 99999;
        float min_at = 99999;

        for (int i = 0; i < n; i++) {

            if (at[i] <= current_time && completed[i] == 0) {

                if (pr[i] < priority) {

                    priority = pr[i];
                    index = i;
                }
                else if (pr[i] == priority) {

                    if (at[i] < at[index])
                        index = i;
                }
            }

            if (!completed[i] && at[i] < min_at)
                min_at = at[i];
        }

        if (index == -1) {

            current_time = min_at;
        }
        else {

            remaining_time[index]--;
            current_time++;

            if (remaining_time[index] <= 0) {

                ct[index] = current_time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];

                completed[index] = 1;
                count++;
            }
        }
    }
}
// Display Table
void display_table(int n, float at[], float bt[], float ct[], float tat[], float wt[]) {

    float avg_tat = 0;
    float avg_wt = 0;

    printf("\n-------------------------------------------------------------");
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT");
    printf("\n-------------------------------------------------------------");

    for (int i = 0; i < n; i++) {

        printf("\nP%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",
               i + 1,
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\n-------------------------------------------------------------");
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
}
