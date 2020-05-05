#ifndef QUEUEOPS_H
#define QUEUEOPS_H

#include "structs.h"


void enqueue(ui pid,Arrays array, process processes[]);

ui dequeue(Arrays array, process processes[]);

void doQueueCounters(Arrays array, os controlVars, process processes[]);
















#endif
