#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t = x), (x = y), (y = t))
#define SORTS 20

void print_status(int list[], int n, int show) {
    if (show) {
        for(int i = 0; i < n; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");
    }
}

void selection_sort(int list[], int n, int show, int *move_cnt, int *com_cnt) {
    int least, temp;
    *move_cnt = 0;
    *com_cnt = 0;
    for(int i=0; i<n-1; i++) {
        least = i;
        for(int j=i+1; j<n; j++) {
            (*com_cnt)++;
            if(list[j] < list[least]) {
                least = j;
            }
        }
        if (i != least) {
            SWAP(list[i], list[least], temp);
            (*move_cnt)++;
        }
        print_status(list, n, show);
    }
}

void insertion_sort(int list[], int n, int show, int *move_cnt, int *com_cnt) {
    int i, j, key;
    *move_cnt = 0;
    *com_cnt = 0;
    for(i=1; i<n; i++) {
        key = list[i];
        for(j=i-1; j>=0; j--) {
            (*com_cnt)++;
            if(list[j] > key) {
                list[j+1] = list[j];
                (*move_cnt)++;
            } else {
                break;
            }
        }
        list[j+1] = key;
        print_status(list, n, show);
    }
}

void bubble_sort(int list[], int n, int show, int *move_cnt, int *com_cnt) {
    int i, j, temp;
    *move_cnt = 0;
    *com_cnt = 0;
    for(i=n-1; i>0; i--){
        for(j=0; j<i; j++) {
            (*com_cnt)++;
            if(list[j] > list[j+1]) {
                SWAP(list[j], list[j+1], temp);
                (*move_cnt)++;
            }
        }
        print_status(list, n, show);
    }
} 

int main() {
    int oList[20];
    int total_move, total_comp, move_cnt, comp_cnt;

    srand(time(NULL)); // 난수 생성기 초기화

    // 선택 정렬
    printf("Selection Sort\n");
    total_move = total_comp = 0;
    for (int i = 0; i < SORTS; i++) {
        for (int j = 0; j < 20; j++) {
            oList[j] = rand() % 100;
        }
        selection_sort(oList, 20, i == 0, &move_cnt, &comp_cnt);
        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %d\n", total_move / SORTS);
    printf("Average Compared Count : %d\n", total_comp / SORTS);

    // 삽입 정렬
    printf("\nInsertion Sort\n");
    total_move = total_comp = 0;
    for (int i = 0; i < SORTS; i++) {
        for (int j = 0; j < 20; j++) {
            oList[j] = rand() % 100;
        }
        insertion_sort(oList, 20, i == 0, &move_cnt, &comp_cnt);
        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %d\n", total_move / SORTS);
    printf("Average Compared Count : %d\n", total_comp / SORTS);

    // 버블 정렬
    printf("\nBubble Sort\n");
    total_move = total_comp = 0;
    for (int i = 0; i < SORTS; i++) {
        for (int j = 0; j < 20; j++) {
            oList[j] = rand() % 100;
        }
        bubble_sort(oList, 20, i == 0, &move_cnt, &comp_cnt);
        total_move += move_cnt;
        total_comp += comp_cnt;
    }
    printf("Average Moved Count : %d\n", total_move / SORTS);
    printf("Average Compared Count : %d\n", total_comp / SORTS);

    return 0;
}