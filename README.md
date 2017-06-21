# dlist
Type-safe single file linked list.

## What is this?
This is my personal attempt to make a nice templated version of a doubly linked list, in C. 

## Why not use [insert library here]?
In short, none of them have the right features I need. OpenBSD's queue.h comes really close, but I really dislike the whole ALL_CAPS_MACROS thing, and I
stole a lot of inspiration from queue.h.

## What makes this so special?
First of all, it takes advantage of a macro trick to parameterize a type that nobody I have been able to find has taken advantage of. BSD's queue.h and the darray.h file from _ 
come within inches, but fail at the last second. The trick looks an awful lot like C++....

Basically, once you declare the dlist for your type, you can then forever refer to it as `dlist(yourtype)`.

```
#include <dlist.h>

struct my_lovely_data {
    int data;
}

dlist_declare(struct my_lovely_data, my_lovely_data);

// Omg, it's just like C++!
void
operate_on_my_lovely_data_list(dlist(my_lovely_data)* l){
    // ...
}

int main(int argc, char **argv){
    // this is straight up magic
    dlist(my_lovely_data) *data = dlist_new(my_lovely_data);
}
```
