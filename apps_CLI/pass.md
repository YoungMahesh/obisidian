```bash
pass   # list all passwords
export EDITOR=nvim  # append this to ~/.bashrc file to set neovim as default editor
pass insert github/personal   # add new password, here we are storing it in `github` directory
pass insert github/work
pass generate aws    # generate and store a new password
pass show github/personl  # get password and metadata
pass show -c github/personal  # copy password to clipboard
pass find github    # get all passwords which have word `github` in their directory
pass grep "email"   # search word `email` within password or metadata
pass edit github/personal  # edit password or add metadata
# append `export $EDITOR=nvim` in ~/.bashrc file, to use nvim for editing pass files, word `export` is necessory to add
# metadata such as email, address etc, will go on any line below password line
# first line is for password, all other lines for metadata

# if you are getting warnging: There is no assurance this key belongs to the named user: change trust of gpg-key as mentiond in ./encryption.md

pass rm github/personal  # remove password
pass git log  # changes made until now
pass git revert HEAD   # remove last changes
# every edit, remove, generate, insert command of pass creates a new git-commit
# revert helps when you want to revert last update you made in `pass`

# lock pass content immediately by restarting gpg
gpg-connect-agent reloadagent /bye

# ------------------------------- Initialize --------------------------------------------------
# create or import gpg keys: read `encryption.md` file
gpg -k  # get gpg keys
# pub   rsa3072 2023-09-11 [SC] [expires: 2025-09-10]
#      525A4CCA5D86AE842D9A51C3DF39BF4C371A2ADD
# rsa3072 - cryptography-algorithm-name
# 525....ADD - gpg-public-key

sudo apt install pass

# create new password-store
pass init <gpg-public-key> # set/change gpg-key for password-store
cat ~/.password-store/.gpg-id  # view gpg-public-key used to encrypt passwords

# create new git repository
pass git init
# OR use existing password-store
git clone <pass-repository-url> ~/.password-store  # here we are cloning pass-repo in `.password-store`
# `~/.password-store` is the default directory for `pass`
```


### multiple pass
1. login to a different user account: `su -l <username>`

2. append to `.bashrc` file
    ```bash
    # set nvim as default editor for pass
    export EDITOR=nvim

    # need to execute `script /dev/null` to make pass work in other user-account shell
    # following script automatically execute `script /dev/null` on login
    if [ -z "$SCRIPT" ]; then
        SCRIPT=/dev/null script -q
    fi
    ```

- create new user if not already availble
    ```bash
    su -l <username> # login to diffrent user
    # setup new user on your ubuntu computer 
    useradd -m <username>  # create a new user
    passwd <username>  # set password for user
    ```

