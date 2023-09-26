#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
} TreeNode;

// TreeNode 초기화
TreeNode n14 = {64, NULL, NULL};
TreeNode n13 = {62, NULL, NULL};
TreeNode n12 = {42, NULL, NULL};
TreeNode n11 = {70, NULL, NULL};
TreeNode n10 = {63, &n13, &n14};
TreeNode n9 = {55, NULL, NULL};
TreeNode n8 = {46, &n12, NULL};
TreeNode n7 = {25, NULL, NULL};
TreeNode n6 = {65, &n10, &n11};
TreeNode n5 = {53, &n8 ,&n9};
TreeNode n4 = {16, &n7, &n8};
TreeNode n3 = {74, &n6, NULL};
TreeNode n2 = {41, &n4, &n5};
TreeNode root = {60, &n2, &n3};   

TreeNode *search_iter(TreeNode *root, int key, int *visited) {
    *visited = 0;
    while(root != NULL) {
        (*visited)++;
        if(key == root -> data) {
            return root;
        }
        else if(key < root -> data) {
            root = root -> left;
        }
        else {
            root = root -> right;
        }
    }
    fprintf(stderr, "Error\n");
}

TreeNode *search_rec(TreeNode *root, int key, int *visited) {
    *visited = 0;
    if(root == NULL) {
        return NULL;
    }
    (*visited)++;
    if(key == root -> data) {
        return root;
    }
    else if(key < root -> data) {
        return search_rec(root -> left, key, visited);
    }
    else {
       return search_rec(root -> right, key, visited);
    }
}

TreeNode *insert_rec(TreeNode *root, int key, int *visited) {
    (*visited)++;
    if(root == NULL) {
        TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode -> data = key;
        newNode -> left = newNode -> right = NULL;
        return newNode;
    }
    if(key < root -> data) {
        root -> left = insert_rec(root -> left, key, visited);
    }
    else if(key > root -> data) {
        root -> right = insert_rec(root -> right, key, visited);
    }
    return root;
}

TreeNode *delete_node_rec(TreeNode *root, int key, int *visited) { // 탐색시간 트리의 높이만큼 걸림
    if(root == NULL) return NULL;
    (*visited)++;
    if(key < root -> data) {
        root -> left = delete_node_rec(root -> left, key, visited);
    }
    else if(key > root -> data) {
        root -> right = delete_node_rec(root -> right, key, visited);
    }
    else {
        if(root -> left == NULL) {
            TreeNode *temp = root -> right;
            free(root);
            return temp;
        }
        else if(root -> right == NULL) {
            TreeNode *temp = root -> left;
            free(root);
            return temp;
        }
        else { // 자식을 둘 다 가지고 있는 경우
            TreeNode *temp = min_value_node(root -> right); // 오른쪽 서브트리에서 가장 작은 값을 찾음
            root -> data = temp -> data; // 부모노드의 값을 찾아온 값으로 대체
            root -> right = delete_node_rec(root -> right, temp -> data); // 노드삭제
        }
    }
    return root;
}

TreeNode * min_value_node(TreeNode * node) {
    TreeNode * current = node; 
    
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL) {   
        current = current->left;
    }
    return current; 
} 

void inorder(TreeNode *root) { // 중위순회
    if(root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}

int main() {
    int menu;
    int visited;

    while(1) {
        printf("\n=====MENU=====\n");
        printf("1 : 검색\n");
        printf("2 : 노드추가\n");
        printf("3 : 노드삭제\n");
        printf("4 : 중위순회\n");
        printf("5 : 노드추가(반복)\n");
        printf("6 : 노드삭제(반복)\n");
        printf("0 : 종료\n");

        printf("메뉴입력 : ");
        scanf("%d", menu);

        if(menu == 1) {
            int key;
            printf("검색할 값 : ");
            scanf("%d", &key);
            TreeNode *result = search_iter(&root, key, &visited);
            if(result) {
                printf("검색성공 : %d (방문한 노드의 수 : %d)\n", result -> data, visited);
            }
            else {
                printf("검색실패 : (방문한 노드의 수 : %d)\n", visited);
            }
            inorder(&root);
            printf("\n");
        }
        else if(menu == 2) {
            int key;
            printf("삽입할 값 : ");
            scanf("%d", &key);
            root = *insert_rec(&root, key, &visited);
            printf("노드 추가 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(&root);
            printf("\n");
        }
        else if(menu == 3) {
            int key;
            printf("삭제할 값 : ");
            scanf("%d", &key);
            root = delete_node_rec(&root, key, &visited);
            printf("노드 삭제 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(&root);
            printf("\n");
        }
        else if(menu == 4) {
            printf("중위순회결과 : ");
            inorder(&root);
            printf("\n");
        }
        else if(menu == 5) {
            int key;
            printf("삽입할 값 : ");
            scanf("%d", &key);
            
        }
        else if(menu == 6) {
            int key;
            printf("삭제할 값 : ");
            scanf("%d", &key);
            //delete_node_iter(root, key);
        }
        else if(menu == 7) {
            exit(-1);
        }
    }
    return 0;
}