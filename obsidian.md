## why not obsidian?

### 1. problem in custom vim-motions

I prefer to use custom vim motion while writing/editing notes.
Obsidian by default does not support custom vim-motions.
[obsidian-vimrc-support](https://github.com/esm7/obsidian-vimrc-support) enables custom vim motions on obisdian.
But, one custom keymap (9 to move cursor to end of line) is not working.

### 2. editor freeze

Obsidian editor hangs suddenly while working with vim-mode on ubuntu snap-package.
This happens very frequently

## Advantages of obsidian

- Better UI than neovim, vscode for markdown editing
- notes can be published in graph-view using [digital-garden](https://github.com/oleeskild/obsidian-digital-garden) plugin

# custom vim-motions for obsidian

```vimrc
" .obsidian.vimrc
" nnoremap - normal mode; vnoremap - visual mode
" nnoremap (non-recursive map); nmap (recursive map)
" recursive map: This creates a mapping where the RHS of the mapping is re-evaluated.
"   If the RHS contains other mappings, those mappings are expanded and executed as well.

" Move up half of viewport + cursor at middle (zz)
nnoremap a <C-u>zz
vnoremap a <C-u>zz

" Move down half of viewport + cursor at middle (zz)
nnoremap ; <C-d>zz
vnoremap ; <C-d>zz

" Move and insert at end of line
nnoremap q A
vnoremap q A

" Redo
nnoremap r <C-r>

" Move to first char of line
nnoremap 0 ^
vnoremap 0 ^

" Move to last char of line
" BUG: does not work with any of the following config
"nnoremap 9 $
"noremap 9 $
"noremap <silent> 9 $h
```
