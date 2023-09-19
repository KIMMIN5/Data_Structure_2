#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    double data;
    struct treeNode *left, *right;
} TreeNode; // 트리노드를 구조체로 정의

#define SIZE 30 // 스택의 사이즈
TreeNode *stack[SIZE]; // 반복적 순회를 위한 스택 생성
int top = -1;

void push(TreeNode *p) { 
    if(top < SIZE - 1) {
        stack[++top] = p;
    }
}

TreeNode *pop() { 
    TreeNode *p = NULL;
    if(top >= 0) {
        p = stack[top--];
    }
    return p;
}

double evaluate(TreeNode *root) { // 수식계산함수
    double result = 0; // 결과를 저장 할 변수 초기화
    if(root == NULL) return 0; // 노드가 없으면 0을 리턴
    if(root -> left == NULL && root -> right == NULL) return root -> data; // 단말노드일 경우 그 노드의 데이터를 반환
    else { // 재귀적인 방법으로 계산
        double op1 = evaluate(root -> left); 
        double op2 = evaluate(root -> right);
        switch((int)(root -> data)) { // 비단말노드의 데이터는 연산자이므로 (int)형으로 타입캐스팅 후 케이스에 따라 처리
            case '+': result = op1 + op2; break;
            case '-': result = op1 - op2; break;
            case '*': result = op1 * op2; break;
            case '/': result = op1 / op2; break;
        }
        printf("%.2lf %c %.2lf = %.2lf\n", op1, (char)root->data, op2, result); // 출력
        
    }
    return result; 
}

int get_node_count(TreeNode *root) { // 노드의 수를 전위순회로 계산하는 함수
    if(!root) return -1; // 루트가 없으면 에러값 -1 반환
    int count = 0; // 노드의 수를 저장하기 위한 변수 초기화
    push(root); // 

    while(top != -1) {
        
        TreeNode *current = pop();
        count++; // 팝 할때마다 노드를 방문한 것으로 간주하여 카운트를 셈

        // 오른쪽 노드 먼저 스택에 추가하기 때문에, 오른쪽 노드를 나중에 처리하기 위해 먼저 푸쉬
        if(current -> right) {
            push(current -> right);
        }
        if(current -> left) {
            push(current -> left);
        }
    }

    return count;
}

int main() {

    // 노드의 생성, 할당, 값입력
    TreeNode *n19 = (TreeNode*)malloc(sizeof(TreeNode));
    n19 -> data = 5;
    n19 -> left = NULL;
    n19 -> right = NULL;

    TreeNode *n18 = (TreeNode*)malloc(sizeof(TreeNode));
    n18 -> data = 4;
    n18 -> left = NULL;
    n18 -> right = NULL;

    TreeNode *n17 = (TreeNode*)malloc(sizeof(TreeNode));
    n17 -> data = 3;
    n17 -> left = NULL;
    n17 -> right = NULL;

    TreeNode *n16 = (TreeNode*)malloc(sizeof(TreeNode));
    n16 -> data = 2;
    n16 -> left = NULL;
    n16 -> right = NULL;

    TreeNode *n11 = (TreeNode*)malloc(sizeof(TreeNode));
    n11 -> data = 7;
    n11 -> left = NULL;
    n11 -> right = NULL;

    TreeNode *n10 = (TreeNode*)malloc(sizeof(TreeNode));
    n10 -> data = 6;
    n10 -> left = NULL;
    n10 -> right = NULL;

    TreeNode *n9 = (TreeNode*)malloc(sizeof(TreeNode));
    n9 -> data = '*';
    n9 -> left = n18;
    n9 -> right = n19;

    TreeNode *n8 = (TreeNode*)malloc(sizeof(TreeNode));
    n8 -> data = '+';
    n8 -> left = n16;
    n8 -> right = n17;

    TreeNode *n5 = (TreeNode*)malloc(sizeof(TreeNode));
    n5 -> data = '/';
    n5 -> left = n10;
    n5 -> right = n11;

    TreeNode *n4 = (TreeNode*)malloc(sizeof(TreeNode));
    n4 -> data = '+';
    n4 -> left = n8;
    n4 -> right = n9;

    TreeNode *n3 = (TreeNode*)malloc(sizeof(TreeNode));
    n3 -> data = 9;
    n3 -> left = NULL;
    n3 -> right = NULL;

    TreeNode *n2 = (TreeNode*)malloc(sizeof(TreeNode));
    n2 -> data = '-';
    n2 -> left = n4;
    n2 -> right = n5;

    TreeNode *n1 = (TreeNode*)malloc(sizeof(TreeNode));
    n1 -> data = '+';
    n1 -> left = n2;
    n1 -> right = n3;
    
    evaluate(n1); // 수식트리의 연산결과
    printf("총 노드의 수는 %d개 입니다.\n", get_node_count(n1)); // 총 노드의 수를 출력

    //메모리 반환
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n8);
    free(n9);
    free(n10);
    free(n11);
    free(n16);
    free(n17);
    free(n18);
    free(n19);

    return 0;
}