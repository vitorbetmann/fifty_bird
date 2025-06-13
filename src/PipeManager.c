#include "PipeManager.h"
#include "Pipe.h"
#include "raylib.h"
#include "stdlib.h"

float spawnTimer = 0.0f;

void PipesEnqueue(Pipe *pipe, PipeQueue *pipes) {
  PipeNode *newNode = malloc(sizeof(PipeNode));
  if (newNode == NULL) {
    return;
  }

  newNode->pipe = pipe;
  newNode->next = NULL;

  if (pipes->head == NULL) {
    pipes->head = pipes->tail = newNode;
  } else {
    pipes->tail->next = newNode;
    pipes->tail = newNode;
  }
}

void PipesDequeue(PipeQueue *pipes) {
  if (pipes->head == NULL) {
    return;
  }
  PipeNode *temp = pipes->head;
  pipes->head = pipes->head->next;

  if (pipes->head == NULL) {
    pipes->tail = NULL;
  }

  PipesUnloadNode(temp);
}

void PipesUpdate(PipeQueue *pipes, float dt, Vector2 screen) {

  if (CanGeneratePipe(dt)) {
    PipesEnqueue(NewPipe(screen), pipes);
  }

  PipeNode *curr = pipes->head;
  while (curr != NULL) {
    PipeUpdate(curr->pipe, dt);
    PipeNode *next = curr->next;
    if (curr->pipe->pos.x < -curr->pipe->width) {
      PipesDequeue(pipes);
    }
    curr = next;
  }
}

bool CanGeneratePipe(float dt) {
  spawnTimer += dt;
  if (spawnTimer > 2) {
    spawnTimer = 0.0f;
    return true;
  }
  return false;
}

void PipesDraw(PipeQueue *pipes) {
  PipeNode *curr = pipes->head;
  while (curr != NULL) {
    PipeDraw(curr->pipe);
    curr = curr->next;
  }
}

void PipesUnload(PipeQueue *pipes) {
  PipeNode *curr = pipes->head;
  while (curr != NULL) {
    PipeNode *next = curr->next;
    PipesUnloadNode(curr);
    curr = next;
  }

  pipes->head = pipes->tail = NULL;
}

void PipesUnloadNode(PipeNode *pipeNode) {
  free(pipeNode->pipe);
  free(pipeNode);
}