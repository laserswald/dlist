#include <assert.h>
#include <stdio.h>
#include "dlist.h"

void assert_list_is(dlist(int)* list, int* array, int len){
    dlist(int) *cursor = list;
    int i;
    for (i = 0; i < len; i++) {
        assert(dlist_data(cursor) == array[i]);
        cursor = cursor->next;
    }
}

void print_int_list(dlist(int)* list){
    printf("list:\n");
    dlist(int)* cursor = list;
    dlist_foreach(list, cursor){
        printf("%d\n", cursor->data);
    }
}

int main(void){
    dlist(int) *list = NULL;

    // Push test
    dlist_push(int, list, 5);
    int array[5] = {5, 0, 0, 0, 0};
    assert_list_is(list, array, 1);

    // Shift test
    dlist_shift(int, list, 2);
    assert_list_is(list, (int[]){5, 0, 0, 0, 0}, 2);

    // Pop test
    dlist(int) *item = NULL;
    dlist_pop(list, item);
    //printf("data: %d\n", item->data);
    //print_int_list(list);

    // Unshift test
}

