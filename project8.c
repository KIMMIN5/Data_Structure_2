#include <stdio.h>
#include <stdlib.h>

#define MAX 200

typedef struct treeNode {
    int weight;
    char ch;
    struct treeNode *left, *right;
} TreeNode;

typedef struct Element {
    TreeNode *ptree;
    char ch;
    int key;
} element;

typedef struct heapType {
    element heap[MAX];
    int heapSize;
} HeapType;

void error(char *message) {
    fprintf(stderr, "%s", message);
}

HeapType *create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType *h) {
    h->heapSize = 0;
}

int is_full(HeapType *h) {
    return (h->heapSize == MAX - 1);
}

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

TreeNode *make_tree(TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

void destroy_tree(TreeNode *root) {
    if(!root) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

int is_leaf(TreeNode *root) {
    return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
    for(int i=0; i<n; i++) {
        printf("%d ", codes[i]);
    }
    printf("\n");
}

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

void huffman_tree(int freq[], char ch_list[], int n) {
    HeapType *h;
    TreeNode *node, *x;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    h = create();
    init(h);

    for(int i=0; i<n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(h, e);
    }

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
    int arr[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86};
    int n = sizeof(arr) / sizeof(int);
    heap_sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char ch_list[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int freq[] = {10, 15, 12, 3, 4, 13, 1};
    huffman_tree(freq, ch_list, 7);

    return 0;
}
