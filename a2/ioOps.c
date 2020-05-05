#include <stdio.h>
#include "structs.h"
#include "queueOps.h"




void ioEnqueue(ui pid, Arrays array, process processes[]){

  array.io->io[array.io->ioCount]=pid;
  processes[pid].curIo=0;
  array.io->ioCount++;

}



void doIOcounters(Arrays array, process processes[]){

  for (size_t i = 0; i < array.io->ioCount; i++) {
    if(processes[array.io->io[i]].curIo==processes[array.io->io[i]].cpu){
      processes[array.io->io[i]].ioTotal+=processes[array.io->io[i]].curIo;
      enqueue(array.io->io[i], array, processes);

      for (size_t j = i; i < array.io->ioCount; i++) {
        array.io->io[j]=array.io->io[j+1];
      }
      array.io->ioCount--;

  }else{
      processes[array.io->io[i]].curIo++;

    }

  }


}




ui ioDequeue(Arrays array){

  ui returnPid= array.io->io[0];
  for (size_t i = 0; i < array.io->ioCount; i++) {
    array.io->io[i]=array.io->io[i+1];
  }
  array.io->ioCount--;


  return returnPid;

}
