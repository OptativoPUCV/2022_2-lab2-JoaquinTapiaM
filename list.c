
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista = (List*)calloc(1,sizeof(List));
  return lista;
}

void * firstList(List * list) {
  if (list->head != NULL){
    list->current = list->head;
    return list->head->data;
  }
  return NULL;
}

void * nextList(List * list) {
  if(list->current !=NULL){
    if(list->current->next != NULL){
      list->current = list->current->next;
      return list->current->data;
    }
  }
  return NULL;
}

void * lastList(List * list) {
  if (list->tail != NULL){
    list->current = list->tail;
    return list->tail->data;
  }
  return NULL;
}

void * prevList(List * list) {
  if(list->current !=NULL){
    if(list->current->prev != NULL){
      list->current = list->current->prev;
      return list->current->data;
    }
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  Node * newNode = createNode(data);
  list->current = newNode;
  if(list->head == NULL ){
    list->head = list->current;
    list->tail = list->current;
  }
  else{
    list->current->next = list->head;
    newNode->prev = NULL;
    list->head = list->current;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * newNode = createNode(data);
  if(list->current == list->tail){
    list->current->next = newNode;
    newNode->prev = list->current;
    list->current = newNode;
    list->tail = list->current;
  }
  else{
    newNode->next = list->current->next;
    list->current->next->prev = newNode;
    newNode->prev = list->current;
    list->current->next = newNode;
    list->current = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list){
  if(list->head == NULL){
    return NULL;
  }
  void * datoEliminado = list->current->data;
  if(list->current==list->tail){
    list->current = list->current->prev;
    list->current->next = NULL;
    list->tail = list->current;
  }
  if(list->current==list->head){
    list->current = list->current->next;
    list->current->prev = NULL;
    list->head = list->current;
  }
  else{
  Node * aux = createNode(NULL);
  aux = list->current->prev;
    list->current->next->prev = list->current->prev;
    aux->next = list->current->next;
    list->current = list->current->next;
  }
    return datoEliminado;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}