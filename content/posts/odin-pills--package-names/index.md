+++
title       = 'Odin Pills: Package Names'
description = 'Why Odin requires package names to be different and how to (kind of) get around that.'
date        = '2024-11-04T21:08:06+01:00'
tags        = ['Programming Language', 'Compiler']
categories  = ['Explanation']
draft       = false
+++

The [Odin programming languages](https://odin-lang.org) is built around the idea of _packages_: independent code units that contain related functionality.

As the [documentation](https://odin-lang.org/docs/overview/#authoring-a-package) states, each Odin file must start with a _package declaration_, like this:

```Odin
package strings    // Package declaration

/* ... */
```

The above file declares itself to be part of the `strings` package. If another package wants to use the functionality it provides, it must import it like this:

```Odin
package program

import "path_to_package/strings"    // Import declaration

main :: proc() {
	s := strings.clone("Hellope")
}
```

This way, the `program` package can use the name `strings` to refer to the imported package.

However, if you try to do exactly what I did, you will run into a problem: My custom package is called _"strings"_, just like one of the packages in the `core` collection. This will cause a compilation error:

```
C:/odin/core/strings/ascii_set.odin(1:2) Error: Duplicate declaration of 'package strings'
        package strings
         ^~~~~~~~~~~~~^
        A package name must be unique
        There is no relation between a package name and the directory that contains it, so they can be completely different
        A package name is required for link name prefixing to have a consistent ABI
```

As you can see, the error is related to the _Application Binary Interface_, or _ABI_. In short, when the program is compiled and symbols need to be resolved, how can the linker know what links to what? If some code calls `clone()`, to which definition of the procedure is it referring? Odin uses package names to prevent this confusion.

Does this mean you can't have a custom package with the same name as a standard package? Actually, you can.
As the error message hints at, the name used for the package _declaration_ is only used for linking, while the name of the _directory_ will be what other packages can refer to.

So if you want a custom `strings` package, all you have to do is make sure that all the files in your `strings` directory have a different package _declaration_ than any of the ones used by the standard collections:

```Odin
package totally_not_a_string_package

/* ... */
```

An then use it as normal:

```Odin
package program

import "path_to_package/strings"

main :: proc() {
	s := strings.clone("Hellope")
}
```

Now just be careful to [use a different _import name_](https://odin-lang.org/docs/overview/#import-statement) if importing both packages, otherwise you will have name conflicts _before the compiler even gets to linking_. Yeah, it can get pretty confusing at times.
