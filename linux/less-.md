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
p # full page up; previous page
/<word> # search 'word', case-sensitive
n # next-occurrence of <word> in search
N # previous-occurence of <word> in search
j # move one line down
k # move one line up
q # quit 

info less
```