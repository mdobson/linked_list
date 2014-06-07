#include <stdio.h>
#include <stdlib.h>

struct node {
  int x;
  struct node *next;
};

struct list {
  struct node *head;
  int count;
  void (*add)(struct list *p_list, struct node *p_node);
  void (*delete)(struct list *p_list, int value);
  void (*iterate)(struct list *p_list, void (*f)(int));
};

struct list * newList();
struct node * newNode();
void add(struct list *p_list, struct node *p_node);
void delete(struct list *p_list, int value);
void iterate(struct list *p_list, void (*f)(int));

struct node * newNode() {
  struct node * newNode = (struct node *) malloc(sizeof(struct node));
  newNode -> next = 0;
  return newNode;
}

struct list * newList() {
  struct list *newList = (struct list *) malloc(sizeof(struct list));
  newList -> add = add;
  newList -> delete = delete;
  newList -> iterate = iterate;
  return newList;
}

void add(struct list *p_list, struct node *p_node) {
  struct node *cur;
  cur = p_list -> head;
  while(cur -> next != 0) {
    cur = cur -> next;
  }
  cur -> next = p_node;
}

void delete(struct list * p_list, int val) {
  struct node *cur;
  struct node * prev;
  cur = p_list -> head;
  while(cur -> x != val) {
    prev = cur;
    cur = cur -> next;
  }

  prev -> next = cur -> next;
  free(cur);
}

void iterate(struct list *p_list, void (*f)(int)) {
  struct node *iter;
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
  struct list *list;
  struct node *root;
  struct node *second;

  list = newList();
  root = newNode();
  second = newNode();
  root -> x = 1;
  list -> head = root;
  
  second -> x = 2;

  list -> add(list, second);
  list -> iterate(list, print);
  
}
