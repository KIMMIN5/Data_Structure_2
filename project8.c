#include <stdio.h>
#include <stdlib.h>

#define MAX 200  // 힙의 최대 크기 정의

// 허프만 트리의 트리 노드 정의
typedef struct treeNode {
    int weight;   // 문자의 빈도 또는 가중치
    char ch;      // 이 노드에 대응하는 문자
    struct treeNode *left, *right; // 노드의 왼쪽과 오른쪽 자식
} TreeNode;

// 힙 연산을 위한 원소 구조체 정의
typedef struct Element {
    TreeNode *ptree; // 트리노드에 대한 포인터
    char ch;         // 트리노드의 문자
    int key;         // 힙 연산을 위한 키, 주로 트리노드의 가중치
} element;

// 힙 연산을 위한 힙 구조체 정의
typedef struct heapType {
    element heap[MAX];  // 힙의 원소를 저장할 배열
    int heapSize;       // 현재 힙의 크기
} HeapType;

// 오류 메시지를 출력하는 함수
void error(char *message) {
    fprintf(stderr, "%s", message);
}

// 새로운 힙을 생성하고 그 포인터를 반환하는 함수
HeapType *create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙의 크기를 0으로 초기화하는 함수
void init(HeapType *h) {
    h->heapSize = 0;
}

// 힙이 가득 찼는지 검사하는 함수
int is_full(HeapType *h) {
    return (h->heapSize == MAX - 1);
}

// 힙이 비어 있는지 검사하는 함수
int is_empty(HeapType *h) {
    return (h->heapSize == 0);
}

// 현재 힙의 상태를 출력하는 함수
void print_heap(HeapType *h) {
    for(int i=1; i<=h->heapSize; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 최소 힙에 원소를 삽입하는 함수
void insert_min_heap(HeapType *h, element item) {
    int i;
    i = ++h->heapSize;

    while(i != 1 && (item.key < h->heap[i/2].key)) {
        h->heap[i] = h->heap[i/2];
        i = i/2;
    }
    h->heap[i] = item;
    print_heap(h);
}

// 최소 힙에서 최소 원소를 삭제하고 반환하는 함수
element delete_min_heap(HeapType *h) {
    element item, temp;
    int parent = 1;
    int child = 2;
    item = h->heap[1];
    temp = h->heap[h->heapSize--];

    while(child <= h->heapSize) {
        if(child < h->heapSize && h->heap[child].key > h->heap[child+1].key) {
            child++;
        }

        if(temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    print_heap(h);
    return item;
}

// 새로운 트리 노드를 생성하는 함수
TreeNode *make_tree(TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 트리를 제거하는 함수
void destroy_tree(TreeNode *root) {
    if(!root) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 노드가 잎(leaf)인지 검사하는 함수
int is_leaf(TreeNode *root) {
    return !(root->left) && !(root->right);
}

// 허프만 코드를 출력하기 위한 배열을 출력하는 함수
void print_array(int codes[], int n) {
    for(int i=0; i<n; i++) {
        printf("%d ", codes[i]);
    }
    printf("\n");
}

// 허프만 코드를 출력하는 함수
void print_codes(TreeNode *root, int codes[], int top) {
    if(root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    if(root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    if(is_leaf(root)) {
        printf("%c : ", root->ch);
        print_array(codes, top);
    }
}

// 주요 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) {
    HeapType *h;
    TreeNode *node, *x;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    h = create();
    init(h);

    // 문자와 빈도로 힙을 초기화
    for(int i=0; i<n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(h, e);
    }

    // 허프만 트리를 만드는 과정
    for(int i=1; i<n; i++) {
        e1 = delete_min_heap(h);
        e2 = delete_min_heap(h);
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("/// %d + %d -> %d \n", e1.key, e2.key, e.key);
        insert_min_heap(h, e);
    }

    e = delete_min_heap(h);
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(h);
}

// 힙 정렬 함수
void heap_sort(int arr[], int n) {
    HeapType *h = create();
    init(h);

    for (int i = 0; i < n; i++) {
        element e;
        e.key = arr[i];
        insert_min_heap(h, e);
    }

    for (int i = 0; i < n; i++) {
        element e = delete_min_heap(h);
        arr[i] = e.key;
    }

    free(h);
}

int main() {
    char ch_list[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    int freq[] = { 45, 13, 12, 16, 9, 5 };
    int n = 6;

    printf("Huffman coding\n");
    huffman_tree(freq, ch_list, n);

    return 0;
}
