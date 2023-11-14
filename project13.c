#include <stdio.h>
#include <stdlib.h>

#define INFINITY 1000L
#define MAX 100

int distance[MAX][MAX];
int path[MAX][MAX];

// 에러메시지 출력 함수
void error(char *message) {
    fprintf(stderr, "message\n");
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

// 최단 거리를 출력
void print_distance(GraphType_matrix *g, int start, int end) {
    printf("Shortest Distance : %d\n", distance[start-1][end-1]);
}

// 최단 경로를 거치는 노드를 출력
void print_path(int start, int end) {
    if(path[start][end] != -1) {
        print_path(start, path[start][end]);
        printf(" ");
        print_path(path[start][end], end);
    }
    else {
        printf("%d", end+1);
    }
}

void print_shortestpath(GraphType_matrix *g, int start, int end) {
    printf("Shortest path node : %d ", start);
    print_path(start-1, end-1);
    printf("\n");
}

// Floyd-Warshall 알고리즘 구현
void floyd_matrix(GraphType_matrix *g) {
    int i, j, k;

    // 배열 복사 및 초기화
    for(i=0; i<g->n; i++) { 
        for(j=0; j<g->n; j++) {
            distance[i][j] = g->weight[i][j];
            path[i][j] = -1;
        }
    }

    // 최단 경로 업데이트
    for(k=0; k<g->n; k++) {
        for(i=0; i<g->n; i++) {
            for(j=0; j<g->n; j++) {
                if(distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    path[i][j] = k;
                }
            }
        }   
    }
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

int main() {
    GraphType_matrix *g = makeGraph_matrix();
    int start, end;
    printf("Floyd-Warshall Algorithm\n");

    while(1) {
        printf("Enter the start node : ");
        scanf("%d", &start);
        if(start == -1) break;
        printf("Enter the end node : ");
        scanf("%d", &end);
        floyd_matrix(g);
        print_distance(g, start, end);
        print_shortestpath(g, start, end);
    }

    free(g); // 메모리 반환
    

    return 0;
}