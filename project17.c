#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20  // 배열 최대 크기 정의

// 현재 배열의 상태를 출력하는 함수
void print_status(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 두 값을 교환하는 함수, 이동 횟수도 증가시킴
void SWAP(int *x, int *y, int *move_cnt) {
    int t = *x;
    *x = *y;
    *y = t;
    (*move_cnt)++;
}

// 배열을 분할하고 피벗 위치를 반환하는 함수
int partition(int list[], int left, int right, int *move_cnt, int *comp_cnt) {
    int pivot, low, high;
    low = left;
    high = right+1; 
    pivot = list[left];  // 피벗 설정
    do {
        do {
            low++;
            (*comp_cnt)++;
        } while(low<=right && list[low]<pivot);
    
        do {
            high--;
            (*comp_cnt)++;
        } while(high>=left && list[high]>pivot);

        if(low<high) SWAP(&list[low], &list[high], move_cnt); 
    } while(low<high);

    SWAP(&list[left], &list[high], move_cnt);
    return high; 
}

// 재귀적인 퀵 정렬 함수
void quick_sort_rec(int list[], int left, int right, int *move_cnt, int *comp_cnt, int show) {
    if(left < right) {
        if (show) print_status(list, MAX); // 정렬 과정 출력
        int q = partition(list, left, right, move_cnt, comp_cnt);
        if (show) print_status(list, MAX); // 정렬 과정 출력
        quick_sort_rec(list, left, q-1, move_cnt, comp_cnt, show);
        quick_sort_rec(list, q+1, right, move_cnt, comp_cnt, show);
    }
}

// 스택을 위한 구조체 정의
typedef struct {
    int left;
    int right;
} StackNode;

// 스택에 요소를 추가하는 함수
void push(StackNode stack[], int *top, int left, int right) {
    if ((*top) < MAX - 1) {
        (*top)++;
        stack[*top].left = left;
        stack[*top].right = right;
    }
}

// 스택에서 요소를 제거하는 함수
int pop(StackNode stack[], int *top, int *left, int *right) {
    if ((*top) > -1) {
        *left = stack[*top].left;
        *right = stack[*top].right;
        (*top)--;
        return 1;
    }
    return 0;
}

// 반복적 퀵 정렬 함수
void quick_sort_iter(int list[], int left, int right, int *move_cnt, int *comp_cnt, int show) {
    StackNode stack[MAX];
    int top = -1;

    push(stack, &top, left, right);

    while (top >= 0) {
        int start, end;
        if (pop(stack, &top, &start, &end)) {
            int pivot = partition(list, start, end, move_cnt, comp_cnt);
            if (show) print_status(list, MAX); // 정렬 과정 출력

            if (pivot - 1 > start) {
                push(stack, &top, start, pivot - 1);
            }
            if (pivot + 1 < end) {
                push(stack, &top, pivot + 1, end);
            }
        }
    }
}

int main() {
    int oList[MAX];  // 원본 배열
    int move_cnt, comp_cnt;
    double total_move, total_comp;

    srand(time(NULL));  // 난수 초기화

    // 재귀적 퀵 정렬 실행
    printf("\nQuick Sort using recursive\n");
    total_comp = total_move = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < MAX; j++) {
            oList[j] = rand() % 100;  // 난수 생성
        }

        move_cnt = comp_cnt = 0;
        quick_sort_rec(oList, 0, MAX - 1, &move_cnt, &comp_cnt, i == 0);
        if (i == 0) print_status(oList, MAX);  // 첫 번째 케이스에서 정렬 후 상태 출력

        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %lf\n", total_move / 20);
    printf("Average Compared Count : %lf\n", total_comp / 20);

    // 반복적 퀵 정렬 실행
    printf("\nQuick Sort using iterative\n");
    total_comp = total_move = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < MAX; j++) {
            oList[j] = rand() % 100;
        }

        move_cnt = comp_cnt = 0;
        quick_sort_iter(oList, 0, MAX-1, &move_cnt, &comp_cnt, i == 0);
        if (i == 0) print_status(oList, MAX);  // 첫 번째 케이스에서 정렬 후 상태 출력

        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %lf\n", total_move / 20);
    printf("Average Compared Count : %lf\n", total_comp / 20);

    return 0;
}
