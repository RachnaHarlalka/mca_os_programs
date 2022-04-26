//non - preemtive version of priority scheduling

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int process_id,arrival_time,burst_time,completion_time,turn_around_time,waiting_time,isDone,response_time,priority;
}process;

int main()
{
        int no_of_process,i,status;
        process *processArray;
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
        void sortByAT(process *processArray,int no_of_process);

        status=priority(processArray,no_of_process);
        if(status!=0)
                printf("unsuccessful!!");
        free(processArray);
        return 0;


}
void sortByAT(process *p,int n){
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

}
int priority(process*p,int n)
{
        int i,isDone=0,index,morePriority,current_time=0;
        float avgTAT=0.0, avgWT=0.0;
         
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
                                }
                        }
                } 
                if(index!=-1)
                {
                        printf("| P%d |",p[index].process_id);
                        current_time+=p[index].burst_time;
                        p[index].turn_around_time=current_time-p[index].arrival_time;
                        p[index].waiting_time=p[index].turn_around_time-p[index].burst_time;
                        p[index].isDone=1;
                        isDone++;

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