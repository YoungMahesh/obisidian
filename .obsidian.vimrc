" Move to first char of line
nnoremap 0 ^
vnoremap 0 ^

" Move to last char of line
" nnoremap 9 g_  '9' and 'g_' keymap does not exist in obisidian-vim
" --------- not working -------------
nnoremap L $
vnoremap L $

" Move and insert at end of line
nnoremap q A

" Move up half of viewport + cursor at middle (zz)
nnoremap a <C-u>zz
vnoremap a <C-u>zz

" Move down half of viewport + cursor at middle
nnoremap ; <C-d>zz
vnoremap ; <C-d>zz

" Redo
nnoremap r <C-r>

" use the system clipboard as the default for yank, delete, change, and put operations
set clipboard=unnamedplus
