#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int process_id,arrival_time,burst_time,completion_time,turn_around_time,waiting_time,isDone,response_time;
}process;
int sortByAT(process *,int);
int RR(process*,int,int);

int main(){
    int no_of_process,status,q;
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
        processArray[i].response_time=processArray[i].burst_time;
        printf("\n");
    }
    sortByAT(processArray,no_of_process);

    printf("Enter the time quantum");
    scanf("%d",&q);
    printf("/n");
    
    printf("Round Robin\n");

    status=RR(processArray,no_of_process,q);
    if(status!=0)
    {
        printf("Unsuccessfull !!");
    }

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
//  for(i=0;i<n;i++)
//  {
//      printf("%d",p[i].process_id);
//  }
return 0;
}

int RR(process *p,int n, int TQ)
{
    int i, j, time, remain, flag = 0;
    float avgWT = 0.0, avgTAT = 0.0;

    time = 0;
    i = 0;
    remain = n;

    printf("Gantt Chart\n");

    while (remain)
    {
        //situation when remaining burst time is less than time quantum and greater than 0
        if (p[i].response_time <= TQ && p[i].response_time > 0)
        {
            time = time + p[i].response_time;
            printf(" P%d ", p[i].process_id);
            p[i].response_time = 0;
            flag = 1;
        }
        //situation when remaining burst time is greater then time quantum
        else if (p[i].response_time > 0)
        {
            p[i].response_time = p[i].response_time - TQ;
            time = time + TQ;
            printf(" P%d ", p[i].process_id);
        }
        //when remaining burst time is equal to 0 i.e process is processed
        if (p[i].response_time == 0 && flag == 1)
        {
            remain--;
            p[i].turn_around_time = time - p[i].arrival_time;
            p[i].waiting_time = time - p[i].arrival_time - p[i].burst_time;
            avgWT = avgWT + time - p[i].arrival_time - p[i].burst_time;
            avgTAT = avgTAT + time - p[i].arrival_time;
            flag = 0;
        }

        //when only one process is left by going sequentially
        if (i == n - 1)
        {
            i = 0;
        }
        else if (p[i + 1].arrival_time <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    printf("\n\n");
    printf("Process\tAT\tBT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].turn_around_time, p[i].waiting_time);
    }

    printf("\n");
    printf("Average Waiting Time : %.2f\n", avgWT / n);
    printf("Average Turn Around Time : %.2f\n", avgTAT / n);

    return 0;
}

