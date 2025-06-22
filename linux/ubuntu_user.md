```bash
#------------------------------ user management --------------------------------------------
useradd -m mahesh # create user named mahesh, # -m == create user's home folder
passwd mahesh # set password for user mahesh
deluser --remove-home mahesh # delete/remove user named mahesh

# set user's shell to bash
sudo chsh -s /bin/bash <username>

# user's group management
groups mahesh # list of groups of user mahesh
getent group docker # check list of users in group docker
usermod -aG docker mahesh  # add user mahesh to group docker, -a == append, -G == group-name
usermod -aG sudo mahesh # add user to sudo group
sudo gpasswd -d username groupname  # remove <username> from group with name <groupname>
# changes to sudo group may not take effect immediately, user need to logout and login to get sudo privilages
 
# hide user from ubuntu-login-ui (Ubuntu_v22.04)
#   1. change value of variable `SystemAccount` to `true` in `/var/lib/AccountsService/users/<user-name>`
    sudo -s   # you cannot use `sudo` and cd together, so switch to root user first 
    cd /var/lib/AccountsService/users/<user-name>
    Ctrl+d  # exit from root user
#   2. execute: `sudo systemctl restart accounts-daemon.service`


# switch to a different user-account
su -l mahesh # switch to user `mahesh`
script /dev/null  # fixes permisssion-denied in some cases (e.g. gpg --gen-key)

sudo -i  # switch to root user
```


```bash
#------------------------------ server-management ----------------------------
free -h  # check RAM/memory stats of server
# buff/cache refers to a portion of memory maintained by the operating system and used for "page cache" - used for caching the content of files to speed up disk IO. 
# This is memory that, if needed, can be freed for other purposes - that's why you also see a lot of memory in the available column, it's the responsibility of the kernel to manage this

docker stats --no-stream # check memory consumed by docker containers


#-------------------------------- env ---------------------------------------
# To set environment variable, append env with it's value in ~/.bashrc file
export EDITOR=nvim  # set variable `EDITOR` with `nvim` as it's value, `export` is necessory to allow scripts to use variable
# open new window and run `echo $EDITOR` to verify if env is set correctly

# reference: https://unix.stackexchange.com/questions/26047/how-to-correctly-add-a-path-to-path
# `PATH` environment veriable of bash stores all paths of executable files separated by `:`
# append path `~/.bashrc` file like this
PATH="${PATH:+${PATH}:}~/opt/bin"   # appending
PATH="~/opt/bin${PATH:+:${PATH}}"   # prepending

# change directory-name color to orange (blue is difficult for eye to see)
export LS_COLORS="$LS_COLORS:di=38;5;208"
#-------------------------- file content handling ---------------------------------------------------------

#--------------------------------- terminal management -----------------------------------------------------------
echo $SHELL  # check which shell terminal  is currently using
chsh -s /bin/bash  # change default shell to bash, logout and login again to see the changes
ln -s /bin/python3 python  # create soft symlink, provide path of executable for certain command
alias docker-compose='docker compose' # now `docker-compose version` will execute -> `docker compose version`

###------------------------------ screen brightness (ubuntu 20) -----------------------------------------------
## for gnome you can use magnifier to control brightness as follows
# go to Settings->Accessibility->Zoom->(1.Magifier->Magnification:1.00)(2.ColorEffects->Brightness)

echo $XDG_SESSION_TYPE  # check display server protocol
# if display server protocol is x11 then you can use `xrandr` command as follows
xrandr        # check connected devices, screen type and screen-resolutions available
xrandr --output HDMI-2 --brightness .8   # manage brightness below default
xrandr --output HDMI-2 --mode 1368x768   # change screen resolution
# here HDMI-2 is name of device connected, replace it connected device name on your system


###------------------------------ time management -----------------------------------------------
date  # print current date and time

#-------------------------------- history ------------------------------------------------------
history      # list of all commands executed
history 7    # list of last 7 commands executed
!1132        # run 1132th command from history
(Cntr + r) <keyword> # search for command with <keyword> in history list

#------------------------------ session history ------------------------------------------------
script session.log # start storing commands and output
exit # print all stored history in `sessin.log` file in current folder
```

### operating sytem

- `dpkg --print-architecture` - check if computer have amd or arm architecture

### desktop

- Control brightness
  1. `sudo apt update && sudo apt upgrade`
  1. install [google chrome](https://www.google.com/intl/en_in/chrome/)
  1. install [gnome-shell-extension](https://chrome.google.com/webstore/detail/gnome-shell-integration/gphhapmejobijbbhgpjhcjognlahblep)
  1. install brightness controller
     - Upto gnome-version 42 use: [soft-brightness](https://extensions.gnome.org/extension/1625/soft-brightness/)
     - After gnome-version 42 (ubuntu 22.04)use: [soft-brightness-plus](https://extensions.gnome.org/extension/5943/soft-brightness-plus/)
  1. install "extensions" app by "The GNOME Project" from built-in "Ubuntu Software" app (optional, to manage settings of extensions)
  1. logout and login
  1. now you will have brightness controller in top-right menu
  1. Update `Full-screen behavior` in `Extensions_app->Soft brightness plus->settings` to keep backlight during full-screen videos

```bash
Cntr + Alt + <left or right arrow-key>  # move to left or right workspace
```

- shortcuts
  - ctrl + tab : switch windows from current workspace
  - windows + tab : switch from all workspaces

### cron-job

```bash
# reference: https://www.hostinger.in/tutorials/cron-job
crontab -l    # list cronjob file
crontab -e    # edit cronjob file

# -----------------------------------Inside crontab-file-----------------------------------------------
# GET cron-syntax from  https://crontab.guru/, and put command infront of cron-syntax
* * * * * cd /path/to/folder && <command>
```
