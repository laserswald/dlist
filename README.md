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

## Documentation

### Declarations
- `dlist_declare(type, typename)`
    Before you use a dlist, you need to declare it using this macro. The first argument is the actual type
    you want the list to hold, while the second is what you would like the type to be called. This
    is so you can hold pointers and such. You'll use the typename as the parameter to dlist() and all
    it's associated functions.

### Operations
In general, any function you want to use on a dlist takes the type it is specified with
as the first argument, and the list itself as the second argument.

#### Memory creation and deletion
- `dlist_new(type)`
    Create a new dlist on the heap. You don't need to clear the memory; this does it for you.

- `dlist_free(type, list)`
    Free a dlist and it's elements from memory.

- `dlist_shift(type, list, item)`
    Move an item to the head of the dlist. If you pass NULL as the list, it will create
    a new dlist (via dlist_new) for you and prepend it to that.

- `dlist_unshift(type, list)`
    Pull an item from the head of the dlist. This will delete the associated element, too.

- `dlist_push(type, list, item)`
    Append an item to the tail of the dlist. If you pass NULL as the list, it will create
    a new dlist (via dlist_new) for you, just like dlist_shift.

- `dlist_pop(type, list)`
    Like dlist_unshift, but the back of the list.

- `dlist_foreach(type, list, name)`
    This is a special macro to iterate over a dlist, starting with the head.. A new element with the name will be created, and will point to the current item.

- `dlist_foreach_rev(type, list, name)`
    Like dlist_foreach, but from the tail.

