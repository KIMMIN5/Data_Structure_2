#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
} TreeNode; // 하나의 트리노드를 구조체로 표현

/* 링크드트리의 순회함수 */
void preorder(TreeNode *root) { // 전위순회
    if(root != NULL) {
        printf("%d ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }
}

void inorder(TreeNode *root) { // 중위순회
    if(root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}

void postorder(TreeNode *root) { // 후위순회
    if(root != NULL) {
        postorder(root -> left);
        postorder(root -> right);
        printf("%d ", root -> data);
    }
}

/* 배열트리의 순회함수 루트노드와의 관계 왼쪽노드 : 2 * i + 1, 오른쪽노드 : 2 * i + 2 */
void arrayPreorder(int tree[], int i, int n) {
    if (i <= n && tree[i] != 0) {
        printf("%d ", tree[i]);
        arrayPreorder(tree, 2 * i + 1, n);
        arrayPreorder(tree, 2 * i + 2, n);
    }
}

void arrayInorder(int tree[], int i, int n) {
    if (i <= n && tree[i] != 0) {
        arrayInorder(tree, 2 * i + 1, n);
        printf("%d ", tree[i]);
        arrayInorder(tree, 2 * i + 2, n);
    }
}

void arrayPostorder(int tree[], int i, int n) {
    if (i <= n && tree[i] != 0) {
        arrayPostorder(tree, 2 * i + 1, n);
        arrayPostorder(tree, 2 * i + 2, n);
        printf("%d ", tree[i]);
    }
}

//메인함수
int main() {

    int arrayTree[15] = {
        1, 2, 7, 3, 6, 8, 9, 4, 5, 0, 0, 0, 0, 10, 11
    }; // 배열로 이루어진 트리 생성

    // 노드를 조작하기 위한 포인터 생성
    TreeNode *rootNode = (TreeNode*)malloc(sizeof(TreeNode)); 
    TreeNode *node2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node3 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node4 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node5 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node6 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node7 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node8 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node9 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node10 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *node11 = (TreeNode*)malloc(sizeof(TreeNode));
    
    // 루트노드의 정보 입력
    rootNode -> data = 1;
    rootNode -> left = node2;
    rootNode -> right = node3;

    // 자식노드의 정보 입력
    node2 -> data = 2;
    node2 -> left = node4;
    node2 -> right = node5;

    node3 -> data = 7;
    node3 -> left = node6;
    node3 -> right = node7;

    node4 -> data = 3;
    node4 -> left = node8;
    node4 -> right = node9;

    node5 -> data = 6;
    node5 -> left = NULL;
    node5 -> right = NULL;

    node6 -> data = 8;
    node6 -> left = NULL;
    node6 -> right = NULL;

    node7 -> data = 9;
    node7 -> left = node10;
    node7 -> right = node11;

    node8 -> data = 4;
    node8 -> left = NULL;
    node8 -> right = NULL;

    node9 -> data = 5;
    node9 -> left = NULL;
    node9 -> right = NULL;

    node10 -> data = 10;
    node10 -> left = NULL;
    node10 -> right = NULL;

    node11 -> data = 11;
    node11 -> left = NULL;
    node11 -> right = NULL;


    printf("\n<LinkedTree>\n");
    printf("Preorder\n");
    preorder(rootNode);
    printf("\n");

    printf("Inorder\n");
    inorder(rootNode);
    printf("\n");

    printf("Postorder\n");
    postorder(rootNode);
    printf("\n");

    printf("\n<Array Tree>\n");
    printf("Preorder\n");
    arrayPreorder(arrayTree, 0, 14);
    printf("\n");

    printf("Inorder\n");
    arrayInorder(arrayTree, 0, 14);
    printf("\n");

    printf("Postorder\n");
    arrayPostorder(arrayTree, 0, 14);
    printf("\n");

    // 메모리 해제
    free(node11);
    free(node10);
    free(node9);
    free(node8);
    free(node7);
    free(node6);
    free(node5);
    free(node4);
    free(node3);
    free(node2);
    free(rootNode);

    return 0;
    
}