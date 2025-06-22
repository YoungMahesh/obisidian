# my ubuntu 24.04 setup


### install #apps

```bash
# check version
lsb_release -a

sudo apt update && apt list --upgradable
sudo apt install --only-upgrade package_name
sudo apt upgrade # upgrade all
```

### ui modifications

- open terminal window full-screen
  - open terminal-desktop file: `sudo nvim /usr/share/applications/org.gnome.Terminal.desktop`
  - append `--maximize` to line starting with Exec as: `Exec=gnome-terminal --maximize`

### default keyboard shortcuts

- `Super` - view Activities
- `Alt+Tab` - switch windows 
- `Super+l` - lock os (better than logout)


### gnome custom keyboard shortcuts (24.04)
- switch workspace
    - settings -> keyboard -> keyboard shortcuts -> View and Customize shortcuts -> Navigation
        - switch to workspace 1: Super+1
        - switch to workspace 2: Super+2
        - switch to workspace 2: Super+3
    - in ubuntu-24.04 this was not working, until i disabled `Extensions -> Ubuntu Dock`
- settings -> keyboard -> keyboard shortcuts -> View and Customize shortcuts -> Windows
  - View split on left: Super+a
  - View split on right: Super+d

### font

```bash
fc-list  # list all fonts on the computer
# download font from a font website such as: https://www.nerdfonts.com/font-downloads
# copy folder or .ttf file to `/usr/share/fonts` directory
fc-list | grep "CodeNewRoman"  # verify font (here CodeNewRoman) is installed on system
```
