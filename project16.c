#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 20  // 정의된 최대 배열 크기

int sorted[MAX];  // 병합 정렬을 위한 임시 배열

// 현재 배열의 상태를 출력하는 함수
void print_status(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 두 부분 배열을 병합하는 함수
void merge(int list[], int left, int mid, int right, int *move_cnt, int *comp_cnt) {
    int i = left, j = mid + 1, k = left;

    // 두 부분 배열을 순회하며 요소들을 비교하고 정렬
    while (i <= mid && j <= right) {
        (*comp_cnt)++;  // 비교 횟수 증가
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
        (*move_cnt)++;  // 이동 횟수 증가
    }

    // 남은 요소들을 sorted 배열로 이동
    while (i <= mid) {
        sorted[k++] = list[i++];
        (*move_cnt)++;
    }
    while (j <= right) {
        sorted[k++] = list[j++];
        (*move_cnt)++;
    }

    // sorted 배열에서 원본 배열로 요소들을 복사
    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
    }
}

// 재귀적으로 배열을 병합 정렬하는 함수
void merge_sort_rec(int list[], int left, int right, int show, int *move_cnt, int *comp_cnt) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;

        // 분할 과정을 시작하기 전의 배열 상태 출력
        if (show == 1) {
            printf("Before dividing [%d, %d]: ", left, right);
            print_status(list + left, right - left + 1);
        }

        merge_sort_rec(list, left, mid, show, move_cnt, comp_cnt);
        merge_sort_rec(list, mid + 1, right, show, move_cnt, comp_cnt);

        // 병합하기 전의 배열 상태 출력
        if (show == 1) {
            printf("Before merging [%d, %d]: ", left, right);
            print_status(list + left, right - left + 1);
        }

        merge(list, left, mid, right, move_cnt, comp_cnt);

        // 병합 후의 배열 상태 출력
        if (show == 1) {
            printf("After merging [%d, %d]: ", left, right);
            print_status(list + left, right - left + 1);
        }
    }
}

// 반복적 방식으로 배열을 병합 정렬하는 함수
void merge_sort_iter(int list[], int n, int show, int *move_cnt, int *comp_cnt) {
    int i, j, left, mid, right;
    for (i = 1; i < n; i *= 2) {
        for (j = 0; j < n - i; j += i * 2) {
            left = j;
            mid = j + i - 1;
            right = j + 2 * i - 1;
            if (right >= n) right = n - 1;
            merge(list, left, mid, right, move_cnt, comp_cnt);

            if (show == 1) {
                print_status(list, n);
            }
        }
    }
}

int main() {
    int oList[MAX];  // 원본 배열
    int total_move, total_comp, move_cnt, comp_cnt;

    srand(time(NULL));  // 난수 초기화

    printf("\nMerge Sort using recursive\n");
    total_comp = total_move = 0;

    // 재귀적 병합 정렬을 여러 번 실행하며 평균 이동 및 비교 횟수 계산
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < MAX; j++) {
            oList[j] = rand() % 100;
        }

        move_cnt = comp_cnt = 0;  
        merge_sort_rec(oList, 0, MAX - 1, i == 0, &move_cnt, &comp_cnt);  
        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %d\n", total_move / 20);
    printf("Average Compared Count : %d\n", total_comp / 20);

    printf("\nMerge Sort using iterative\n");
    total_comp = total_move = 0;

    // 반복적 병합 정렬을 여러 번 실행하며 평균 이동 및 비교 횟수 계산
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < MAX; j++) {
            oList[j] = rand() % 100;
        }
        move_cnt = comp_cnt = 0;
        merge_sort_iter(oList, MAX, i == 0, &move_cnt, &comp_cnt);
        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %d\n", total_move / 20);
    printf("Average Compared Count : %d\n", total_comp / 20);

    return 0;
}