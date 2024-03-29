//preemtive version of shortest job first

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int process_id,arrival_time,burst_time,completion_time,turn_around_time,waiting_time,isDone;
}process;

int sortByAT(process*,int);
int SRJF(process*,int); 

int main(){
    int no_of_process,status;
    float avgTAT=0.0,avgWT=0.0;
    process *processArray;
    printf("Enter the number of process : ");
    scanf("%d",&no_of_process);
    processArray = (process*)malloc(sizeof(process)*no_of_process);
    if(processArray ==NULL)
    {
        return -1;
    }
    for(int i=0;i<no_of_process;i++)
    {
        printf("For the process P%d\n",i+1);
        printf("Enter the arrival time : ");
        scanf("%d",&processArray[i].arrival_time);
        printf("Enter the burst time : ");
        scanf("%d",&processArray[i].burst_time);
        processArray[i].process_id=i+1;
        processArray[i].isDone = 0;
        processArray[i].completion_time=0;
        processArray[i].turn_around_time=0;
        processArray[i].waiting_time=0;
        printf("\n");
    }
    sortByAT(processArray,no_of_process);

    printf("Shortest remaining Job first\n");

    status=SRJF(processArray,no_of_process);
    if(status!=0)
    {
        printf("Unsuccessfull !!");
    }
    printf("\n --------------------------------\n");
    printf("\n\n");
    printf("Process\t  Arrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    for (int i = 0; i < no_of_process; i++)
    {
        avgWT += processArray[i].waiting_time;
        avgTAT += processArray[i].turn_around_time;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processArray[i].process_id, processArray[i].arrival_time, processArray[i].burst_time, processArray[i].turn_around_time, processArray[i].waiting_time);
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", avgWT / no_of_process);
    printf("Average Turn around time : %.2f\n", avgTAT / no_of_process);

    return 0;

}

//applyiing insertion sort to sort ptocess by arrival time
sortByAT(process *p,int n){
    int i,j;
    for( i=1;i<n;i++)
    {
        process temp=p[i];
        for( j=i-1;j>=0;j--)
        {
            if (p[j].arrival_time>temp.arrival_time)
            {
                p[j+1]=p[j];
            }
            else
                break;
        }
        p[j+1]=temp;
    }
return 0;
}

int SRJF(process *p,int n)
{
    int *remaining_BT;
    int i,total=0,index,currentSmallestBT,currentTime=0,prev=-1;
    // float avgTAT=0.0,avgWT=0.0;

    remaining_BT = (int *)malloc(sizeof(int) * n);
    if(remaining_BT == NULL)
    {
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        remaining_BT[i] = p[i].burst_time;
    }

    printf("Gantt Chart : ");
    printf("\n --------------------------------\n");

    while (total < n)
    {
        index = -1;
        currentSmallestBT = __INT_MAX__;
        for (i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= currentTime && p[i].isDone == 0)
            {
                if (remaining_BT[i] < currentSmallestBT)
                {
                    currentSmallestBT = remaining_BT[i];
                    index = i;
                }
            }
        }

       if (index != -1)
        {
            if (prev != index)
            {
                printf("P%d ", p[index].process_id);
            }
            remaining_BT[index]--;
            currentTime++;
            prev = index;
            if (remaining_BT[index] == 0)
            {
                p[index].completion_time = currentTime;
                p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
                p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
                p[index].isDone = 1;
                total++;
            }
        }
        else
        {
            currentTime++;
        }
    }
    free(remaining_BT);

    return 0;
}

