#include <stdio.h>
#include <stdlib.h>

struct node {
  int x;
  struct node *next;
  void (*add)(struct node* p_root, struct node*p_node);
  void (*delete)(struct node* p_root, int value);
};

struct node * new();
void add(struct node *p_root, struct node *p_node);
void delete(struct node *p_root, int value);

struct node * new() {
  struct node * newNode = (struct node *) malloc(sizeof(struct node));
  newNode -> add = add;
  newNode -> delete = delete;
  return newNode;
}

void add(struct node * p_root, struct node *p_node) {
  struct node *cur;
  cur = p_root;
  while(cur -> next != 0) {
    cur = cur -> next;
  }
  cur -> next = p_node;
}

void delete(struct node * p_root, int val) {
  struct node *cur;
  struct node * prev;
  cur = p_root;
  while(cur -> x != val) {
    prev = cur;
    cur = cur -> next;
  }

  prev -> next = cur -> next;
  free(cur);
}

int main() {
  struct node *root;
  struct node *conductor;
  struct node *iter;

  root = new();
  root -> next = 0;
  root -> x = 5;
  conductor = new();
  conductor -> next = 0;
  conductor -> x = 6;
  root -> add(root, conductor);
  conductor = new();
  conductor -> next = 0;
  conductor -> x = 7;
  root -> add(root, conductor);
  root -> delete(root, 6);

  iter = root;
  while(iter != 0) {
    printf("Value:%d\n", iter -> x);
    iter = iter -> next;
  }
}
