#keyboard 

- keymap: currently active; original: replaced from nvim
- mappings below are placed according to order in qwerty keyboard
- actions with NULL are open to use for other purposes
- verify current map: 
	- try `:map <C-i>` OR `:help <C-i>` for `ctrl+i` mapping

| keymap | original | action                                                                                     |
| ------ | -------- | ------------------------------------------------------------------------------------------ |
|        | $        | move to end of line                                                                        |
|        | %        | move to pair of bracket                                                                    |
| q      | A        | move end of line + insert                                                                  |
|        | w        | move start of next word                                                                    |
|        | e        | move end of word                                                                           |
| r      | ctrl+r   | redo                                                                                       |
| t      |          | manage tabs                                                                                |
|        | y        | copy highlighted                                                                           |
|        | u        | undo                                                                                       |
|        | i        | insert                                                                                     |
|        | o        | move to line-below + insert                                                                |
|        | p        | paste at cursor                                                                            |
|        | [        | move to opening parent-bracket                                                             |
|        |          | e.g. `[{` to move to parent `{`                                                            |
|        |          | you can then move to to pair using % to select whole block                                 |
|        | ]        | NULL                                                                                       |
| a      | ctrl+u   | move cursor half-page up                                                                   |
| s      |          | manage save-files                                                                          |
|        | d        | delete                                                                                     |
|        | dw       | delete word                                                                                |
|        | f        | find forward in current line                                                               |
| g      |          | manage git in neovim                                                                       |
|        | h        | move cursor left                                                                           |
|        | k        | move cursor up                                                                             |
|        | l        | move cursor right                                                                          |
| ;      | ctrl+d   | move half-page down                                                                        |
| "      | '        | move to mark ('a to move mark a)                                                           |
|        | z        | manage fold                                                                                |
|        | x        | cut                                                                                        |
| xn     | ctrl+i   | next element in jump-list                                                                  |
| xp     | ctrl+o   | previous element in jump-list                                                              |
|        | c        | NULL; manage quickfix list                                                                 |
|        | v        | visual mode                                                                                |
|        | b        | move start of previous word                                                                |
|        | n        | move to next word search                                                                   |
|        | N        | move to previous word search                                                               |
|        | m        | set mark ('a to set mark a)                                                                |
| '      | $        | move end of line                                                                           |
|        | ,        | go to previous element in find-command search (, for previous element, . for next element) |
|        | .        | repeat previous find-command                                                               |
|        |          | (fa then . will execute fa again as )                                                      |
|        | /        | search current-file                                                                        |
| ctrl+a |          | select all in current file                                                                 |
|        | ctrl+o   | go to previous cursor location                                                             |
