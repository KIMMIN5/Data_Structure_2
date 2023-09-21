#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// TreeNode의 구조체 정의
// is_thread는 right가 스레드인지 아닌지를 나타냄
typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
    bool is_thread;
} TreeNode;

// TreeNode 초기화
TreeNode n11 = {11, NULL, NULL, false};
TreeNode n10 = {10, NULL, NULL, false};
TreeNode n5 = {5, NULL, NULL, false};
TreeNode n4 = {4, NULL, NULL, false};
TreeNode n9 = {9, &n10, &n11, false};
TreeNode n8 = {8, NULL, NULL, false};
TreeNode n6 = {6, NULL ,NULL ,false};
TreeNode n3 = {3, &n4, &n5, false};
TreeNode n7 = {7, &n8, &n9, false};
TreeNode n2 = {2, &n3, &n6, false};
TreeNode root = {1, &n2, &n7, false};    

// 주어진 노드의 중위순회 후임을 찾는 함수
TreeNode *find_successor(TreeNode *p) {
    TreeNode *q = p -> right;

    if(q == NULL || p ->is_thread == true) {
        return q;
    }
    while(q -> left != NULL) {
        q = q-> left;
    }
    return q;
}

// 스레드이진트리의 중위순회 함수
void inorder_thread(TreeNode *root) {
    TreeNode *q;
    q = root;
    while(q -> left) q = q -> left; // 가장 왼쪽 노드로 이동
    do {
        printf("%d ", q -> data);
        q = find_successor(q); // 중위순회의 다음 노드로 이동
    } while(q);
}

// 주어진 자식 노드의 부모 노드를 찾는 함수
TreeNode *parent(TreeNode *child) {
    TreeNode *q = child -> right;
    TreeNode *qleft = q -> left;

    if(q == NULL) {
        return NULL;
    }
    else if(q -> left == child || q -> right == child) {
        return q;
    }
    else if(qleft -> left == child || qleft -> right == child) {
        return qleft;
    }
    else {
        fprintf(stderr, "Error\n");
        return NULL;
    }
}

int main() {

    // 스레드 설정
    n6.right = &root;
    n6.is_thread = true;

    n4.right = &n3;
    n4.is_thread = true;

    n5.right = &n2;
    n5.is_thread = true;

    n8.right = &n7;
    n8.is_thread = true;

    n10.right = &n9;
    n10.is_thread = true;


    printf("1. 중위순회결과 : ");
    inorder_thread(&root);
    printf("\n");

    printf("2. Node 4의 부모 : %d\n", parent(&n4) -> data);
    printf("3. Node 5의 부모 : %d\n", parent(&n5) -> data);
    printf("4. Node 6의 부모 : %d\n", parent(&n10) -> data);

    return 0;
}