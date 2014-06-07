#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int x;
  struct node *next;
} Node;

typedef struct list {
  Node *head;
  int count;
  void (*add)(struct list *p_list, struct node *p_node);
  void (*delete)(struct list *p_list, int value);
  void (*iterate)(struct list *p_list, void (*f)(int));
} List;

List * newList();
Node * newNode();
void add(List *p_list, Node *p_node);
void delete(List *p_list, int value);
void iterate(List *p_list, void (*f)(int));

Node * newNode() {
  Node * newNode = (Node *) malloc(sizeof(Node));
  newNode -> next = 0;
  return newNode;
}

List * newList() {
  struct list *newList = (struct list *) malloc(sizeof(struct list));
  newList -> add = add;
  newList -> delete = delete;
  newList -> iterate = iterate;
  newList -> count = 0;
  return newList;
}

List *newListWithHead(struct node *p_head) {
  List *list = newList();
  list -> head = p_head;
  list -> count = 1;
  return list;
}

void add(List *p_list, struct node *p_node) {
  Node *cur;
  cur = p_list -> head;
  while(cur -> next != 0) {
    cur = cur -> next;
  }
  p_list -> count = p_list -> count + 1;
  cur -> next = p_node;
}

void delete(List * p_list, int val) {
  Node *cur;
  Node * prev;
  cur = p_list -> head;
  while(cur -> x != val) {
    prev = cur;
    cur = cur -> next;
  }

  prev -> next = cur -> next;
  p_list -> count = p_list -> count - 1;
  free(cur);
}

void iterate(struct list *p_list, void (*f)(int)) {
  Node *iter;
  iter = p_list -> head;
  while(iter != 0) {
    (*f)(iter -> x);
    iter = iter -> next;
  }
}

void print(int x) {
  printf("PRINTING: %d\n", x);
}

int main() {
  List *list;
  Node *root;
  Node *second;

  list = newList();
  root = newNode();
  second = newNode();
  root -> x = 1;
  list -> head = root;
  
  second -> x = 2;

  list -> add(list, second);
  list -> iterate(list, print);
  
}
