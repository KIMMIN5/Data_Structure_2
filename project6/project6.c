#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left, *right;
} TreeNode; 

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
    return NULL;
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

TreeNode *insert_iter(TreeNode *root, int key, int *visited) {
    *visited = 0;
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode -> data = key;
    newNode -> left = newNode -> right = NULL;

    if(root == NULL) return newNode;

    TreeNode *current = root;
    TreeNode *parent = NULL;
    while(current != NULL) {
        (*visited)++;
        parent = current;
        if(key < current -> data) current = current -> left;
        else if(key > current -> data) current = current -> right;
        else return root; // 중복된 key는 삽입하지 않음
    }

    if(key < parent -> data) parent -> left = newNode;
    else parent -> right = newNode;

    return root;
}

TreeNode *min_value_node(TreeNode *node, int *visited) {
    TreeNode * current = node; 
    
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL) {  
        (*visited)++; 
        current = current->left;
    }
    return current; 
} 

TreeNode *delete_node_iter(TreeNode *root, int key, int *visited) {
    (*visited) = 0;
    if(root == NULL) return NULL;

    TreeNode *current = root;
    TreeNode *parent = NULL;

    while(current != NULL && current -> data != key) {
        (*visited)++;
        parent = current;
        if(key < current -> data) current = current -> left;
        else current = current -> right;
    }

    if(current == NULL) return root; // 삭제할 노드가 존재하지 않음

    // 노드에 자식이 없는 경우
    if(current -> left == NULL && current -> right == NULL) {
        if(parent == NULL) root = NULL; //current가 NULL인 경우
        else if(parent -> left == current) parent -> left = NULL;
        else parent -> right = NULL;
        
        free(current);
    }

    // 노드에 한 개의 자식이 있는 경우
    else if(current -> left == NULL || current -> right == NULL) {
        TreeNode *child = (current -> left != NULL) ? current -> left : current -> right;
        if(current != root) {
            if(parent -> left == current) parent -> left = child;
            else parent -> right = child;
        } else root = child;

        free(current);
    }

    // 노드에 두 개의 자식이 있는 경우
    else {
        TreeNode *parentOfSuccessor = current;
        TreeNode *successor = current -> right;

        while(successor -> left != NULL) {
            (*visited)++;
            parentOfSuccessor = successor;
            successor = successor -> left;
        }

        current -> data = successor -> data;
        if(parentOfSuccessor -> left == successor) parentOfSuccessor -> left = successor -> right;
        else parentOfSuccessor -> right = successor -> right;

        free(successor);
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
            TreeNode *temp = min_value_node(root -> right, visited); // 오른쪽 서브트리에서 가장 작은 값을 찾음
            root -> data = temp -> data; // 부모노드의 값을 찾아온 값으로 대체
            root -> right = delete_node_rec(root -> right, temp -> data, visited); // 노드삭제
        }
    }
    return root;
}

void inorder(TreeNode *root, int *visited) { // 중위순회
    if(root != NULL) {
        inorder(root -> left, visited);
        printf("%d ", root -> data);
        (*visited)++;
        inorder(root -> right, visited);
    }
}

int main() {    
    int menu;
    int visited;

    TreeNode *n1 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n2 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n3 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n4 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n5 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n6 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n7 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n8 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n9 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n10 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n11 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n12 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n13 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *n14 = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *root = n1;

    n1 -> data = 60;
    n1 -> left = n2;
    n1 -> right = n3;

    n2 -> data = 41;
    n2 -> left = n4;
    n2 -> right = n5;

    n3 -> data = 74;
    n3 -> left = n6;
    n3 -> right = NULL;

    n4 -> data = 16;
    n4 -> left = NULL;
    n4 -> right = n7;

    n5 -> data = 53;
    n5 -> left = n8;
    n5 -> right = n9;

    n6 -> data = 65;
    n6 -> left = n10;
    n6 -> right = n11;

    n7 -> data = 25;
    n7 -> left = NULL;
    n7 -> right = NULL;

    n8 -> data = 46;
    n8 -> left = n12;
    n8 -> right = NULL;

    n9 -> data = 55;
    n9 -> left = NULL;
    n9 -> right = NULL;


    n10 -> data = 63;
    n10 -> left = n13;
    n10 -> right = n14;

    n11 -> data = 70;
    n11 -> left = NULL;
    n11 -> right = NULL;

    n12 -> data = 42;
    n12 -> left = NULL;
    n12 -> right = NULL;

    n13 -> data = 62;
    n13 -> left = NULL;
    n13 -> right = NULL;

    n14 -> data = 64;
    n14 -> left = NULL;
    n14 -> right = NULL;

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
        scanf("%d", &menu);

        if(menu == 1) {
            int key;
            visited = 0;
            printf("검색할 값 : ");
            scanf("%d", &key);
            TreeNode *result = search_iter(root, key, &visited);
            if(result) {
                printf("검색성공 : %d (방문한 노드의 수 : %d)\n", result -> data, visited);
            }
            else {
                printf("검색실패 : (방문한 노드의 수 : %d)\n", visited);
            }
            inorder(root, &visited);
            printf("\n");
        }
        else if(menu == 2) {
            int key;
            visited = 0;
            printf("삽입할 값 : ");
            scanf("%d", &key);
            root = insert_rec(root, key, &visited);
            printf("노드 추가 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(root, &visited);
            printf("\n");
        }
        else if(menu == 3) {
            int key;
            visited = 0;
            printf("삭제할 값 : ");
            scanf("%d", &key);
            root = delete_node_rec(root, key, &visited);
            printf("노드 삭제 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(root, &visited);
            printf("\n");
        }
        else if(menu == 4) {
            visited = 0;
            printf("중위순회결과 : ");
            inorder(root, &visited);
            printf("\n");
            printf("방문한 노드의 수 : %d\n", visited);
        }
        else if(menu == 5) {
            visited = 0;
            int key;
            printf("삽입할 값 : ");
            scanf("%d", &key);
            root = insert_iter(root, key, &visited);
            printf("노드 추가 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(root, &visited);
            printf("\n");
        }
        else if(menu == 6) {
            visited = 0;
            int key;
            printf("삭제할 값 : ");
            scanf("%d", &key);
            root = delete_node_iter(root, key, &visited);
            printf("노드 삭제 완료 (방문한 노드의 수 : %d)\n", visited);
            inorder(root, &visited);
            printf("\n");
        }
        else if(menu == 0) {
            exit(0);

            
        }
    }
    return 0;
}