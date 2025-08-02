
### update keymaps
- Tools -> Preferences -> Interface -> Show setting (bottom-left) -> All -> left-menu search 
	- -> Hotkeys settings -> search `jump` to modify video jump keymap

### stop storing history
- Preferences -> Interface -> Show setting (bottom-left) -> All -> left-menu search -> 
	- Qt -> Uncheck "Save recently played items"
### clear history
- Media -> Open Recent -> Clear
## problems on Ubuntu 24.04
-  for some videos, only audio is playing, video not playing
	1. Open VLC.
	2. Go to Tools > Preferences.
	3. Click the Input/Codecs tab.
	4. Find Hardware-accelerated decoding and set it to Disable.
	5. Click Save.
	6. Restart VLC and try playing your video again.
	