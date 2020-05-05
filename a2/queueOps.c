#include <stdio.h>
#include "structs.h"
#include "queueOps.h"





void enqueue(ui pid,Arrays array, process processes[]){

array.queue->queue[array.queue->queueCount]=pid;
processes[pid].wait=0;
processes[pid].waitCount++;
processes[pid].curPrior= processes[pid].priority;
array.queue->queueCount++;

}


ui dequeue(Arrays arrays, process processes[]){

  ui returnPid= arrays.queue->queue[0];

  if(processes[returnPid].wait>processes[returnPid].waitMax){
    //check if current wait time is greatter than max wait time
    processes[returnPid].waitMax=processes[returnPid].wait;
  } else if(processes[returnPid].wait<processes[returnPid].waitMin){
    //check if current wait time is less than min wait time
    processes[returnPid].waitMin=processes[returnPid].wait;

  }

  processes[returnPid].waitSum+=processes[returnPid].wait;


  for (size_t i = 0; i < arrays.queue->queueCount-1; i++) {
    arrays.queue->queue[i]=arrays.queue->queue[i+1];
  }
  arrays.queue->queueCount--;



  return returnPid;

}


void doQueueCounters(Arrays array, os controlVars, process processes[]){

  for (size_t i = 0; i < array.queue->queueCount; i++) {
    if(processes[array.queue->queue[i]].wait==controlVars.wait && processes[array.queue->queue[i]].curPrior<15){

      processes[array.queue->queue[i]].curPrior++;


    }else {
      processes[array.queue->queue[i]].wait++;
    }
  }



}
