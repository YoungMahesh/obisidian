#app-store #package-manager 
## basic commands #snap-store
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