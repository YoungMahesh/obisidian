#grep
### Basic Syntax

```bash
# Basic Syntax
# **PATTERN**: The text or regular expression you want to search for.
# **FILE**: The file(s) you want to search in.
grep [OPTIONS] PATTERN [FILE...]

# search for the word "grep" in `example.txt`
grep "grep" example.txt

info grep
```

---

### Common Options

- `-i` : Ignore case (case-insensitive search)
- `-n` : Show line numbers
- `-v` : Invert match (show lines that **do not** match)
- `-r` : Recursively search directories
- `-l` : Show only filenames with matches
- `-c` : Count the number of matching lines

---

### Examples

```bash
# Case-insensitive search
grep -i "grep" example.txt

# Show line numbers
grep -n "grep" example.txt

# Show lines that do NOT contain "grep"
grep -v "grep" example.txt

# Search recursively in all `.txt` files in a directory
grep -r "pattern" *.txt
# search recursively in all files in current directory
grep -r "pattern" * 
```
