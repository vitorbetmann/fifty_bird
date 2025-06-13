#ifndef PIPE_MANAGER_H
#define PIPE_MANAGER_H
#include "Pipe.h"

// Data types
// ----------
typedef struct Pipes_t {
  Pipe *pipe;
  struct Pipes_t *next;
} PipeNode;

typedef struct {
  PipeNode *head;
  PipeNode *tail;
} PipeQueue;
// ----------

// Prototypes
// ----------
void PipesEnqueue(Pipe *pipe, PipeQueue *pipes);
void PipesDequeue(PipeQueue *pipes);
void PipesUpdate(PipeQueue *pipes, float dt, Vector2 screen);
bool CanGeneratePipe(float dt);
void PipesDraw(PipeQueue *pipes);
void PipesUnload(PipeQueue *pipes);
void PipesUnloadNode(PipeNode *pipeNode);
// ----------

// Variables
extern float spawnTimer;

#endif