# dlist
Type-safe single file linked list.

## What is this?
This is my personal attempt to make a nice templated version of a doubly linked list, in C. 

## Why not use [insert library here]?
In short, I don't think any are as safe and usable as they could be. This thing is designed to melt into the background just like another C 
linked list implementation; except with this, it's type-safe, because we don't have to deal with `void *`. With this library, you can use a parameterized type just like C++'s templates, and interact with it in pretty much the same way. 

OpenBSD's queue.h is certainly very close to this one, and I took a lot of inspiration from it. You could think of this library as a flashier and cleaner version of that one. 

## What makes this so special?
First of all, it takes advantage of a macro trick to parameterize a type that nobody I have been able to find has taken advantage of. BSD's queue.h and the [Fat-Array from htmk](https://github.com/htmk/Fat-Array) are examples of macro libraries similar to this one, but they don't have the parametric type that this one has. 

Of course, it's just really porcelain. But, it's really _nice_ porcelain, and this trick makes it absolutely clear what the type is, if you know that the macro is there. 

Basically, once you declare the dlist for your type, you can then forever refer to it as `dlist(yourtype)`.

```c
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
