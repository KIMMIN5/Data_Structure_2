#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SORTS 20

// 현재 배열의 상태 출력
void print_status(int list[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// Shell sort를 수행하기 위한 삽입정렬
void insertion_sort_for_shell(int list[], int n, int start, int gap, int *move_cnt, int *com_cnt) {
    int i, j, key;
    for(i = start + gap; i < n; i += gap) {
        key = list[i];
        for(j = i - gap; j >= start; j -= gap) {
            (*com_cnt)++;
            if(list[j] > key) {
                list[j + gap] = list[j];
                (*move_cnt)++;
            } else {
                break;
            }
        }
        list[j + gap] = key;
    }
}

// Shell sort
void shell_sort(int list[], int n, int *move_cnt, int *com_cnt) {
    int gap, i;
    *move_cnt = 0;
    *com_cnt = 0;
    for(gap = n / 2; gap > 0; gap /= 2) {
        if(gap % 2 == 0) {
            gap++;
        }
        for(i = 0; i < gap; i++) {
            insertion_sort_for_shell(list, n, i, gap, move_cnt, com_cnt);
        }
        printf("After gap %d: ", gap);
        print_status(list, n);
    }
}

// 메인함수
int main() {
    int oList[20];
    int total_move, total_comp, move_cnt, comp_cnt;

    srand(time(NULL)); // 난수 생성기 초기화

    // 셸 정렬
    printf("\nShell Sort\n");
    total_move = total_comp = 0;
    for (int i = 0; i < SORTS; i++) {
        for (int j = 0; j < 20; j++) {
            oList[j] = rand() % 100;
        }
        print_status(oList, SORTS);
        shell_sort(oList, 20, &move_cnt, &comp_cnt);
        total_move += move_cnt;
        total_comp += comp_cnt;
        printf("\n");
    }
    printf("Average Moved Count : %d\n", total_move / SORTS);
    printf("Average Compared Count : %d\n", total_comp / SORTS);

    return 0;
}
