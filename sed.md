#ubuntu/file-manipulation 
## 1. **Search (Print Matching Lines)**

```bash
# - `-n`: Suppresses automatic printing.
# - `/pattern/p`: Prints lines matching `pattern`.
# sed -n '/pattern/p' filename
sed -n '/hello/p' file.txt

# it is better to use grep to search, as it print line numbers, so that you can delete content using lines (safer way)
grep -n 'hello' file.txt
```

---

## 2. **Delete Line(s)**

To **delete** lines matching a pattern or by line number:

```bash
# Delete by pattern
sed '/pattern/d' filename

# Delete by line number
# see output by removing first line
sed '1d' filename
# -i == edit file; edit the file in place by removed 1st line
sed -i '1d' filename
# delete 3rd line
sed -i '3d' filename

# Delete a range of lines (e.g., lines 2 to 4)
sed -i '2,4d' filename
```

---

## 3. **Add Line (Insert/Append)**

```bash
# Insert a line before a pattern
sed '/pattern/i\New line text' filename

# Append a line after a pattern
sed '/pattern/a\New line text' filename

# Insert at a specific line number (before line 3)
sed '3i\Inserted line' filename

# Append at a specific line number (after line 3)
sed '3a\Appended line' filename
```

---
## Basic Information
- https://www.gnu.org/software/sed/
- sed (stream editor) is a non-interactive command-line text editor.
- sed is commonly used to filter text, i.e., it takes text input, performs some operation (or set of operations) on it, and outputs the modified text. sed is typically used for extracting part of a file using pattern matching or substituting multiple occurrences of a string within a file.
