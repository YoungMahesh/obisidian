
#install #ubuntu/app-store 
## app installation
### install from apt
```bash
# flameshot (#screeshot), pass (password-store), i3 (i3wm manager), 
# blueman (bluetooth manager), # pavucontrol (audio output management)
sudo apt install flameshot pass i3 blueman pavucontrol
```

### install from snap-store
- [snap-store](https://snapcraft.io/store)
- obsidian, telegram, chromium, brave, vlc, vscode

### pre-installed app-store
- `#snap-store` (for snap packages) and `gnome-software` (for Debian, Snap, Flatpak packages)


### check architecture
- execute `uname -m`
	- If the output is x86_64, your system is 64-bit (x64 or amd64 or x86_64).
	- If the output is i686, i386, or similar, your system is 32-bit (x86).

### make usb-drive compatible for image-flash on ubuntu
- format usb disk -> create partition on whole drive of type FAT 
- use balena-etcher with gnome UI (do not use i3wm interface as it creates problem for sudo password input which leads to error)
---

[[package-manager]]

[[flameshot]]
