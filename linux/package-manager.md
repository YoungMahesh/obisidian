# npm
```bash
npm init -y     # create package.json file for your project
npm install <package-name>  # install a package
npm install <package-name> --save-dev  # save as development dependency

npm install     # install all packages written in package.json
npm run <command>                      # run package.json script

npm install <package-name> -g          # globally install packge
npm uninstall -g yarn                  # remove global packages

npm -v          # check current version

npm list -g --depth=0     # check globally installed packages on npm
```

# snap
```bash
snap find <search-text>    # find packages on snap, you can also search pakages on snapcraft website
snap info <package>        # get information about package
snap install <package>     # install snap package
snap install --dangerous <package.snap>  # install snap package without signature
snap remove <package>      # remove snap package

snap list                  # list snap packages installed on your system
snap refresh --list        # check for updates for snap packages on system
snap refresh <package>     # update snap package
snap revert <package>      # revert back to the previous version of app

snap changes               # history of snap packages added and removed

snap download <package>    # download snap package
snap ack <package.assert>  # i think this is for varification of package
snap install <package.snap>  # install local package after varification as in above-line

sudo apt install snapd  # already installed on ubuntu-based systems
```

# apt (for debian/ubuntu) 
```bash
<packageName> --version       # check version of app
<packageName> --help          # get options available for command

which <packageName>          # get path of file from which python3 command is executing
whereis <packageName>        # get all paths where command is available

sudo apt install --only-upgrade <packageName>

sudo apt purge code   # remove vscode
sudo apt autoremove  # after every removal

dpkg-deb -x package.deb /opt/folder1   # install debian-package in a specific directory

apt install packageName    # #install package from repository
apt install ./packageName  # #install local package
apt remove packageName     # remove package
apt update                 # Refresh Repository Index to get information about latest packages in connected repositories
apt upgrade                # Upgrade all packages to latest version
apt autoremove             # Remove packages which are no longer needed
apt-cache search chrome    # search package in repositories
apt-cache policy vlc       # get #version available of the app in the ubuntu repository
dpkg -l | grep cal         # search package with name 'cal' in installed packages

cat /etc/debian_version    # find current debian #version on system
```




# flatpack  
```bash
flatpak install <package-name/path>
flatpak list
flatpack remove <package-name>
flatpak --help
```
