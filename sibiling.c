#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* right;
    struct TreeNode* left;

} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* new_node = (TreeNode*) malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        printf("The memory allocation is failed");
        exit(-1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void inOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void preOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data); 
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

TreeNode* findMin(TreeNode* node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) return root; 

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            
            TreeNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

int get_node_height(TreeNode* node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int get_node_depth(TreeNode* root, int val) {
    if (root == NULL) {
        return -1;
    }
    if (root->data == val) {
        return 0;
    }
    if (val < root->data) {
        return 1 + get_node_depth(root->left, val);
    } else {
        return 1 + get_node_depth(root->right, val);
    }
}

int get_node_level(TreeNode* root, int val) {
    return 1 + get_node_depth(root, val);
}

TreeNode* get_node_sibling(TreeNode* root, int val) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL; 
    }

    if ((root->left != NULL && root->left->data == val) || (root->right != NULL && root->right->data == val)) {
        return (root->left != NULL && root->left->data == val) ? root->right : root->left;
    }

    TreeNode* leftSibling = get_node_sibling(root->left, val);
    if (leftSibling != NULL) {
        return leftSibling;
    }

    TreeNode* rightSibling = get_node_sibling(root->right, val);
    if (rightSibling != NULL) {
        return rightSibling;
    }

    return NULL;
}

int main() {
    TreeNode* p1 = createNode(20);
    insertNode(p1, 13);
    insertNode(p1, 17);
    insertNode(p1, 19);
    insertNode(p1, 1);
    insertNode(p1, 34);
    insertNode(p1, 15);
    insertNode(p1, 5);

    printf("In-order traversal: ");
    inOrderTraversal(p1);
    printf("\n");
    
    printf("Pre-order traversal: ");
    preOrderTraversal(p1);
    printf("\n");
    
    printf("Post-order traversal: ");
    postOrderTraversal(p1);
    printf("\n");
    
    deleteNode(p1, 19);
    printf("In-order traversal after deletion: ");
    inOrderTraversal(p1);
    printf("\n");

    
    TreeNode* sibling = get_node_sibling(p1, 1);
    if (sibling != NULL) {
        printf("Sibling of 34 is: %d\n", sibling->data);
    } else {
        printf("Node with value 34 has no sibling.\n");
    }

    
    return 0;
}
