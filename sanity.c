#include "types.h"
/*#include "stat.h"*/
#include "user.h"

struct perf {
  int ctime;
  int ttime;
  int stime;
  int retime;
  int rutime;
};

void printStat(struct perf * myPerf, int status){
	printf(1, "%d\tstart\t\t%d\n",status, myPerf->ctime);
	printf(1, "%d\tend\t\t%d\n",status, myPerf->ttime);
	printf(1, "%d\tsleep\t\t%d\n",status, myPerf->stime);
    printf(1, "%d\trunnable\t%d\n",status, myPerf->retime);
    printf(1, "%d\trunning\t\t%d\n",status, myPerf->rutime);
    printf(1, "%d\tturnaround\t%d\n",status, myPerf->ttime-myPerf->ctime);
	if(myPerf->ttime-myPerf->ctime != 0) {
		printf(1, "%d\tSpent %d\% as runnable\n",status, (myPerf->retime*100/(myPerf->ttime-myPerf->ctime)));
    	printf(1, "%d\tSpent %d\% in sleep\n",status, (myPerf->stime*100/(myPerf->ttime-myPerf->ctime)));
	}
    printf(1, "\n");
}

void countDown(int n) {
	if (n <= 1)
		return;
	countDown(n-1);
	countDown(n-2);
	
}

void sleeper(){
	for (int i=0; i<500 ;i++)
	 	sleep(1);
	
	
}

void counter(){
	countDown(24);
}

void test(int processes, void fstFunc(), void secFunc()) {
    int status;
    struct perf procPerf;
    for (int j=0; j < 3; j++) {
	    for (int i=0; i < processes; i++){
		    if (fork()==0){
		    	
		    	if (i%9 == 2 || i == 28) // 2, 11, 20, 28, 29
		    		priority(10);
		    	if (i%11 == 1) // 1, 12, 23
		    		priority(0);
				
				
		    	if (i%2 == 0){
					fstFunc();
		    	}
		    	else{
					secFunc();
		    	}
		    	exit(i);
		    }
		}
		for (int i=0; i<processes; i++){
			wait_stat(&status, &procPerf);
			printStat(&procPerf, status);
		}
	}
}


int main(void){
	// int pid;
	// int first_status;
	// int second_status;
	// int third_status;
	
	// policy(1);
    // test(30, &counter, &sleeper);
    // printf(1, "\n");
	// policy(2);
    // test(30, &counter, &sleeper);
	// printf(1, "\n");
	policy(3);
    test(30, &counter, &sleeper);
	policy(2);
    // test(30, &counter, &sleeper);
	// policy(2);
	// pid = fork(); // the child pid is 99
	// if(pid > 0) {          
 	// 	first_status = detach(pid); // status = 0
	// 	printf(2, "detach -> %d\n",first_status);
 	// 	second_status = detach(pid); // status = -1, because this process has already
	// 	printf(2, "detach -> %d\n",second_status);
 	// 	// detached this child, and it doesn’t have
 	// 	// this child anymore.
 	// 	third_status = detach(pid); // status = -1, because this process doesn’t
	// 	printf(2, "detach -> %d\n",third_status);
 	// 	//have a child with this pid.
	//}
  exit(0);
}
