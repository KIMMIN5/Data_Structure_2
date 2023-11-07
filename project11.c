#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INFINITY 1000L

int selected[MAX] = {0,}; // MST에 포함된 노드
int distance[MAX] = {0,}; // MST에 포함되지 않은 노드들의 번호와 Cost가 저장될 배열

void error(char *message) {
    fprintf(stderr, "\n%s\n", message);
}

typedef struct graphType {
    int n; // 정점의 개수
    int weight[MAX][MAX]; // 인접행렬로 표현된 그래프
} GraphType;

GraphType *create() {
    return (GraphType*)malloc(sizeof(GraphType));
}

void init_g(GraphType *g) {
    g->n = 0;
    
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            g->weight[i][j] = 0;
        }
    }
}

int get_min_vertex(int n) {
    int v; // 최소비용을 가진 정점
    for(int i=0; i<n; i++) {
        if(selected[i] == 0) {
            v = i;
            break;
        }
    }

    for(int j=0; j<n; j++) {
        if(selected[j] == 0 && distance[j] < distance[v]) {
            v = j;
        }
    }

    return v;
}

void prim_matrix(GraphType *g, int startNode) {
    int u, v;

    for(u=0; u<g->n; u++) {
        distance[u] = INFINITY;
    }
    distance[startNode-1] = 0;

    for(int i=0; i<g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = 1;
        if(distance[u] == INFINITY) {
            return;
        }
        printf("정점 %d 추가\n", u+1);
        for(v=0; v<g->n; v++) {
            if(g->weight[u][v] != INFINITY) {
                if(selected[v] == 0 && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}

GraphType *makeGraph() {
    GraphType *g = create();
    init_g(g);
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

int main() {
    GraphType *g = makeGraph();
    prim_matrix(g, 1);
    
    return 0;
}