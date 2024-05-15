#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int i, j , k;
   int row_check[9], col_check[9], box_check[9];
   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++){
         if (n->sudo[i][j] != 0){
            row_check[n->sudo[i][j] - 1] = 0;
            col_check[n->sudo[j][i] - 1] = 0;
         }
      }
   }

   for (i = 0; i < 9; i++){
      for (j = 0; j < 9; j++){
         if (n->sudo[i][j] != 0){
            if (row_check[n->sudo[i][j] - 1] == 1) return 0;
            row_check[n->sudo[i][j] - 1] = 1;
         }
         if (n->sudo[j][i] != 0){
            if (col_check[n->sudo[j][i] - 1] == 1) return 0;
            col_check[n->sudo[j][i] - 1] = 1;
         }
      }
      for (k = 0; k < 9; k++) {
         row_check[k] = 0;
         col_check[k] = 0;
      }
   }

   for (i = 0; i < 9; i += 3) {
      for (j = 0; j < 9; j += 3) {
         for (k = 0; k < 9; k++) {
            box_check[k] = 0;
         }
            for (k = 0; k < 9; k++) {
               int x = i + k / 3;
               int y = j + k % 3;
               if (n->sudo[x][y] != 0) {
                  if (box_check[n->sudo[x][y] - 1] == 1) return 0;
                  box_check[n->sudo[x][y] - 1] = 1;
               }
            }
      }
   }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
   int i, j, k;

   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) {
            for (k = 1; k <= 9; k++) {
               Node *new_node = copy(n);
               new_node->sudo[i][j] = k;
               if (is_valid(new_node)) {
                  pushBack(list, new_node);
               }
               else {
                  free(new_node);
               }
            }
            return list;
         }
      }
   }
    
    return list;
}


int is_final(Node* n){
   int i, j;
   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/