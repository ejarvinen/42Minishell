# 42Minishell: A Minimal Bash-like Shell

## Overview
**Minishell** is a project aimed at creating a simple, yet functional shell. By developing our own shell, we gained a deeper understanding of processes, file descriptors, and the fundamentals of command-line interfaces.

## Features
- **Interactive Command Prompt**: Displays a prompt and waits for user commands.
- **Command Execution**: Executes commands using:
  - PATH environment variable.
  - Absolute or relative paths.
- **Built-in Commands**:
  - `echo` (with `-n` option).
  - `cd` (with relative or absolute paths).
  - `pwd` (prints current directory).
  - `export` (manages environment variables).
  - `unset` (removes environment variables).
  - `env` (displays environment variables).
  - `exit` (exits the shell).
- **Redirections**:
  - Input redirection `<`.
  - Output redirection `>`.
  - Append output redirection `>>`.
  - Here-document redirection `<<`.
- **Pipes**: Supports pipelines (`|`) to chain commands.
- **Quoting**:
  - Single quotes (`'`) prevent interpretation of special characters.
  - Double quotes (`"`) prevent interpretation except for `$` (variable expansion).
- **Environment Variables**: Expands variables (e.g., `$VAR`) and special variable `$?` (last command's exit status).
- **Signal Handling**:
  - `Ctrl-C`: Displays a new prompt.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing in interactive mode.
    
## Prerequisites
- **C Compiler**: Ensure a compatible C compiler (e.g., `gcc`) is installed.
- **Makefile**: Provided to simplify compilation.
- **GNU Readline**: Ensure [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) is installed for line editing and history management.

## Setup and Usage
### Installation
1. Clone this repository:
```
git clone https://github.com/staskine/42Minishell.git
cd 42Minishell
```
2. Build the project:
```
make
```
### Running Minishell
Start the shell by executing:
```
./minishell
```
## Development Guidelines
- **Norm Compliance**: Code must adhere to the 42 coding norm.
- **Memory Management**: All allocated memory must be freed properly to avoid memory leaks.
- **Error Handling**: Code should not crash unexpectedly (e.g., segmentation faults).
## Example Usage
