## Pull Request Process

This library is tested with the [Check](https://libcheck.github.io/check) unit testing framework.

If you are contributing to the library's API, you need to:

- read [this tutorial] on writing tests for Check
- find a [test suite] related to the *module* (i.e. header file) you worked on
- if your module is brand new, create a new suite and write your tests there

Creating a demo program is encouraged, but *not* required. To do that, you should:

- make a new directory inside `examples`. Give it a brief name like `demo002`
- write a small program that uses your new function(s), in C or C++. You can use one of the [completed examples][] as a template
- in the same directory, create a [CMakeLists.txt][] (see the [notes](#notes))
- add your program to the project by editing the [main configuration file][]. For example, if your source files are in `demo002`, put this line at the bottom: `add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo002")`

For **all** contributions, make sure to:

- follow these coding conventions:

|                                                         | Naming style                     |
|:--------------------------------------------------------|:--------------------------------:|
| `struct`, `typedef struct`, "constructors" <sup>1</sup> | PascalCase                       |
| functions, variables, header files <sup>2</sup>         | snake_case                       |
|                                                                                            |
| <sup>1</sup> functions returning a `struct` or `struct *`, e.g. `ConstructInteger()`       |
| <sup>2</sup> exception: header's defining a `struct` should be PascalCase, e.g. `Int32.h`  |

|                                                         | Comment (doc) style                                |
|:--------------------------------------------------------|:---------------------------------------------------|
|  files with `.h`, `.c` extensions                       | `/* ISO C  */`                                     |
|  files with `.cpp`, `.cxx`, `.hpp`, `.hxx` extensions   | `// C++`                                           |
|  documentation comments                                 | - `/** block style */`, __never__ `/// line style` |
|                                                         | - begin [tags] with `@`, __never__ `\`             |

- compile the project according to the [build instructions][]
- **do not change any version numbers**
- if the project compiles with no errors or warnings, [create your pull request][]

---
###### Notes

- do **not** put a `project` declaration in your `CMakeLists.txt`: ~~project(my_demo_program)~~

- **do** link your program with the main project library, like so: `target_link_libraries(my_demo_program PRIVATE moreinttypes)`


[create your pull request]: https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork
[CMakeLists.txt]: https://www.jetbrains.com/help/clion/cmakelists-txt-file.html
[build instructions]: https://github.com/rdipardo/libmoreinttypes#building
[main configuration file]: https://github.com/rdipardo/libmoreinttypes/blob/master/CMakeLists.txt
[completed examples]: https://github.com/rdipardo/libmoreinttypes/tree/master/examples
[this tutorial]: https://libcheck.github.io/check/doc/check_html/check_3.html#How-to-Write-a-Test
[test suite]: https://github.com/rdipardo/libmoreinttypes/tree/master/test/src
[tags]: https://www.doxygen.nl/manual/commands.html
