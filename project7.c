#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 200

// Element 구조체 정의
typedef struct Element {
    int key; // 각 원소의 키값
} element;

// 힙 구조체 정의
typedef struct heaptype {
    element heap[MAX];
    int heap_size; // 현재 힙의 크기
} HeapType;

// 에러 메시지 출력 함수
void error(char *message) {
    fprintf(stderr, "%s\n", message);
}

// 동적할당을 통한 힙생성
HeapType *create() {
    return((HeapType*)malloc(sizeof(HeapType)));
}

// 힙 초기화
void init(HeapType *h) {
    h -> heap_size = 0;
}

// 힙의 공백함수
int is_empty(HeapType *h) {
    return(h->heap_size == 0);
}

// 인덱스 1번부터 저장되기 때문에 MAX-1
int is_full(HeapType *h) { 
    return(h->heap_size == MAX-1);
}

// 현재 힙의 상태를 출력하는 함수
void printHeap(HeapType *h) {
    if(is_empty(h)) {
        error("Heap is empty\n");
    }
    else {
        for(int i=1; i<=h->heap_size; i++) {
            printf("%d ", h->heap[i]);
        }
        printf("\n");
    }
}

// 힙의 원소 삽입 함수
int insert_heap(HeapType *h, element item, bool isPrinting) {
    int count = 0; // 원소의 이동횟수를 카운팅하기 위한 변수
    int i = ++(h->heap_size); // 힙의 마지막 위치로 초기화

    // 부모의 키값보다 현재 원소의 키값이 클 때까지 반복
    while((i > 1) && item.key > h->heap[i/2].key) {
        h -> heap[i] = item; // 현재위치에 키값을 저장
        count++; // 원소 이동횟수 증가
        if(isPrinting) {
            printHeap(h); // 현재 힙의 상태 출력
        }
        h -> heap[i] = h -> heap[i/2]; // 현재위치에 부모노드를 복사
        i = i/2; // 부모노드로 이동
    }
    h -> heap[i] = item; // 적절한 위치에 원소 삽입
    if(isPrinting) printHeap(h); // 이동이 종료된후 힙의 현재상태 출력
    return count; // 카운트 반환
}

// 힙의 원소 삭제 함수
element delete_heap(HeapType *h) {
    element item, temp; // 삭제할 원소와 마지막 원소를 저장할 변수
    int parent, child, count = 0;

    item = h->heap[1]; // 우선순위가 가장 높은 노드, 루트의 원소
    temp = h->heap[(h->heap_size)--]; // 우선순위가 가장 낮은 노드, 마지막 노드
    parent = 1; // 삭제할 원소의 위치 (루르부터 시작)
    child = 2; // 초기 자식 노드의 위치 (루트의 왼쪽자식)

    // temp 원소를 적절한 위치에 삽입하기 위한 반복문 
    while(child<=(h->heap_size)) {

        // 두 자식 중에 키값이 더 큰 자식노드를 선택
        if((child < h->heap_size) && h->heap[child].key < h->heap[child+1].key) {
            child++;
        }

        // temp 원소의 키 값이 자식 노드의 키 값보다 크면 적절한 위치를 찾은 것으로 판단하고 루프 종료
        if(temp.key > h->heap[child].key) break;
        h->heap[parent] = h->heap[child]; // 자식 노드의 값을 현재 부모 위치에 저장
        parent = child; // 현재 위치를 자식 노드로 변경
        printHeap(h); // 현재 힙의 상태 출력
        count++; // 원소 이동 횟수 증가
        child *= 2; // 다음 레벨의 왼쪽 자식 노드로 이동
        
    }
    printf("Moved node count : %d\n", count); // 원소의 이동횟수 출력
    h->heap[parent] = temp; // 마지막 원소를 적절한 위치에 삽입
    return item; // 삭제한 우선순위가 높은 노드의 키값 반환
}

void levelorder(HeapType *h) {
    if(h->heap_size == 0) {
        error("Heap is empty\n");
    }
    else {
        int level = 1;  // 레벨을 나타내는 변수 (1부터 시작)
        int count = 0;  // 현재 레벨에서 출력한 원소의 수
        int elementsInLevel = 1;  // 현재 레벨에서 출력해야 할 원소의 총 수

        for(int i=1; i<=h->heap_size; i++) {
            if(count == 0) { // 레벨의 시작일 때 레벨 번호를 출력
                printf("[%d] ", level);
            }

            printf("%d ", h->heap[i]);
            count++;

            if(count == elementsInLevel) {
                printf("\n");  // 현재 레벨의 모든 원소를 출력했으면 줄바꿈
                level++;  // 다음 레벨로 넘어감
                elementsInLevel *= 2;  // 다음 레벨의 원소 수는 현재 레벨의 2배
                count = 0;  // 다음 레벨에서의 출력 원소 수를 0으로 초기화
            }
        }
        if(count != 0) printf("\n");  // 마지막 레벨의 원소들을 모두 출력한 후 줄바꿈
    }
}

int main() {
    
    // 초기 힙의 설정
    HeapType *h = create();
    init(h);

    element e1 = {90}, e2 = {89}, e3 = {70}, e4 = {36}, e5 = {75}, e6 = {63}, e7 = {65}, e8 = {21}, e9 = {18}, e10 = {15};

    insert_heap(h, e1, false);
    insert_heap(h, e2, false);
    insert_heap(h, e3, false);
    insert_heap(h, e4, false);
    insert_heap(h, e5, false);
    insert_heap(h, e6, false);
    insert_heap(h, e8, false);
    insert_heap(h, e9, false);
    insert_heap(h, e10, false);

    // 메뉴가 동작
    while(1) {
        int menu;
        element value;

        printf("\n=====Menu=====\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Printf Node by level\n");
        printf("4. Exit\n\n");
        printf("Enter a menu : ");
        scanf("%d", &menu);
        switch(menu) {
            case 1:
                printf("Enter a key : ");
                scanf("%d", &value);
                if(is_full(h)) {
                    error("Heap is full\n");
                }
                else { // 힙이 가득차있지않으면 삽입 실행
                    printf("Moved node count : %d\n", insert_heap(h, value, true));
                }
                break;
            case 2: 
                if(is_empty(h)) {
                    error("Heap is empty\n");
                }
                else {
                    delete_heap(h); // 힙이 비어있지않으면 삭제 실행
                }
                break;
            case 3: 
                levelorder(h); // 레벨순회
                break;
            case 4: exit(0); break; // 종료

            default: error("다시 입력하세요.\n"); // 메뉴값 외의 값을 입력 시 에러메시지출력
        }

    }

}