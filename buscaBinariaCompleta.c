#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
 int key;
 struct Node* left;
 struct Node* right;
 struct Node* parent;

};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

struct Node* minimum(struct Node* x){
     if(x == NULL)
        return NULL;
     struct Node* current = x;
     while(current->left != NULL)
        current = current->left;
    return current;

}

struct Node* maximum(struct Node* x){
     if(x == NULL)
        return NULL;
     struct Node* current = x;
     while(current->right != NULL)
        current = current->right;
     return current;
}

struct Node* Sucessor(struct Node* x){
   if(x-> right != NULL)
    return minimum(x->right);
   struct Node* y = x->parent;

    while(y != NULL && x == y->right){
    x = y;
    y = y->parent;
    }
    return y;
}

struct Node* Search(struct Node* x, int key) {
    if (x == NULL || x->key == key)
        return x;
    if (key < x->key)
        return Search(x->left, key);
    else
        return Search(x->right, key);
}


struct Node* Insert(struct Node* root, int key){
      struct Node* newNode = createNode(key);
      struct Node* y = NULL;
      struct Node* x = root;
      while(x != NULL){
        y = x;
        if(key < x->key)
            x = x->left;
        else
            x = x->right;
      }
      newNode->parent = y;
      if (y == NULL) {
        root = newNode;  // A árvore estava vazia
    } else if (key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    return root;
};
struct Node* delecao(struct Node* root, int key){
    if(root == NULL)
        return root;
    if(key < root->key){
    root->left = delecao(root->left, key);
}   else if(key > root->key){
    root->right = delecao(root->right, key);
}   else{
        //caso o nó destinado a ser excluido não tenha filho o nó pai aponta pra NULL.
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        //caso o nó destinado tenha um filho o nó pai agora aponta para o no filho do excluido.
        }if(root->left == NULL ){
            struct Node* temp = root->right;
            free(root);
            return temp;

        }if(root->right == NULL){
            struct Node* temp = root->left;
            free(root);
            return temp;
        //caso o nó destinado tenha dois filhos o nó destinado agora a ponta ao seu sucessor ou seja um numero mais proximo maior que ele.
        }struct Node* temp = minimum(root->right);
         root->key = temp->key;
         root->right = delecao(root->right, temp->key);
}
return root;

};

int main()
{
    struct Node* root = createNode(11);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(9);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(17);
    root->right->right = createNode(20);


    // Teste da função de busca
    int key = 20;
    struct Node* result = Search(root, key);
    if (result != NULL)
        printf("Chave %d encontrada no noo com endereco %p\n", key, (void*)result);
    else
        printf("Chave %d nao encontrada\n", key);

    // Teste das funções minima e maxima
    struct Node* minNode = minimum(root);
    struct Node* maxNode = maximum(root);

    if (minNode != NULL)
        printf("A menor chave na arvore e %d\n", minNode->key);
    else
        printf("A arvore está vazia.\n");

    if (maxNode != NULL)
        printf("A maior chave na arvore e %d\n", maxNode->key);
    else
        printf("A arvore está vazia.\n");

    return 0;
}
