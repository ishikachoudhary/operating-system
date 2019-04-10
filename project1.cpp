#include<stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>

struct process{
	int priority;
	int burst_time;
	int pid;
	int waiting_time;
	int turnaround_time;
	int remaining_time;
	int arrival_time;
};

void delay();
void getIn();
void calcWaitingTime(struct process *z,int);
void calcTurnAroundTime(struct process *z,int);
void printQueue(struct process *z,int Size1);
void RR();
void priSort();
void FCFS();
void printQueueI(struct process);
void printQueue(struct process *,int);

//Queues
//Q1 = Batch Process having Low Priority with FCFS Algorithm
//Q2 = Interactive Process having Medium Priority with Priority Based Sorting
//Q3 = System Process having High Priority with Round Robin Algorith Quantum Time=4
int q1_n=0,q2_n=0,q3_n=0,n=0; //N=Total Process
struct process *q1,*q2,*q3;
//Time Quantum
int time_quantum = 4;
void getIn(){
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//Allocatig Memory
	q1 = (struct process *)malloc(n*sizeof(struct process));
	q2 = (struct process *)malloc(n*sizeof(struct process));
	q3 = (struct process *)malloc(n*sizeof(struct process));
	for(int i=0;i<n;i++){
		struct process p;
		printf("\n\t\tProcess %d\n=============================================\n\n",i+1);
		p.arrival_time = (rand())%(n+1);
		printf("PId:\t");
		scanf("%d",&p.pid);
		printf("Priority (1-9):\t");
		scanf("%d",&p.priority);
		printf("\nBurst Time: %d\t",p.burst_time);
		scanf("%d",&p.burst_time);
		p.remaining_time = p.burst_time;
		if(p.priority>0 && p.priority<=3){
			q1[q1_n++]  = p;
		}else if(p.priority>3 && p.priority<=6){
			q2[q2_n++] = p;
		}else{
			q3[q3_n++] = p;
		}
	}
}
void printQueue(struct process *z,int Size1){
	calcWaitingTime(z,Size1);
	calcTurnAroundTime(z,Size1);
	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
	printf("\n================================================================================\n");
	for(int i=0;i<Size1;i++){
		printQueueI(z[i]);
	}
	printf("\n\n");
}
void printQueueI(struct process p){
	printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",p.pid,p.priority,p.burst_time,p.waiting_time,p.turnaround_time,p.arrival_time);
}
void calcWaitingTime(struct process *z,int Size1){
	z[0].waiting_time = 0;
	for(int i=1;i<Size1;i++){
		z[i].waiting_time = z[i-1].waiting_time + z[i-1].burst_time;
	}
}
void calcTurnAroundTime(struct process *z,int Size1){
	z[0].waiting_time = 0;
	for(int i=0;i<Size1;i++){
		z[i].turnaround_time = z[i].waiting_time + z[i].burst_time;
	}
}
void RRAlgo(struct process *z,int Size1){
	int time=0,i=0,remain=Size1,flag=0,wait_time=0,tat_time=0,total_times=0;
	for(time=0,i=0;remain!=0;){
		struct process p = z[i];
		if(p.remaining_time<=time_quantum && p.remaining_time>0){
			time += p.remaining_time;
			p.remaining_time = 0;
			flag = 1;
		}else if(p.remaining_time>time_quantum){
			p.remaining_time -= time_quantum;
			time += time_quantum;
		}
		if(p.remaining_time==0 && flag==1){
			remain--;
			printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.priority,p.burst_time,p.waiting_time,p.turnaround_time);
			wait_time += time -p.arrival_time - p.burst_time;
			tat_time += time -p.arrival_time;
			flag = 0;
		}

		if(i==remain-1){
			i=0;
		}else if(z[i+1].arrival_time<time){
			i++;
		}else{
			i=0;
		}

		z[i] = p;
	}
	printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
	printf("Avg Turnaround Time = %f\n",tat_time*1.0/n);
}
void RR(){
	printf("\n\n===========================================================================");
	printf("\n\t\tRound Robin\t");
	printf("\n===========================================================================\n\n");

	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time");
	printf("\n================================================================================\n");
	calcWaitingTime(q3,q3_n);
	calcTurnAroundTime(q3,q3_n);

	RRAlgo(q3,q3_n);
}
void priSortAlgorithm(struct process *z,int Size1){
	for(int i=0;i<Size1;i++){
		for(int j=0;j<Size1;j++){
			if(z[j].priority>z[i].priority){
				struct process t = z[i];
				z[i] = z[j];
				z[j] = t;
			}
		}
	}
}
void priSort(){
	printf("\n\n===========================================================================");
	printf("\n\t\tPriority Sorting\t");
	printf("\n===========================================================================\n\n");
	priSortAlgorithm(q2,q2_n);
	printQueue(q2,q2_n);
}
void FCFSAlgorithm(struct process *z,int Size1){
	for(int i=0;i<Size1;i++){
		for(int j=0;j<Size1;j++){
			if(z[j].arrival_time>z[i].arrival_time){
				struct process t = z[i];
				z[i] = z[j];
				z[j] = t;
			}
		}
	}
}
void FCFS(){
	printf("\n\n===========================================================================");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n===========================================================================\n\n");
	FCFSAlgorithm(q1,q1_n);
	printQueue(q1,q1_n);
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

int main(){
    system("color 2a");
	getIn();
	int i=1;
	while(n>0){
		switch(i){
			case 3:
				RR();
				break;
			case 2:
				priSort();
				break;
			case 1:
				FCFS();
				break;
		}
		i++;
		delay(10);
		//sleep(10);
		//return 0;
	}
	printf("\n\n");
	system("cls");
	//return 0;
}

