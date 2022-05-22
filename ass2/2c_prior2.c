//preemtive version of priority

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int process_id,arrival_time,burst_time,completion_time,turn_around_time,waiting_time,isDone,response_time,priority;
}process;

int sortByAT(process*,int);
int priority(process*,int);

int main()
{
        int no_of_process,i,status;
        // float avgTAT=0.0, avgWT=0.0;
        process *processArray;
        printf("..........PREEMTIVE PRIORITY SCHEDULING...........\n ");
        printf("Enter the no. of processes ");
        scanf("%d",&no_of_process);
        processArray=(process*)malloc(sizeof(process)*no_of_process);
        if(processArray==NULL)
        {
                return -1;
        }
        for(i=0;i<no_of_process;i++)
        {
                printf("For the process P%d\n",i+1);
                printf("Enter the priority value : ");
                scanf("%d",&processArray[i].priority);
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

        printf("Preemtive priority scheduling !!\n");

        status=priority(processArray,no_of_process);
        if(status!=0)
                printf("unsuccessful!!");
        else 
                printf("Succcessfull !!");
                
       
        free(processArray);
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

//scheduling function

int priority(process*p,int n)
{
        int *remaining_BT;
        int i,isDone=0,index,morePriority,current_time=0,prev=-1;
               float avgTAT=0.0, avgWT=0.0;

        remaining_BT = (int *)malloc(sizeof(int) * n);
        if(remaining_BT == NULL)
        {
                return -1;
        }

        for (i = 0; i < n; i++)
        {
                remaining_BT[i] = p[i].burst_time;
        }
        
        printf("\n\nGantt Chart : ");
        printf("\n --------------------------------\n");

        while(isDone!=n)
        {
                index=-1;
                morePriority= __INT_MAX__;
                for(i=0;i<n;i++)
                {
                        if(p[i].arrival_time<=current_time && p[i].isDone==0)
                        {
                                if(p[i].priority<morePriority)
                                {
                                        morePriority=p[i].priority;
                                        index=i;
                                        // printf("hello i am inside priority more\n");

                                }
                        }
                } 
                if(index!=-1)
                {
                        if (index != prev)
                                {
                                printf("| P%d |", p[index].process_id);
                                }
                        prev = index;
                        current_time++;
                        remaining_BT[index]--;

                        if (remaining_BT[index] == 0)
                        {
                                p[index].completion_time = current_time;
                                p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
                                p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
                                p[index].isDone = 1;
                                isDone++;
                                // printf("hello i am inside bt==0");
                        }
                }
                else
                        current_time++;
        }
        
         printf("\n");
        printf("Process\tPN\tAT\tBT\tWT\t TAT\n");
        for(i=0;i<n;i++)
        {
                printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].process_id,p[i].priority,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turn_around_time);

                avgWT+=p[i].waiting_time;
                avgTAT+=p[i].turn_around_time;
        }
        printf("Average Waiting Time:%.2f\n",avgWT/n);

        printf("Average Turn Around Time:%.2f\n",avgTAT/n);

        return 0;
}