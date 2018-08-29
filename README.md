### Mts (My tiny shell) is a simple implementation of a unix like shell. Based on [lsh](https://brennan.io/2015/01/16/write-a-shell-in-c/)

## Installation
```
$ git clone https://github.com/maks500/mst-shell
```

## Usage
```
$ cd mst-shell
$ make && ./mst
```

## TODO:
  - [X] Ctrl+L clear screen
  - [ ] env / setenv / unsetenv
  - [ ] history / Navigate history
  - [ ] Ctrl+R to search history
  - [ ] Up and down to navigate commands
  - [ ] Copy and paste
  - [ ] Auto Complete
  - [ ] `;` command line separator
  - [ ] Pipes
  - [ ] Redirections ( `>`, `>>`, `<`, `<<` )
  - [ ] Move to beginning and end of line
  - [ ] Colors ?
  - [ ] Show user and group
  - [ ] Variables with $
  - [ ] Brace expansion
  - [ ] Startup scripts
  - [ ] Run in background with `&`
  - [ ] Conditional execution with `&&` and `||`
  - [X] Ability to delete
  - [X] Ability to move and edit 
  - [ ] Aliases
  - [ ] Startup configuration files
  - [ ] Command parser, i.e treat echo "mts" as two arguments.
  - [ ] Create Tests

## License
MIT
