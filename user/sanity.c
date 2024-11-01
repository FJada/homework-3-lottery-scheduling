#include "user.h"


// Fibonacci sequence
int fib(int n) {
  if(n <= 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

// Use this for long computation
// fib(39) takes roughly 30 secs
void longComputation() {
  fib(2);
}


int main(int argc, char* argv[]) {
  //child proc stats
  int* c_time = 0;
  int* t_time = 0;
  int* re_time = 0;
  int* ru_time = 0;
  int* s_time = 0;
  int pid;
  //average stats
  int total_c_time = 0;
  int total_t_time = 0;
  int total_re_time = 0;
  int total_ru_time = 0;
  int total_s_time = 0;

  //child process 20x
  for(int i = 0; i < 20; i++){
    pid = fork();
    // parent process
    if(pid > 0){
      // call wait stat
      pid = wait_stat(c_time, t_time, re_time, ru_time, s_time);
      
    }
   //child process
    else if(pid == 0){
        // run something
        longComputation();
        //print time stats
        printf("PID[%d] Creation[%d] Termination[%d] Ready Time[%d] Running Time[%d] Sleep Time[%d] \n", pid, *c_time, *t_time, *re_time, *ru_time, *s_time);
        //get sum
        total_c_time +=  *c_time;
        total_t_time += *t_time;
        total_re_time += *re_time;
        total_ru_time += *re_time;
        total_s_time += *s_time;
       
    }
  
  }
  printf("Avg. Wait Time[%d] Avg. Running Time[%d] Avg. Sleep Time[%d] Avg. Turnaround Time[%d]\n", (total_re_time / 20), (total_ru_time / 20),(total_s_time / 20), ((total_c_time + total_t_time) / 20) );
  exit();
}
