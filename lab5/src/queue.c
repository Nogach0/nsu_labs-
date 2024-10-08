#include "queue.h"

Queue *CreateQueue() {
  Queue *queue = malloc(sizeof(Queue));
  queue->front = queue->back = NULL;

  return queue;
}

QueueNode *CreateQueueNode(TreeNode *tree_node) {
  QueueNode *queue_node = malloc(sizeof(QueueNode));

  queue_node->node = tree_node;
  queue_node->next = NULL;

  return queue_node;
}

int IsEmpty(Queue *queue) { return queue->front == NULL; }

void Push(Queue *queue, TreeNode *tree_node) {
  QueueNode *new_node = CreateQueueNode(tree_node);

  if (IsEmpty(queue) || tree_node->frequency < queue->front->node->frequency) {
    // If the queue is empty or the element should be inserted at the beginning
    // of the queue.
    new_node->next = queue->front;
    queue->front = new_node;
    if (queue->back == NULL) {
      queue->back = new_node;
    }
    return;
  }

  QueueNode *current = queue->front;
  // Find the correct place to insert the element.
  while (current->next != NULL) {
    if (tree_node->frequency < current->next->node->frequency) {
      break;
    }
    current = current->next;
  }

  new_node->next = current->next;
  current->next = new_node;

  if (new_node->next == NULL)
    queue->back = new_node;
}

TreeNode *Delete(Queue *queue) {
  if (IsEmpty(queue))
    return NULL;

  QueueNode *temp = queue->front;
  TreeNode *node = temp->node;
  queue->front = queue->front->next;

  if (queue->front == NULL)
    queue->back = NULL;

  free(temp);
  return node;
}

void DestroyQueue(Queue *queue) {
  if (queue == NULL)
    return;

  while (!IsEmpty(queue)) {
    Delete(queue);
  }

  free(queue);
}
