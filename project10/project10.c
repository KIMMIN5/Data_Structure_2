#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTICES 30

int parent[MAX_VERTICES];

// 배열 초기화
void set_init(int n) {
    for(int i=0; i<n; i++) {
        parent[i] = -1;
    }
}

// 집합의 대표를 찾는 함수
int set_find(int current) {
    if (parent[current] == -1) return current;
    while (parent[current] != -1) {
        current = parent[current];
    }
    return current;
}

// 두 수의 대표가 같지 않으면 합집합 실행
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if(root1 != root2) {
        parent[root2] = root1;
    }
}




// 간선 구조체 정의
typedef struct edge {
    int start;
    int end;
    int weight;
} Edge;

// 그래프 구조체 정의
typedef struct graphType {
    int n; // 노드의 개수
    int num_edges; // 간선의 개수
    Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화
void init_graph(GraphType *g, int n) {
    g->n = n;
    g->num_edges = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INFINITY;
    }
}

// 간선추가
void insert_edge(GraphType *g, int start, int end, int weight) {
    int index = g->num_edges++;
    g->edges[index].start = start;
    g->edges[index].end = end;
    g->edges[index].weight = weight;
}

// QSort에 사용될 비교함수
int compare(const void *a, const void *b) {
    Edge *x = (Edge*)a;
    Edge *y = (Edge*)b;
    return (x->weight - y->weight);
}

// Kruskal MST 알고리즘
void kruskal_qsort(GraphType *g) {
    int edge_accepted = 0;
    int uset, vset;
    Edge e;
    
    set_init(g->n);
    qsort(g->edges, g->num_edges, sizeof(Edge), compare);

    printf("Kruskal Minimum Spanning Tree Algorithm using QSort\n");
    int i=0;
    while(edge_accepted < (g->n-1)) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if(uset != vset) {
            printf("Edge (%d, %d) Select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

// MinHeap 구조체 정의
typedef struct heapType {
    Edge heap[MAX_VERTICES];
    int heapsize;
} HeapType;

// Heap 생성 함수
HeapType *create() {
    return ((HeapType*)malloc(sizeof(HeapType)));
}

// Heap 초기화 함수
void init_heap(HeapType *h) {
    h->heapsize = 0;
}

// Heap 삽입 함수
void insert_heap(HeapType *h, Edge *node) {
    int i=++h->heapsize;
    while(i != 1 && node->weight < h->heap[i/2].weight) {
        h -> heap[i] = h -> heap[i/2];
        i = i/2;
    }
    h -> heap[i] = *node;
}

// Heap 삭제 함수
Edge delete_heap(HeapType *h) {
    Edge item, temp;
    int parent = 1, child = 2;
    item = h->heap[1];
    temp = h->heap[h->heapsize--];

    while(child < h->heapsize && temp.weight > h->heap[child].weight) {
        if(h->heap[child].weight > h->heap[child+1].weight) {
            child++;
        }
        if(temp.weight < h->heap[child].weight) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// MinHeap을 사용한 Kruskal MST 알고리즘 함수
void kruskal_minheap(GraphType *g) {
    int edge_accepted = 0;
    int uset, vset;
    Edge e;

    HeapType *h = create();
    init_heap(h);
    
    set_init(g->n);

    for(int i=0; i<=g->num_edges; i++) {
        insert_heap(h, &g->edges[i]);
    }

    printf("Kruskal Minimum Spanning Algorithm using MinHeap\n");

    while(edge_accepted < (g->n-1)) {
        e = delete_heap(h);

        uset = set_find(e.start);
        vset = set_find(e.end);

        if(uset != vset) {
            printf("Edge (%d, %d) Select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }

    free(h);
}

// 그래프 생성
GraphType *makeGraph() {
    GraphType *g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init_graph(g, 10);

    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;
}

int main() {
    GraphType *g = makeGraph();

    kruskal_qsort(g);
    printf("\n");
    kruskal_minheap(g);

    free(g);

    return 0;
}
