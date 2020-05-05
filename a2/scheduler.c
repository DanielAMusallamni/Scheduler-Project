#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "queueOps.h"
#include "ioOps.h"
#include "printStats.h"









void sort(Arrays arrays, int n, process processes[]){
  ui temp;
  for(ui i=0;i< n;i++)
  {
      for(ui j=i+1;j< n;j++)
      {
          if(processes[arrays.queue->queue[i]].curPrior< processes[arrays.queue->queue[j]].curPrior)
          {
              temp    =arrays.queue->queue[i];
              arrays.queue->queue[i]  =arrays.queue->queue[j];
              arrays.queue->queue[j]  =temp;
          }
      }
  }
}







int main(int argc, char const *argv[]) {



FILE * infile= fopen("a2in.txt","r");

os controlVars;
controlVars.quantum=70;
controlVars.wait=20;

process processes[48];

Arrays arrays;
arrays.queue= calloc(48,sizeof(queueArray*));
arrays.io= calloc(48,sizeof(ioArray*));

arrays.queue->queue=malloc(sizeof(ui)*48);
arrays.queue->queueCount= (ui)0;

arrays.io->io= malloc(sizeof(ui)*48);
arrays.io->ioCount=(ui)0;




ui cpu=0;// the cpu.. it only handles one process at a time. it's set to the index of the process in main array of processes


//==============================================================================
int counter=0;
while (fscanf(infile, "%u %u %u %u",&processes[counter].priority,&processes[counter].cpu,&processes[counter].io,&processes[counter].runTime)!=EOF) {


  processes[counter].curCpu=0;
  processes[counter].curIo=0;
  processes[counter].wait=0;
  processes[counter].curPrior=processes[counter].priority;
  processes[counter].cpuTotal=0;
  processes[counter].ioTotal=0;
  processes[counter].waitSum=0;
  processes[counter].waitCount=0;
  processes[counter].waitMin=48930438;//set to an arbitrary large number to start
  processes[counter].waitMax=0;
  processes[counter].isRunning=processes[counter].runTime;

  enqueue(counter, arrays, processes );


  counter++;
}
//============================================================================== read the file






cpu = dequeue(arrays, processes);





while (cpu !=-1 ) {


  if (processes[cpu].curCpu==controlVars.quantum){//time quantum check
    //check to see if it goes back into ready queue or io


    if(processes[cpu].curCpu==processes[cpu].cpu){
      //put into io
      processes[cpu].cpuTotal+=processes[cpu].curCpu;

      ioEnqueue(cpu, arrays, processes);

      cpu=dequeue(arrays, processes);
      processes[cpu].curCpu=0;



    } else{
      //put back into ready queue
      processes[cpu].cpuTotal+=processes[cpu].curCpu;

      enqueue(cpu, arrays, processes);

      cpu=dequeue(arrays, processes);
      processes[cpu].curCpu=0;



    }


  } else if(processes[cpu].curCpu==processes[cpu].cpu){//check if its ready for io
    //put into io
    processes[cpu].cpuTotal+=processes[cpu].curCpu;

    ioEnqueue(cpu, arrays, processes);
    cpu=dequeue(arrays, processes);
    processes[cpu].curCpu=0;


  } else if(processes[cpu].isRunning==0){//check to see if process is done running
    //process is done.. dont put it anywhere
    processes[cpu].cpuTotal+=processes[cpu].curCpu;

    cpu=-1;

    cpu=dequeue(arrays, processes);
    processes[cpu].curCpu=0;




  }else{
    //increment curcpu counter
    processes[cpu].isRunning--;
    processes[cpu].curCpu++;
  }

  doQueueCounters(arrays,  controlVars,processes);

  doIOcounters(arrays, processes);

  sort(arrays, arrays.queue->queueCount, processes);


  if (arrays.io->ioCount && arrays.queue->queueCount==0) {
    cpu=-1;

  }








}



printStats(processes, controlVars);









fclose(infile);
free(arrays.queue->queue);
free(arrays.io->io);
free(arrays.queue);
free(arrays.io);

  return 0;
}
