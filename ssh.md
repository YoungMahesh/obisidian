### setup ssh to connect with two github accouonts from same machine
```bash
# 1. create ssh key inside `~/.ssh` directory
ssh-keygen -f work -C "<email-address>"  # create ssh key, -f == file-name, -C=comment
ssh-keygen -f sample # with "-C", $USER@$HOSTNAME will be automatically included in ssh-public-key 
ssh-keygen -f <private-key-path> -C ""  -y > <pubic-key-path/name>.pub # generate public-key using private-key

# 2. paste `work.pub` and `mahesh.pub` files in respective github accounts
# github-account -> settings -> SSH and GPG keys -> SSH Keys -> New SSH key

# 3. update or create `~/.ssh/config` file
#---------------- `config` file---------------------------------------------
# Default github account
Host github.com
   HostName github.com
   User git
   IdentityFile ~/.ssh/work
   
# Other github account
Host github
   HostName github.com
   User git
   IdentityFile ~/.ssh/mahesh
#--------------------------------------------------------------------------------------

# 4. start ssh-agent
eval "$(ssh-agent)"    # start ssh-agent on debian/ubuntu
# eval (ssh-agent -c)    # start ssh-agent on garuda-linux

# 5. add private-keys to ssh-agent
ssh-add ~/.ssh/work   # add keys to ssh agen
ssh-add ~/.ssh/mahesh
# execute `chmod 400 ~/.ssh/work` if you encounter: `UNPROTECTED PRIVATE KEY FILE!` error

# 6. test your github connection
ssh -T git@github.com
ssh -T git@github

# 7. now for non-default github-account, while cloning or pushing code, 
#     update github ssh-url link with "Host" in config-file
# e.g.  git@github.com:Web3Modal/web3modal.git  -> git@github:Web3Modal/web3modal.git
```

### setup ssh to connect with remote server / vps
```bash
# 1. create ssh key inside `~/.ssh` directory
ssh-keygen -f workspace   # create ssh key, -f == file-name

# 2. paste content of `workspace.pub` to `/home/<username>/.ssh/authorized_keys` file on your remote-server

# 3. update or create `~/.ssh/config` file
#---------------- `config` file---------------------------------------------
Host company
   HostName <ip-address>
   User <username>
   IdentityFile ~/.ssh/workspace
   
#--------------------------------------------------------------------------------------

# 4. start ssh-agent, if not already running
eval "$(ssh-agent)"    # start ssh-agent on debian/ubuntu
# eval (ssh-agent -c)    # start ssh-agent on garuda-linux

# 5. add private-key to ssh-agent
ssh-add ~/.ssh/workspace   # add keys to ssh agen
# execute `chmod 400 ~/.ssh/workspace` if you encounter: `UNPROTECTED PRIVATE KEY FILE!` error

# 6. connect to your server
ssh company
```


### move files
```bash
# move file from vps to local
# here relative == path in vps at `echo $HOME`
scp <ssh-host>:<relative-path-to-file> ./

# move file from local to vps
scp ./image1.jpg  <ssh-host>:<relative-directory>
```
