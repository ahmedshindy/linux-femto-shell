# linux-femto-Shell

Implementing a simple linux shell that supports some features of the linux bash shell.

## Supported Utilities
- Execute all commands available on your system "external commands" using fork and exec system calls.
- Local and environment variables where the environment variables are passed to any child created by your shell while the local variables are not passed to the child processes.

### Download & Compile
```shell
git clone https://github.com/ahmedshindy/linux-femto-shell
```
In the terminal navigate to the download directory/repo-name & type
```shell
  make build : to build the program
  make run   : to run 
```
### Usage 
```shell
- linux-command <flags> : run any external command as it usually runs on bash
- var_name = var_value  : set local variable by writing.
- set                   : shows your own shell commands.
- export var_name       : to export shell local variable to be environment variables "available for you shell only".
```

##### Watch [Demo](https://youtu.be/Q_-8Zb4FTMQ)
##### Credits [Eng. Reda](https://www.linkedin.com/feed/update/urn:li:activity:7008362772371533826/)
