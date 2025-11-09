# 🐚 Minishell (with Bonus 110/100)

> **This project is originally designed for a team of two people.  
I completed the entire project alone :P **  
---

## 📌 About the Project

Minishell is a simplified Unix command interpreter written in C.  
Its purpose is to provide a minimal yet functional shell environment that mimics essential behaviors of **bash**, while teaching process control, parsing, memory management, and Unix system programming.

This project is part of the **42 School curriculum**.

---

## ✨ Mandatory Features

| Feature          |             Description                               |
|------------------|-------------------------------------------------------|
| **Prompt**       | Displays a custom interactive shell prompt            |
| **History**      | Supports command history via `readline`               |
| **Command Parse**| Handles whitespace, quotes, and tokenization rules    |
| **Environment**  | `$VAR` expansion respecting quoted contexts           |
| **Builtins**     | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| **Redirections** | `<`, `>`, `>>`                                        |
| **Pipes**        | `cmd1 | cmd2 | cmd3 ...` multiple commands supported  |
| **Execute Cmds** | Executes binaries using `execve`                      |
| **Signal Handle**| Custom handling for: `Ctrl-C`, `Ctrl-D`, `Ctrl-\`     |
| **Heredoc**      | With correct behavior when delimiters are quoted      |
| **Leaks Hndling**| No memory leaks or file descriptor leaks              |
|--------------------------------------------------------------------------|
---

## ⭐ Bonus (Score: 110/100)

| Bonus Feature                 |             Description                                  |
|-------------------------------|----------------------------------------------------------|
| **Wildcards Expansion (`*`)** | Pattern matching for filenames, similar to bash globbing |

---

## 🧠 Key Technical Concepts Learned

- Process creation: **fork**
- Program execution: **execve**
- Environment variable handling: linked list storage
- File descriptors & redirections: **dup2**
- Pipeline implementation: **pipe**
- Parsing engine with quote state logic
- Signal masking and asynchronous behavior handling
- Memory discipline: **Valgrind-clean implementation**

---

## 🔧 Installation & Usage

```sh
git clone https://github.com/M4rgs/minishell.git
cd minishell
make
./minishell
```

---

## 📚 Example Session

```sh
$ echo Hello World
Hello World

$ export USERNAME=Taha
$ echo $USERNAME
Taha

$ ls | grep ".c" >> sources_list.txt

$ cat sources_list.txt
main.c
parser.c
utils.c
```
---

## 🎯 Goal

The goal of Minishell is to understand:
- Process creation and execution
- How shells parse and interpret commands
- File descriptors and pipeline communication
- Signal handling in interactive programs

---

###👤 Author
  TAHA MOUNIR
