#include <stdio.h>
#include <stdlib.h>

#define INFINITY 1000L
#define MAX 100

int distance[MAX];
int found[MAX];
int previous[MAX];

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

void print_MST(int parent[], int n) {
    printf("MST Edges:\n");
    for (int i = 1; i < n; i++) {
        printf("%d ", parent[i]);
    }
}

typedef struct graphType_matrix {
    int n;
    int weight[MAX][MAX];
} GraphType_matrix;

typedef struct graphType_list {

} GraphType_list;

GraphType_matrix *create_matrix() {
    return (GraphType_matrix*)malloc(sizeof(GraphType_matrix));
}

void init_g_m(GraphType_matrix *g) {
    g->n = 0;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            g->weight[i][j] = 0;
        }
    }
}

int choose(int distance[], int n, int found[]) {
    int min = INFINITY;
    int minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortest_path(GraphType_matrix *g, int start) {
    int u, w;
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = 0;
        previous[i] = start; // 초기에 모든 노드의 부모를 시작점으로 설정
    }
    found[start] = 1;
    distance[start] = 0;

    for (int j = 0; j < g->n - 1; j++) {
        u = choose(distance, g->n, found);
        found[u] = 1;
        for (w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] < distance[w]) {
                distance[w] = g->weight[u][w];
                previous[w] = u; // 부모 노드 업데이트
            }
        }
        print_status(distance, found, g->n);
    }
    print_MST(previous, g->n); // MST 출력
}

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

GraphType_list *makeGraph_list() {

}

int main() {
    GraphType_matrix *g;
    g = makeGraph_matrix();
    shortest_path(g, 0);

    return 0;
}