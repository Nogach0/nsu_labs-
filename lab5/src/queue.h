#ifndef LAB5_QUEUE_H
#define LAB5_QUEUE_H

#include "common.h"
#include "tree.h"

typedef struct QueueNode {
  TreeNode *node;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  struct QueueNode *front;
  struct QueueNode *back;
} Queue;

Queue *CreateQueue();
QueueNode *CreateQueueNode(TreeNode *tree_node);
int IsEmpty(Queue *queue);
void Push(Queue *queue, TreeNode *tree_node);
TreeNode *Delete(Queue *queue);
void DestroyQueue(Queue *queue);

#endif // LAB5_QUEUE_H
