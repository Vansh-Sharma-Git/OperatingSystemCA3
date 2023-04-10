#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int priority;
};

void printGanttChart(struct Process processes[], int n) {
    int i, j;
    printf(" ");
    for(i = 0; i < n; i++) {
        for(j = 0; j < processes[i].burstTime; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    for(i = 0; i < n; i++) {
        for(j = 0; j < processes[i].burstTime - 1; j++) printf(" ");
        printf("P%d", processes[i].pid);
        for(j = 0; j < processes[i].burstTime - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    for(i = 0; i < n; i++) {
        for(j = 0; j < processes[i].burstTime; j++) printf("--");
        printf(" ");
    }
    printf("\n");
}

float calculateAverageWaitingTime(struct Process processes[], int n) {
    int i;
    float totalWaitingTime = 0;
    for(i = 0; i < n; i++) totalWaitingTime += processes[i].waitingTime;
    return totalWaitingTime / n;
}

int main() {
    int n, i, j, currentTime = 0;
    printf("Enter number of jobs: ");
    scanf("%d", &n);
    struct Process processes[n];
    for(i = 0; i < n; i++) {
        printf("Enter arrival time and run time for process %d: ", i+1);
        scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i + 1;
        processes[i].waitingTime = 0;
        processes[i].priority = 1 + processes[i].waitingTime / processes[i].burstTime;
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    printf("\n");
    printf("Gantt Chart:\n");
    while(1) {
        int completed = 1, highestPriorityIndex = -1, highestPriority = -1;
        for(i = 0; i < n; i++) {
            if(processes[i].burstTime > 0 && processes[i].arrivalTime <= currentTime) {
                completed = 0;
                processes[i].waitingTime = currentTime - processes[i].arrivalTime;
                processes[i].priority = 1 + processes[i].waitingTime / processes[i].burstTime;
                if(processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }
        if(completed) break;
        processes[highestPriorityIndex].burstTime--;
        printf("%d ", currentTime);
        for(i = 0; i < n; i++) {
            if(processes[i].burstTime > 0 && processes[i].arrivalTime
<= currentTime) {
if(i == highestPriorityIndex) printf("|P%d|", processes[i].pid);
else printf(" P%d ", processes[i].pid);
}
else printf(" ");
}
printf("\n");
currentTime++;
}
printf("%d\n\n", currentTime);
printf("Individual waiting times:\n");
for(i = 0; i < n; i++) {
processes[i].waitingTime = currentTime - processes[i].arrivalTime - processes[i].burstTime;
printf("Job %d: %d\n", processes[i].pid, processes[i].waitingTime);
}
printf("\n");
float averageWaitingTime = calculateAverageWaitingTime(processes, n);
printf("Average waiting time: %f\n", averageWaitingTime);
return 0;
}
