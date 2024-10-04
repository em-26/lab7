#include <stdio.h>
#include <stdlib.h>

// Definition of a BST node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Helper function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Recursive function to insert a new key into the BST
struct Node* insert(struct Node* node, int key) {
    // If the tree is empty, return a new node
    if (node == NULL) return newNode(key);

    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Return the unchanged node pointer
    return node;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key, search in the right subtree
    if (key > root->key)
        return search(root->right, key);

    // Key is smaller than root's key, search in the left subtree
    return search(root->left, key);
}

// Function to find the minimum value node in a BST
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Loop to find the leftmost leaf (smallest value)
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    // Recur down the tree to find the node to delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // Node to be deleted is found
    else {
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children, get the inorder successor
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}


int main() {
    struct Node* root = NULL;

    // Insert nodes into the BST
    root = newNode(50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the original BST: ");
    inorder(root);
    printf("\n");

    // Search for a node
    int key_to_search = 40;
    struct Node* search_result = search(root, key_to_search);
    if (search_result != NULL)
        printf("Node %d found in the BST.\n", key_to_search);
    else
        printf("Node %d not found in the BST.\n", key_to_search);

    // Delete a node
    int key_to_delete = 50;
    root = deleteNode(root, key_to_delete);

    printf("Inorder traversal after deleting %d: ", key_to_delete);
    inorder(root);
    printf("\n");

    return 0;
}
