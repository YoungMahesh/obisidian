#package-manager for Ubuntu #ubuntu/app-store

```bash
<packageName> --version       # check version of app
<packageName> --help          # get options available for command

which <packageName>          # get path of file from which python3 command is executing
whereis <packageName>        # get all paths where command is available

# upgrade packages
sudo apt update && apt list --upgradable
sudo apt install --only-upgrade package_name
sudo apt upgrade # upgrade all

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