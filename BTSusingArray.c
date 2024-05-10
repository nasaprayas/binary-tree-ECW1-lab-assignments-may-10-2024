#include <stdio.h>
#define SIZE 100

int tree[SIZE];

void initializeTree() {
    for (int i = 0; i < SIZE; i++) {
        tree[i] = -1; 
    }
}

void insert(int value) {
    int index = 0;
    
    while (tree[index] != -1) {
        if (value < tree[index]) {
            index = 2 * index + 1; 
        } else {
            index = 2 * index + 2; 
        }
    }
    
    tree[index] = value;
}

void inorderTraversal(int index) {
    if (index < SIZE && tree[index] != -1) {
        inorderTraversal(2 * index + 1); 
        printf("%d ", tree[index]);
        inorderTraversal(2 * index + 2); 
    }
}

int main() {
    initializeTree();
    insert(5);
    insert(3);
    insert(8);
    insert(1);
    insert(4);
    insert(7);
    insert(9);
    
    printf("Inorder traversal: ");
    inorderTraversal(0);
    
    return 0;
}
