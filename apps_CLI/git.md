#cli/file-manipulation 
### backup
```bash
# current state of files in git without history (latest commit files)
# git archive -o <repo-name>.zip <branch-name>
git archive -o repository.zip HEAD
# -o == --output

# use `git bundle` to backing up entire repository with their history intact; but can just clone zip
```


---
### How to Set Up Directory-Specific Git User Emails

#### 1. Edit Your Global Git Config

Open your global Git config file in your home directory:

```bash
nano ~/.gitconfig
```

#### 2. Add Conditional Includes

Add the following to your `~/.gitconfig` (adjust the paths as needed):

```ini
# ... other configuration such as default editor

[user]
    name = Your Name
    email = yourglobal@email.com

[includeIf "gitdir:~/x/"]
    path = ~/.gitconfig-work
```

- `~/x/` is the path where your work projects live.
- `~/a/` is the path where your personal projects live to which your global email will get set as there is specific configuration for `a` directory.
- The trailing slash is important (`gitdir:~/x/` matches all repos under `~/x/`).

#### 3. Create the Included Config Files

**For work projects:**

```bash
nano ~/.gitconfig-work
```

Add:
```ini
[user]
    email = xyz@gmail.com
```


Now, Whenever You Create a New Repo
- If you create a repo under `~/x/`, Git will automatically use `xyz@gmail.com`.
- If you create a repo under `~/a/`, Git will automatically use `abc@gmail.com`.

---


### post-commit hook

```bash
# 1. describe hook
# create-file-at .git/hooks/post-commit, this file will execute whenever you git-commit
#!/bin/sh
git push

# 2. make hook executable
chmod +x .git/hooks/post-commit
```


### submodule
`git submodule add <remote-repsitory-link> <path to directory from root of current git-repo>`

### initiate
```bash
git init # create git-repository in present working directory
rm -rf .git  # remove git-repository from present-working-directory

# ------------------------ configuration ----------------------------------
# use --global flag, to update gobal-configuation file
git config -l   # list global and local git config
git config -e  # update local git-config file which is present at ".git/config"
git config user.name "John Doe" # update User/Author name
git config user.email johndoe@example.com
git config core.editor "code --wait"	# set vs-code default editor for git
git config core.editor "nano -w"       # set nano as default editor for git
```

### manage
```bash
# ------------------------ working area ----------------------------------
git status # see which files / changes present in which area # file-names in red color are in working_area
# file-names in green color are in staging_area

git diff <file_path> # see changes present in working-area
git restore <file_path>   # delete file-changes made working area
git clean -f # delete all files in working area
git clean -fd  # delete all files and directories in working area

# ------------------------ staking/index area ----------------------------------
git diff --staged # see changes in present in staging_area
git add <file_path>   # move changes (newly created files or modification in previous files) to staging area
git restore --staged <file-path>   # move changes from staging_area to working_area
git stash push -- your_file.txt # stash specific file

# ------------------------ stash area ----------------------------------
git stash # move all changes from working and staging area to stash_area
git stash list # list all blocks of temporariy changes
git stash pop  # move most-recent block from stash_area to working_area ( position{0} )
git stash clear # delete all blocks in stash

# ------------------------ commit area ----------------------------------
git commit -m '<message>'     # move changes from staging_area to commit_area
# <message> is short text giving information about changes made in the commit
git commit --amend -m '<message>'  # move from staging_area to commit_area, but replace last-commit instead of creating new-commit
git log  # view all commits in current branch
git log --oneline # view all commits without description
git log --oneline --graph --all	 # view graphical representation of all branches
git diff <commit_id> # view changes present in commit_id
git revert <commit_ID> # remove all changes in given 'commit_ID'
git reset HEAD~1  # delete last commit and move changes from last-commit to working-area
# HEAD~2 will delete latest 2 commits, HEAD~3 will delete latest 3-commits and so on..

# change commit author
git filter-branch --env-filter '
OLD_EMAIL="old@gmail.com"
CORRECT_NAME="person1"
CORRECT_EMAIL="new@gmail.com"
if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_COMMITTER_NAME="$CORRECT_NAME"
    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_AUTHOR_NAME="$CORRECT_NAME"
    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags
# `git filter-branch` command with an `env-filter` option, is used to rewrite the history of a Git repository in a specific way.
# `--tag-name-filter cat`: specifies how tag names should be filtered. The `cat` filter means that tag names will not be changed. This is necessary because tags are pointers to commits, and since commits are being rewritten, tags need to be adjusted to point to the new commit SHAs.
# `-- --branches --tags`: apply these changes to all branches and tags in the repository. The double dash `--` is used to separate the filter-branch options from the revision parameters.
# After running this command, all commits in the repository that were made by the `OLD_EMAIL` will now appear to have been made by `CORRECT_NAME` with `CORRECT_EMAIL`. This is a form of rewriting history and is very useful if, for example, you committed to a repo using a wrong or outdated email address.

# ------------------------ remote area ----------------------------------
git remote add <remote_area_name> <remote_area_url> # add connection to the remote_area
# you can give any name you want to remote_area_name, devlopers normally use "origin" for their first / default remote_area
git remote -v  # list currently set remote_area / servers names and their areas
git remote remove <remote_area_name>   # remove connection with remote repository
git push <remote_area_name> <branch-name> # copy changes in commit-area to remote_area
git fetch <remote_area_name> <branch_name> # copy branch remote_area to commit_area
git pull <remote_area_name> <branch_name> # merge remote branch to current branch
git clone <remote_area_url> # copy git repository from remote server/area to current folder

# ----------------------------- store credentials -----------------------------
git clone <repository-http-url> # you will be prompted to put username and password
# set username
git config credential.username xyz
# set password/credintial
git pull # you will be prompted to submit credentials only if credential.helper = cache ('cache' is default)
git config credential.helper store # save remote repository credentials (username, password) permanently
# to change config values edit -> ./.git/config
# 'cache' stores credentials in memory, while 'store' stores it on  'disk'
# location of 'store' credentials: `cat ~/.git-credentials`

# ------------------------ branch management ----------------------------------
git branch <branch-name> # Create a new branch containing all git commits of current git-branch
git checkout --orphan <name>  # create a fresh branch without commits from current-branch
git branch -d <branch-name> # delete branch
git branch -m <current-name> <new-name>  # Change branch name
git checkout <branch-name> # move to another branch
git branch --all  # list all local and remote branches

git merge <branch-name> # merge branch with  <branch-name> to current branch
git merge <branch-name> --allow-unrelated-histories  # merge branch whose git-history does not match with current branch, normally used to merge changes from another repository
git merge --abort   # stop current merge process if there are conficts in merge, and you don't want to resolve them now

# ------------------------ tags ----------------------------------
git fetch --all --tags  # fetch all tags from remote
git checkout tags/<version> -b <branch-name>  # switch to a tag and create bracnh for it
```

### installation
- [git-scm](https://git-scm.com/download/linux)

### related
[[lazygit]]