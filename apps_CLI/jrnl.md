#app/note-taking 


```bash
# add entry to journal
jrnl today was average

# keywords like 'ago' for negative, 'm' for minutes, etc is not present 
#   in jrnl cli code, it is part of it's depenedency 'parsedatetime'
# https://github.com/bear/parsedatetime/blob/2a4b16901794f8dc71721d51aef6e1ecd643868b/parsedatetime/pdt_locales/base.py
# set timestamp at 1 hours 10 minutes before current
jrnl '1h ago 10m ago: started some work'
# 10 minutes ago
jrnl '10m ago: work2'
# 3 hours ago
jrnl '3h ago: work 3'
# 1 hour after current
jrnl '1h: work 4'

# view last 10 entries
jrnl -10
jrnl -n 10
# view all entries upto today
jrnl -to today
# view entries from a specific date or range
jrnl -from "last year" -to "March"
jrnl -on yesterday
# --short to give only one line for each entry
jrnl --short -n 10 

# search
jrnl -contains 'keyword'
```

### installation
```bash
pipx install jrnl
jrnl --version

# default path of jornal: ~/.local/share/jrnl/journal.txt
# default config path: ~/.config/jrnl/jrnl.yaml

# if pipx is not installed
sudo apt install pipx
```