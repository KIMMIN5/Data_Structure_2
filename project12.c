#include <stdio.h>
#include <stdlib.h>

#define INFINITY 1000L
#define MAX 100

int distance[MAX]; // 각 정점까지의 최소거리를 저장
int found[MAX]; // 최단경로를 찾은 정점을 표시

// 에러메시지 출력 함수
void error(char *message) {
    fprintf(stderr, "message\n");
}

// 현재 distance, found 배열의 상태를 출력하는 함수
void print_status(int distance[], int found[], int n) {
    printf("Distance: ");
    for(int i = 0; i < n; i++) {
        if(distance[i] != INFINITY) {
            printf("%d ", distance[i]);
        } else {
            printf("* ");
        }
    }
    printf("\nFound: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 인접행렬을 사용한 그래프 구조 정의
typedef struct graphType_matrix {
    int n;
    int weight[MAX][MAX];
} GraphType_matrix;

// 그래프(인접행렬) 생성 함수
GraphType_matrix *create_matrix() {
    return (GraphType_matrix*)malloc(sizeof(GraphType_matrix));
}

// 그래프(인접행렬) 초기화 함수
void init_g_m(GraphType_matrix *g) {
    g->n = 0;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            g->weight[i][j] = 0;
        }
    }
}

// 최단 경로 노드 선택 함수
int choose(int distance[], int n, int found[]) {
    int min = INFINITY;
    int minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && found[i] == 0) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 다익스트라 알고리즘 구현 
void shortest_path(GraphType_matrix *g, int start) {
    int u, w;
    int visitedOrder[MAX]; // 노드 방문 순서를 저장하는 배열
    int orderCount = 0; // 방문한 노드의 수를 카운트

    // 각 배열 초기화
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = 0;
    }
    found[start] = 1;
    distance[start] = 0;
    visitedOrder[orderCount++] = start;

    // 각 정점에 대해 최단경로 찾기
    for (int j = 0; j < g->n - 1; j++) {
        print_status(distance, found, g->n);
        u = choose(distance, g->n, found); // 최단 거리의 정점 선택
        found[u] = 1;
        visitedOrder[orderCount++] = u;

        // 선택된 정점과 인접한 모든 정점에 대해 최단 거리 업데이트
        for (w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INFINITY) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }

    // 방문 순서 출력
    for(int i=0; i<orderCount; i++) {
        printf("%d ", visitedOrder[i] + 1);
    }
    printf("\n");
}

// 인접행렬을 사용한 실습 그래프 생성
GraphType_matrix *makeGraph_matrix() {
    GraphType_matrix *g = create_matrix();
    init_g_m(g);
    g -> n = 10;
    int weight[10][10] = {
        {0, 3, INFINITY, INFINITY, INFINITY, 11, 12, INFINITY, INFINITY, INFINITY}, //1
        {3, 0, 5, 4, 1, 7, 8, INFINITY, INFINITY, INFINITY}, // 2
        {INFINITY, 5, 0, 2, INFINITY, INFINITY, 6, 5, INFINITY, INFINITY}, // 3
        {INFINITY, 4, 2, 0, 13, INFINITY, INFINITY, 14, INFINITY, 16}, // 4
        {INFINITY, 1, INFINITY, 13, 0, 9, INFINITY, INFINITY, 18, 17}, // 5
        {11, 7, INFINITY, INFINITY, 9, 0, INFINITY, INFINITY, INFINITY, INFINITY}, // 6
        {12, 8, 6, INFINITY, INFINITY, INFINITY, 0, 13, INFINITY, INFINITY}, // 7
        {INFINITY, INFINITY, 5, 14, INFINITY, INFINITY, 13, 0, INFINITY, 15}, // 8
        {INFINITY, INFINITY, INFINITY, INFINITY, 18, INFINITY, INFINITY, INFINITY, 0, 10}, // 9
        {INFINITY, INFINITY, INFINITY, 16, INFINITY, INFINITY, INFINITY, 15, 10, 0} // 10
    };

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            g->weight[i][j] = weight[i][j];
        }
    }
    return g;
}

// 그래프 노드 구조체 정의
typedef struct graphNode {
    int vertex;
    int weight;
    struct graphNode *link;
} GraphNode;

// 인접리스트를 사용한 그래프 구조 정의
typedef struct graphType_list {
    GraphNode *adj_list[MAX]; // 인접리스트 배열
    int numOfvertex; // 그래프 정점의 수
} GraphType_list;

// 힙 구조체 정의
typedef struct heapType {
    int heapsize;
    GraphNode *heap[MAX]; 
} HeapType;

// 힙 생성 함수
HeapType *create() {
    return(HeapType*)malloc(sizeof(HeapType));
}

// 힙 초기화 함수
void init_h(HeapType *h) {
    h->heapsize = 0;
    for(int i=0; i<MAX; i++) {
        h->heap[i] = 0;
    }
}

// 힙에 그래프 노드 삽입 함수
void insert_heap(HeapType *h, GraphNode *node) {
    int i=++h->heapsize;

    // 부모 노드와 비교하며 삽입할 위치를 찾음
    while(i != 1 && node->weight <= h->heap[i/2]->weight) {
        h->heap[i] = h->heap[i/2];
        i = i/2; 
    }
    h->heap[i] = node;
}

// 힙에서 노드 삭제 및 노드 반환 함수
GraphNode *delete_heap(HeapType *h) {
    GraphNode *item, *temp;
    int parent = 1, child = 2;
    item = h->heap[1];
    temp = h->heap[h->heapsize--];

    // 적절한 위치를 찾아 요소를 재배치
    while(child < h->heapsize) {
        if(child < h->heapsize && h->heap[child]->weight > h->heap[child+1]->weight) {
            child++;
        }

        if(temp->weight < h->heap[child]->weight) break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 인접리스트 그래프 생성 함수
GraphType_list *create_list() {
    return (GraphType_list*)malloc(sizeof(GraphType_list));
}

// 인접리스트 그래프 초기화 함수
void init_g_l(GraphType_list *gl) {
    gl->numOfvertex = 0;
    for(int i=0; i<MAX; i++) {
        gl->adj_list[i] = NULL;
    }
}

// 인접리스트 그래프에 정점 추가 함수
void insert_vertex(GraphType_list *gl, int vertex) {
    if(vertex > gl->numOfvertex || gl->numOfvertex > MAX -1) {
        error("Over vertex's number");
        return;
    }
    gl->numOfvertex++;
}

// 인접리스트 그래프에 간선 삽입 함수
void insert_edge(GraphType_list *gl, int s, int e, int weight) {
    if(s >= gl->numOfvertex || e >= gl->numOfvertex) {
        error("Default vertex's number");
        return;
    }
    GraphNode *newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode -> vertex = e;
    newNode -> weight = weight;
    newNode -> link = NULL;

    if(gl->adj_list[s] == NULL) {
        gl->adj_list[s] = newNode;
    }
    else {
        GraphNode *current = gl->adj_list[s];
        while(current -> link != NULL) {
            current = current -> link;
        }
        current -> link = newNode;
    }
}

// 다익스트라 알고리즘 구현 (인접리스트 사용)
void shortest_path_list(GraphType_list *gl, int start) {
    HeapType *h = create();
    init_h(h);
    
    int visitedOforder[MAX]; // 노드 방문 순서를 저장하는 배열
    int orderCount = 0; // 방문한 노드의 수를 카운트
    GraphNode *node;

    // 배열초기화
    for(int i = 0; i < gl->numOfvertex; i++) {
        distance[i] = INFINITY;
        found[i] = 0;
        visitedOforder[i] = -1;
    }

    // 시작 정점의 거리는 0
    distance[start] = 0;

    // 힙에 시작 정점 추가
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = start;
    node->weight = 0;
    insert_heap(h, node);

    while(h->heapsize > 0) {
        // 최소 가중치를 가진 정점을 힙에서 제거
        node = delete_heap(h);
        int current = node->vertex;

        if (!found[current]) {
            found[current] = 1;
            visitedOforder[orderCount++] = current;
            GraphNode *adjNode = gl->adj_list[current];

            // 인접한 모든 정점에 대해 거리 업데이트
            while(adjNode != NULL) {
                int v = adjNode->vertex;
                if (found[v] == 0 && distance[v] > distance[current] + adjNode->weight) {
                    // 최단 거리 업데이트
                    distance[v] = distance[current] + adjNode->weight;
                    // 힙에 업데이트된 거리 정보를 가진 정점 추가
                    GraphNode *newNode = (GraphNode*)malloc(sizeof(GraphNode));
                    newNode->vertex = v;
                    newNode->weight = distance[v];
                    insert_heap(h, newNode);
                }
                adjNode = adjNode->link;
                print_status(distance, found, gl->numOfvertex);
            }
        }
        free(node);
    }

    // 방문 순서 출력
    for(int i=0; i<orderCount; i++) {
        printf("%d ", visitedOforder[i]+1);
    }
    printf("\n");

    // 힙 해제
    free(h);
}

// 인접리스트를 사용한 실습 그래프 생성
GraphType_list *makeGraph_list() {
    GraphType_list *gl = create_list();
    init_g_l(gl);

    for(int i = 0; i < 10; i++) {
        insert_vertex(gl, i);
    }

    // 0번 인덱스의 인접 리스트
    insert_edge(gl, 0, 1, 3);
    insert_edge(gl, 0, 5, 11);
    insert_edge(gl, 0, 6, 12);

    // 1번 인덱스의 인접 리스트
    insert_edge(gl, 1, 0, 3);
    insert_edge(gl, 1, 2, 5);
    insert_edge(gl, 1, 3, 4);
    insert_edge(gl, 1, 4, 1);
    insert_edge(gl, 1, 5, 7);
    insert_edge(gl, 1, 6, 8);

    // 2번 인덱스의 인접 리스트
    insert_edge(gl, 2, 1, 5);
    insert_edge(gl, 2, 3, 2);
    insert_edge(gl, 2, 6, 6);
    insert_edge(gl, 2, 7, 5);

    // 3번 인덱스의 인접 리스트
    insert_edge(gl, 3, 1, 4);
    insert_edge(gl, 3, 2, 2);
    insert_edge(gl, 3, 4, 13);
    insert_edge(gl, 3, 7, 14);
    insert_edge(gl, 3, 9, 16);

    // 4번 인덱스의 인접 리스트
    insert_edge(gl, 4, 1, 1);
    insert_edge(gl, 4, 3, 13);
    insert_edge(gl, 4, 5, 9);
    insert_edge(gl, 4, 8, 18);
    insert_edge(gl, 4, 9, 17);

    // 5번 인덱스의 인접 리스트
    insert_edge(gl, 5, 0, 11);
    insert_edge(gl, 5, 1, 7);
    insert_edge(gl, 5, 4, 9);

    // 6번 인덱스의 인접 리스트
    insert_edge(gl, 6, 0, 12);
    insert_edge(gl, 6, 1, 8);
    insert_edge(gl, 6, 2, 6);
    insert_edge(gl, 6, 7, 13);

    // 7번 인덱스의 인접 리스트
    insert_edge(gl, 7, 2, 5);
    insert_edge(gl, 7, 3, 14);
    insert_edge(gl, 7, 6, 13);
    insert_edge(gl, 7, 9, 15);

    // 8번 인덱스의 인접 리스트
    insert_edge(gl, 8, 4, 18);
    insert_edge(gl, 8, 9, 10);

    // 9번 인덱스의 인접 리스트
    insert_edge(gl, 9, 3, 16);
    insert_edge(gl, 9, 4, 17);
    insert_edge(gl, 9, 7, 15);
    insert_edge(gl, 9, 8, 10);

    return gl;
}

int main() {
    printf("Dijkstra Algorithm using matrix\n");
    GraphType_matrix *g;
    g = makeGraph_matrix();
    shortest_path(g, 0);
    free(g);

    printf("\nDijkstra Algorithm using list\n");
    GraphType_list *gl = makeGraph_list();
    shortest_path_list(gl, 0);
    free(gl);

    return 0;
}
