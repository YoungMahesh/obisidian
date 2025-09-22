#keyboard 

- keymap: currently active keymap, if this value is empty then we are using default keymap
- default: default keymap given by vscode
- (neovim): through neovim keymap through vscode-neovim extension

| keymap  | default       | action                                        |
| ------- | ------------- | --------------------------------------------- |
| tab     | ctrl+tab      | quick open previous recently used editor/file |
| ctrl+a  | ctrl+a        | select all in current file                    |
| ctrl+e  | ctrl+e        | focus file explorer                           |
| ctrl+j  | ctrl+b        | toggle primary/left sidebar                   |
| ctrl+k  | ctrl+shift+p  | show all commands                             |
| ctrl+l  | ctrl+t        | toggle terminal                               |
| ctrl+m  | ctrl+1        | focus on first editor group                   |
| ctrl+n  |               | open lsp suggestion list                      |
| space+o |               | focus on outline view (neovim)                |
| ctrl+p  | ctrl+p        | go to file                                    |
| ctrl+r  | shift+alt+f12 | find all references                           |
| ctrl+;  |               | toggle secondary/right sidebar                |
