A bash-like self-coded shell that works just like a regular shell:

* Displays a prompt while waiting for a new input
* Has a history of commands ran
* Searches and launches the right executable (relative or absolute paths)
* Interprets closed single and double quotes
* Interprets redirections (< , > , << and >>)
* Interprets pipes (|)
* Handles environment variables ($)
* Expands $? to the exit status of most recently executed pipeline
* Handles signals (ctrl-C, ctrl-D and ctrl-\) like bash
* Implements the following builtins:
  * echo (with -n)
  * cd (absolute or relative path)
  * pwd (no options)
  * export (no options)
  * unset (no options)
  * env (no options or arguments)
  * exit (no options)
 
## Compilation
Requires readline to be installed. Git clone project to desired directory. Run ```make```. Run executable ```./minishell```
