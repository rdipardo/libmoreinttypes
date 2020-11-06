# Contributing

#### Start by reading the [Code of Conduct][]

Browse the [open issues][] and choose **one** to work on.
Feel free to open a new issue if nothing is available.

Fork the main branch. Read about [making forks][] if you need help with this step.

Clone your fork.

Make sure the project compiles on your machine by following the [build instructions][].

## Pull Request Process

If you are contributing to the library's API, you need to:

- make a new directory inside `examples`. Give it a brief name like `demo002`
- write a small program that uses your new function(s), in C or C++. You can use one of the [completed examples][] as a template
- in the same directory, create a [CMakeLists.txt][] (see the [notes](#notes))
- add your program to the project by editing the [main configuration file][]. For example, if your source files are in `demo002`, put this line at the bottom: `add_subdirectory("${PROJECT_SOURCE_DIR}/examples/demo002")`

For **all** contributions, make sure to:

- compile the project according to the [build instructions][]
- **do not change any version numbers**
- if the project compiles with no errors or warnings, [create your pull request][]

---
###### Notes

- do **not** put a `project` declaration in your `CMakeLists.txt`: ~~project(my_demo_program)~~

- **do** link your program with the main project library, like so: `target_link_libraries(my_demo_program PRIVATE moreinttypes)`


[Code of Conduct]: CODE_OF_CONDUCT.md
[making forks]: https://docs.github.com/en/enterprise-server@2.20/github/getting-started-with-github/fork-a-repo
[create your pull request]: https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork
[CMakeLists.txt]: https://www.jetbrains.com/help/clion/cmakelists-txt-file.html
[open issues]: https://github.com/rdipardo/libmoreinttypes/issues?q=is%3Aissue+is%3Aopen
[build instructions]: https://github.com/rdipardo/libmoreinttypes#building
[main configuration file]: https://github.com/rdipardo/libmoreinttypes/blob/master/CMakeLists.txt
[completed examples]: https://github.com/rdipardo/libmoreinttypes/tree/master/examples
