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

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
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

int 
sys_ps(void) {
  ps();
  return 0;
}

int sys_build_container(void){
  return build_container();
}

int sys_tear_container(void){
  int i;
  if(argint(0, &i) < 0)
    return -1;
  return tear_container(i);
}

int sys_join_container(void){
  int i;
  if(argint(0, &i) < 0)
    return -1;
  return join_container(i);
}

int sys_exit_container(void){
  return exit_container();
}

int sys_scheduler_log_on(void){
  scheduler_log = 1;
  return 1;
}

int sys_scheduler_log_off(void){
  scheduler_log = 0;
  return 1;
}

int sys_memory_log_on(void){
  memory_log = 1;
  return 1;
}

int sys_memory_log_off(void){
  memory_log = 0; 
  return 1;
}

int
sys_getcid(void)
{
  return myproc()->container_id;
}

