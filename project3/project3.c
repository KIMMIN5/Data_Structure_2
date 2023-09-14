#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
} TreeNode; // 하나의 트리노드를 구조체로 표현

#define SIZE 20 // 스택의 사이즈를 결정
int top = -1; 
TreeNode *stack[SIZE]; // 트리노드를 저장할 스택 생성

void push(TreeNode *p) { // 스택에 노드를 푸쉬
    if(top < SIZE - 1) {
        stack[++top] = p;
    }
}

TreeNode *pop() { // 스택에 노드를 팝
    TreeNode *p = NULL;
    if(top >= 0) {
        p = stack[top--];
    }
    return p;
}

void inorder_iter(TreeNode *root) { // 반복적인 중위순회
    while(1) { // 무한루프
        for(; root; root = root -> left) { // 노드의 왼쪽 자식들을 스택에 추가
            push(root);
        }
        root = pop();
        if(!root) break; // 루트가 없으면 중단
        printf("%d ", root -> data);
        root = root -> right;    
    }
}

void preorder_iter(TreeNode *root) { // 반복적인 전위순회
    if(!root) return;
    push(root);
    
    while(top != -1) {
        TreeNode *current = pop();
        printf("%d ", current->data);
        
        // 오른쪽 노드 먼저 스택에 추가하기 때문에, 오른쪽 노드를 나중에 처리하기 위해 먼저 푸쉬
        if(current->right)
            push(current->right);
        if(current->left)
            push(current->left);
    }
}

void postorder_iter(TreeNode *root) {
    TreeNode *stack2[SIZE];
    int top2 = -1;
    
    if(!root) return;
    push(root);

    while(top != -1) {
        TreeNode *current = pop();
        stack2[++top2] = current;  // 후위 순회 결과를 임시로 저장할 두번 째 스택에 추가

        // 후위 순회는 왼쪽, 오른쪽 순으로 추가되기 때문에 반대순서대로 푸쉬
        if(current->left)
            push(current->left);
        if(current->right)
            push(current->right);
    }
    
    while(top2 != -1) {
        TreeNode *current = stack2[top2--];  // 두 번째 스택으로부터 노드를 팝하여 출력
        printf("%d ", current->data);
    }
}

//메인함수
int main() {

    // 노드를 조작하기 위한 포인터 생성 및 할당
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


    // 결과 출력
    printf("\n<LinkedTree>\n");
    printf("Preorder\n");
    preorder_iter(rootNode);
    printf("\n");

    printf("Inorder\n");
    inorder_iter(rootNode);
    printf("\n");

    printf("Postorder\n");
    postorder_iter(rootNode);
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