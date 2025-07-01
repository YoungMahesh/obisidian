#less

```bash
# view large files
# Scroll up and down through the file interactively 
less file1 # top to bottom
less +G file1 # bottom to top
less +25 file1 # start viewing file from line 25

# inside less
ctrl+u # move half page up
ctrl+d # move half page down
n # full page down; next page
p # full page up; previous page
/<word> # search 'word', case-sensitive
q # quit 

info less
```