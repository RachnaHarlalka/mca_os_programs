#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int process_id,arrival_time,burst_time,completion_time,turn_around_time,waiting_time,isDone;
}process;

int sortByAT(process *,int);

int main(){
    int no_of_process,status;
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
    printf("Longest Job first\n");

    status=LJF(processArray,no_of_process);
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

int LJF(process *p,int n)
{
    // int *BTArray;
    int i,totalProcess=0,index,currentLargestBT,currentTime=0;
    float avgTAT=0.0,avgWT=0.0;

    // BTArray = (int *)malloc(sizeof(int) * n);
    // if(BTArray == NULL)
    // {
    //     return -1;
    // }

    // for (i = 0; i < n; i++)
    // {
    //     BTArray[i] = p[i].burst_time;
    // }

    printf("Gantt Chart : ");
printf("\n --------------------------------\n");

    while (totalProcess < n)
    {
        index = -1;  //this index will help in a situation when there is no process to run in current time, so if index is -1 , we will increment the current time
        currentLargestBT = 0;

        //finding the largest burst time among the process that are yet to be precessed
        for (i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= currentTime && p[i].isDone == 0)
            {
                if (p[i].burst_time > currentLargestBT)
                {
                    currentLargestBT = p[i].burst_time;
                    index = i;
                }
            }
        }

        if (index != -1)
        {
            printf(" | P%d | ", p[index].process_id);
            while (p[index].burst_time != 0)
            {
                p[index].burst_time--;
                currentTime++;
            }

            if (p[index].burst_time == 0)
            {
                p[index].completion_time = currentTime;
                p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
                p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
                p[index].isDone = 1;
                totalProcess++;
            }
        }
        else
        {
            currentTime++;
        }
    }
printf("\n --------------------------------\n");
    printf("\n\n");
    printf("Process\t  Arrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n");

    for (i = 0; i < n; i++)
    {
        avgWT += p[i].waiting_time;
        avgTAT += p[i].turn_around_time;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].turn_around_time, p[i].waiting_time);
    }

    printf("\n");
    printf("Average Waiting time : %.2f\n", avgWT / n);
    printf("Average Turn around time : %.2f\n", avgTAT / n);


    return 0;
}

