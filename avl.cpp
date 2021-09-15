// Nome: Francisco Jerônimo da Silva Júnior
// Matrícula: 433399

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef struct No *AVL;

struct No{
    int value;
    int height;
    struct No *left;
    struct No *right;
};

AVL *root;

AVL *criar_arvore(){
    AVL *avl = (AVL*) malloc(sizeof(AVL));
    if(avl != NULL)
        *avl = NULL;
    return avl;
}

int height_no(struct No* node){
    if(node == NULL)
        return -1;
    else
        return node->height;
}

int balanco(struct No* node){
    return labs(height_no(node->left) - height_no(node->right));
}

void rotationll(AVL *root){
    struct No *node;
    node = (*root)->left;
    (*root)->left = node->right;
    node->right = *root;
    (*root)->height = max(height_no((*root)->left), height_no((*root)->right)) +1;

    node->height = max(height_no(node->left), height_no(node->right));
    (*root) = node;
}

void rotationrr(AVL *root){
    struct No *node;
    node = (*root)->right;
    (*root)->right = node->left;
    node->left = (*root);

    (*root)->height = max(height_no((*root)->left), height_no((*root)->right)) + 1;
    node->height = max(height_no(node->left), height_no(node->right)) + 1;

    (*root) = node;
}

bool empty(AVL *root){
    return root == NULL or *root == NULL;
}

void rotationlr(AVL *root){
    rotationrr(&(*root)->left);
    rotationll(root);
}

void rotationrl(AVL *root){
    rotationll(&(*root)->right);
    rotationrr(root);
}

bool search(AVL *root, int x){
    if(!empty(root)){
        if(x == (*root)->value)
            return true;
        else if(x > (*root)->value)
            root = &(*root)->right;
        else
            root = &(*root)->left;
    }
    return false;
}

bool inserir(AVL *root, int x){
    bool aux;

    if(search(root, x))
        return false;

    if(empty(root)){
        struct No* node = (struct No*) malloc(sizeof(struct No));

        node->height = 0;
        node->left = NULL;
        node->right = NULL;
        node->value = x;
        *root = node;
        return true;
    }
    struct No *atual = (*root);
    if(x < atual->value){
        if((aux = inserir(&(atual)->left, x)) == true){
            if(balanco(atual) >= 2){
                if(x < (*root)->left->value)
                    rotationll(root);
                else
                    rotationlr(root);
            }
        }
    }else if(x > atual->value){
        if((aux = inserir(&(atual)->right, x)) == true){
            if(balanco(atual) >= 2){
                if((*root)->right->value < x)
                    rotationrr(root);
                else
                    rotationrl(root);
            }
        }
    }else{
        return false;
    }

    atual->height = max(height_no(atual->left), height_no(atual->right)) + 1;
    return aux;
}

int minimo(AVL *root){
    if(empty(root) or (*root)->left == NULL)
        return (*root)->value;
    return minimo(&(*root)->left);
}

int maximo(AVL *root){
    if(empty(root) or (*root)->right == NULL)
        return (*root)->value;
    return maximo(&(*root)->right);
}

void pre_ordem(AVL *root){
    if(!empty(root)){
        cout << (*root)->value << " ";
        pre_ordem(&(*root)->left);
        pre_ordem(&(*root)->right);
    }
}

void in_ordem(AVL *root){
    if(!empty(root)){
        in_ordem(&(*root)->left);
        cout << (*root)->value << " ";
        in_ordem(&(*root)->right);
    }
}

void pos_ordem(AVL *root){
    if(!empty(root)){
        pos_ordem(&(*root)->left);
        pos_ordem(&(*root)->right);
        cout << (*root)->value << " ";
    }
}

int leaf(AVL *root){
    if(empty(root))
        return 0;
    if((*root)->left == NULL && (*root)->right == NULL)
        return leaf(&(*root)->left) + leaf(&(*root)->right) + 1;
    else
        return leaf(&(*root)->left) + leaf(&(*root)->right);
}

int avl_height(AVL *root){
    int esq = 0, dir = 0;
    if(empty(root))
        return 0;
    esq = avl_height(&(*root)->left);
    dir = avl_height(&(*root)->right);
    if(esq > dir)
        return esq +1;
    else
        return dir + 1;
}

int main(){
    AVL *tree;
    
    tree = criar_arvore();
    while(true){
        int op;
        cout << "----------------------------"<< endl;
        cout << "Implementação da Árvore AVL"<< endl;
        cout << "----------------------------"<< endl;
        cout << "1. Inserir elemento na árvore" << endl;
        cout << "2. Percurso em pre-ordem" << endl;
        cout<<"3. Percurso em in-ordem" << endl;
        cout << "4. Percurso em pós-ordem" << endl;
        cout << "5. Altura da árvore" << endl;
        cout << "6. Número de folhas da árvore" << endl;
        cout << "7. Valor máximo e mínimo da árvore" << endl;
        cout << "8. Sair"<< endl;
        cout << "Entre sua escolha: ";
        cin >> op;
        system("clear");
        if(op == 1){
            system("clear");
            int value;
            cout << "Digite o valor a ser inserido: ";
            cin >> value;
            if(inserir(tree, value))
                cout << "Valor inserido\n" << endl;
            else
                cout << "Valor já existe\n" <<endl;
        }else if(op == 2){
            cout << "Pre-ordem: ";
            pre_ordem(tree);
            cout << endl << endl;
        }else if(op == 3){
            cout << "In-ordem: ";
            in_ordem(tree);
            cout << endl;
        }else if(op == 4){
            cout << "Pós-ordem: ";
            pos_ordem(tree);
            cout << endl << endl;
        }else if(op == 5){
            cout << "Altura: " << avl_height(tree) << endl << endl;
        }else if(op == 6){
            cout << "Folhas: " << leaf(tree) << endl << endl;
        }else if(op == 7){
            if(empty(tree))
                cout << "Árvore vazia" << endl << endl;
            else{
                cout << "Valor Máximo: " << maximo(tree) << endl << endl;
                cout << "Valor Mínimo: " << minimo(tree) << endl << endl;
            }
        }else if(op == 8){
            cout << "Até logo" << endl;
            break;
        }
    }
    return 0;
}
