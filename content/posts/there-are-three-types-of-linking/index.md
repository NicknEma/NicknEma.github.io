+++
title = 'There Are Three Types of Linking'
date = 2024-04-22T14:03:38+02:00
draft = true
+++

I was taught that object files can be linked one of two ways: statically or dynamically.

Computer people love these two words and use them every time they can. Static and dynamic typing, static and dynamic scoping rules.

In the case of linking, the nomenclature describes whether the resulting binary has _depencencies_ that will still be unresolved when it will be loaded into memory for execution.

For a symbol to be resolved statically, the linker (typically `link.exe` on Windows and `ld` on Linux) needs access to the full compiled code, and will _hardcode_ the addresses of procedures and global variables as the operands of the instructions that use them.

For example, when compiling (and linking) this code:

```C
/* foo.c */
extern void foo(void) { /* ... */ }
```
```C
/* main.c */
extern void foo(void);

int main(void) {
    foo();
}
```

You'll get an executable that looks (at a very high level) like this:

```
foo:
0x01234567                    ; body of foo

...

main:
0x0A234567  jump 0x01234567   ; jump to the first instruction of foo
```

When the processor reaches the `jump` instruction, it looks at the memory address right next to it and, well... jumps there. It assigns that pointer to the program counter, which makes execution continue from there.

But when the linker _doesn't_ have access to the full code, and doesn't know the starting address of `foo` (as the procedure is defined in a different binary), this step can't be done. The `jump` instruction doesn't know _where to jump to_ until _someone_ finds out where `foo` is located and writes its address in there.

This is the difference between "static" and "dynamic" linking.

However, the case of "dynamic" linking still leaves one question unanswered: if it isn't the linker, _who_ is the one that locates the missing symbol, and _when_ does it fix the pointer?

I've heard people subdivide dynamic linking further into _implicit dynamic linking_ and _explicit dynamic linking_. This reflects the fact that there are, in fact, two possible answers to my question; these two approaches are quite different though, and they allow the programmer to solve different problems. Just saying "dynamic linking" to indicate both of them is quite reductive.

What are these two approaches?

In the first one ("implicit"), symbols are resolved _at load time_, by _a collaboration between the linker and the operating system's loader_.

The linker [creates in the binary a _jump table_](https://web.stanford.edu/~ouster/cgi-bin/cs140-winter13/lecture.php?topic=linkers), where each row corresponds to a missing symbol. The _usage sites_ of the symbols in question receive as an operand an index into the jump table at the corresponding row.

```
main:
0x0A234567  jump 0x0B234567 + 0  ; jump to entry 0 of the jump table

...

jump_table:
0x0B234567  jump ???             ; entry 0 corresponds to foo, the address of which is still unknown
```

The linker also writes _what the binary's dependencies are_ (which dynamic libraries contain the missing symbols' definitions).

When the program is launched, the operating system's loader takes the executable and all its dependencies; it then looks at the jump table and tries to fill it with the addresses of the corresponding symbol in the libraries.

```
; Inside the loaded copy of main.exe
main:
0x0A234567  jump 0x0B234567 + 0  ; jump to entry 0 of the jump table

...

jump_table:
0x0B234567  jump 0x0F234567      ; entry 0 corresponds to foo, the address of which
                                 ; has been found by the loader
```
```
Inside the loaded copy of foo.dll
foo:
0x0F234567                       ; body of foo
```

The implementation details of this method vary from one OS to another, but the point of it is to make sure that no program can run when some of its symbols are still unresolved.

For example, on Windows, trying to run a program without its associate library will bring up this message box:

(image of message box)

But what if we _want_ to run a program when some of its symbols are unresolved? What if the programmer wants to have more control over how the linking works, the time at which it happens and the logic behind it?

This is what the last kind of linking ("explicit" dynamic) is for. Windows and Linux both provide a way to do it, though they make it more cumbersome than the other two methods.

By defining `foo` as a procedure _pointer_, neither the linker nor the loader will complain about a symbol being unresolved. Procedure pointers are just pointers, after all.

```C
/* foo.c */
extern void foo(void) { /* ... */ }
```
```C
/* main.c */
typedef void Void_Proc(void);
static Void_Proc *foo;
```

We then need to manually assign the correct value to `foo`; then we can call it as usual:

```C
/* main.c */
int main(void) {
    foo = ...; // assign the pointer *somehow*
    foo();
}
```

Fortunately, both Windows and Linux provide ways to figure out what the correct value of `foo` should be. The exact signatures are of course different, but the idea is the same; first, load the library contents into memory:

```C
/* main.c */
{
    // If on Windows:
    HANDLE foo_library_handle = LoadLibraryA("foo.dll");

    // If on Linux:
    void  *foo_library_handle = dlopen("foo.so");
}
```

From the library handle, get the procedure's start address:

```C
/* main.c */
{
    // If on Windows:
    foo = (Void_Proc *) GetProcAddress(foo_library_handle, "foo");

    // If on Linux:
    foo = (Void_Proc *) dlsym(foo_library_handle, "foo");
}
```

And you're done.

You can see how this is quite different than the other flavour of "dynamic linking", as it allows the program to choose _when_ a library is loaded and linked, and even _if_ the library should be loaded. You can imagine the library names being the result of some computation instead of being static strings like the ones in the example, and you can imagine a program un-linking and re-linking symbols at will at any time.

Here is the full "dynamic explicit" code (without the error-checking noise):

```C
/* main.c */
#if OS_WINDOWS
#include <windows.h>
#elif OS_LINUX
#include <dlfcn.h>
#endif

typedef void Void_Proc(void);
static Void_Proc *foo;

int main(void) {
#if OS_WINDOWS

    HANDLE foo_library_handle = LoadLibraryA("foo.dll");
    foo = (Void_Proc *) GetProcAddress(foo_library_handle, "foo");

#elif OS_LINUX

    void  *foo_library_handle = dlopen("foo.so");
    foo = (Void_Proc *) dlsym(foo_library_handle, "foo");

#endif
    foo();
}
```
