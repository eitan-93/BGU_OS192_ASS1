#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int sys_exit(void){
int stat;
  //argint checkes whether 0 is a correct address, if so updates it in stat (cast to an int). else returns -1.
  //if 0 is incorrect, the exit status isn't "graceful".
  //this is a validity check for the current process, like in sys_kill.
  if(argint(0, &stat)< 0){
      return -1;
  }
  else {
      exit(stat);
      return 0;  // not reached
  }
}

int sys_wait(void){
   int stat = 0;   
   //like in sys_exit.
    if (argint(0,  &stat)< 0) {
       return -1;
    }
   //if(argptr(0, (char **) &stat, sizeof(int*))<0)
      //return -1;
   return wait((int*) stat);
}

int sys_wait_stat(void) {
    int stat;
    int perf;
    int pid;

    if(argint(0, &stat) < 0 || argint(1, &perf) < 0)
      return -1;
    // if (argint(0, &stat) < 0)
    //   return -1;

    // if (argint(1, &perf) < 0)
    //   return -1;
    // if(argptr(0, (char **) &stat, sizeof(int*)) < 0 || argptr(1, (char **) &perf, sizeof(struct perf*)));
    //   return -1;
    

    pid = wait_stat((int*)stat, (struct perf*) perf); 
    return pid;
}
 

int sys_detach(void){
   int pid;   
   //like in sys_exit.
   if (argint(0, &pid)< 0) {
      return -1;
   }
   return detach(pid);
}

int sys_priority(void){
   int p;   
   //like in sys_exit.
   if (argint(0, &p)< 0) {
      return -1;
   }
   priority(p);
   return 0;
}

int sys_policy(void){
   int p;   
   //like in sys_exit.
   if (argint(0, &p)< 0) {
      return -1;
   }
   policy(p);
   return 0;
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
