#include "kernel/date.h"
#include "kernel/defs.h"
#include "kernel/memlayout.h"
#include "kernel/mmu.h"
#include "kernel/param.h"
#include "kernel/proc.h"
#include "kernel/types.h"
#include "kernel/x86.h"


int sys_fork(void) {
  return fork();
}

int sys_exit(void) {
  exit();
  return 0; // not reached
}

int sys_wait(void) {
  return wait();
}

int sys_kill(void) {
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void) {
  return proc->pid;
}

int sys_sbrk(void) {
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void) {
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n) {
    if(proc->killed) {
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
int sys_uptime(void) {
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// part 1
int sys_wait_stat(void){
  int* c_time;
  int* t_time;
  int* re_time;
  int* ru_time;
  int* s_time;
  int pid;
  
  if(argptr(0, (char **) &c_time, sizeof(int)) < 0){
    return -1;
  }
  if(argptr(1, (char **) &t_time, sizeof(int)) < 0){
    return -1;
  }
  if(argptr(2, (char **) &re_time, sizeof(int)) < 0){
    return -1;
  }
  if(argptr(3, (char **) &ru_time, sizeof(int)) < 0){
    return -1;
  }
  if(argptr(4, (char **) &s_time, sizeof(int)) < 0){
    return -1;
  }
  pid = wait_stat(c_time, t_time, re_time, ru_time, s_time);
  return pid;
}
