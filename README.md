*This project has been created as part of the 42 curriculum by [lalamino], [csamakka].*

# minishell

## Description

`minishell` is a simplified reimplementation of a Unix shell, written in C as part of the 42 core curriculum. It reproduces the core interactive behavior of Bash: reading and parsing a command line, expanding variables, handling quoting, connecting commands through pipes, redirecting file descriptors, and executing built-in and external commands while correctly propagating exit status and signals.

This project focuses on process management, file descriptors, and signal handling — the goal is not to reimplement Bash exhaustively, but to faithfully reproduce its behavior on the subset of features required by the subject.

### Implemented features (mandatory part)

- Interactive prompt with command history (`readline` / `add_history`)
- Command parsing with support for:
  - simple and double quotes (`'...'`, `"..."`), including `$`-expansion inside double quotes
  - environment variable expansion (`$VAR`) and `$?` (exit status of the last foreground pipeline)
- Redirections: `<`, `>`, `>>`, and heredoc `<<` with a delimiter
- Pipes (`|`), chaining any number of commands
- Executable resolution via `PATH`, or relative/absolute path
- Built-in commands: `echo` (with `-n`), `cd` (relative/absolute path), `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling in interactive mode:
  - `Ctrl-C` → new prompt on a new line
  - `Ctrl-D` → exits the shell
  - `Ctrl-\` → ignored, as in Bash
- A single global variable, storing only the last received signal number (no shared data structures in global scope)
- Memory-leak-free execution of all project-owned code (verified with Valgrind)

No bonus feature (`&&` / `||` with parentheses, wildcards `*`) is implemented in this submission.

## Instructions

### Compilation

```sh
make        # builds the minishell binary
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

The Makefile compiles with `-Wall -Wextra -Werror` using `cc`, and does not perform unnecessary relinking.

### Running

```sh
./minishell
```

This launches an interactive prompt. Standard shell usage applies, for example:

```sh
minishell$ echo "hello $USER" | grep hello > out.txt
minishell$ cat << EOF
> type some input, ended by EOF
> EOF
minishell$ export FOO=bar 
minishell$ env | grep FOO
minishell$ exit
```

Non-interactive mode (e.g. `./minishell < script.sh` or piped input) is also supported.

**Note:** `2>&1` and other advanced redirection syntaxes are not part of the 42 subject and are therefore not handled — test such commands from a real Bash session, not from within minishell.

## Resources
- [Bash features](https://www.gnu.org/software/bash/manual/bash.html)
- [Abstract Syntax Tree](https://keleshev.com/abstract-syntax-tree-an-example-in-c/)
- [Structure unions/enums](https://nareshit.com/blogs/structures-unions-and-enums-in-c-explained)
- `man bash` — reference behavior for parsing, quoting, and built-in semantics
- GNU Readline library documentation (`readline`, `add_history`, `rl_replace_line`)
- Man pages: `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`, `wait(2)`/`waitpid(2)`, `signal(7)`, `sigaction(2)`, `stat(2)`, `access(2)`
- Valgrind documentation, used throughout development to track and fix memory leaks

### AI usage

AI (Claude) was used as a support tool during debugging sessions.