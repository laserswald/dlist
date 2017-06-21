#include <assert.h>
#include <stdio.h>
#include "dlist.h"

void assert_list_is(dlist(int)* list, int* array, int len){
    dlist_element(int) *cursor = list->head;
    for (int i = 0; i < len; ++i) {
        assert(dlistel_data(cursor) == array[i]);
        cursor = cursor->next;
    }
}

void print_int_list(dlist(int)* list){
    printf("list:\n");
    dlist_foreach(int, list, cursor){
        printf("%d\n", cursor->data);
    }
}

int main(void){
    dlist(int) *list = NULL;

    // Push test
    dlist_push(int, list, 5);
    dlist_push(int, list, 3);
    int array[5] = {5, 3, 0, 0, 0};
    assert_list_is(list, array, 2);

    // Shift test
    dlist_shift(int, list, 2);
    assert_list_is(list, (int[]){2, 5, 3, 0, 0}, 3);

    // Pop test
    dlist_element(int) *item = NULL;
    dlist_pop(list, item);
    assert_list_is(list, (int[]){2, 5}, 2);

    // Unshift test
    dlist_unshift(list, item);
    assert_list_is(list, (int[]){5}, 1);
}

