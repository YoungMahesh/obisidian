## extensions
- [control panel for twitter](https://chromewebstore.google.com/detail/control-panel-for-twitter/kpmjjdhbcfebfjgdnpjagcndoelnidfj?hl=en&pli=1)
- [unhook - Remove YouTube Recommended](https://chromewebstore.google.com/detail/unhook-remove-youtube-rec/khncfooichmfjbepaaaebmommgaepoid)
- [excalisave](https://chromewebstore.google.com/detail/excalisave/obnjfbgikjcdfnbnmdamffacjfpankih)
- [focustodo](https://chromewebstore.google.com/detail/focus-to-do-pomodoro-time/ngceodoilcgpmkijopinlkmohnfifjfb?hl=en) - disabled
- [gnome-shell-extension](https://chromewebstore.google.com/detail/gnome-shell-integration/gphhapmejobijbbhgpjhcjognlahblep?hl=en) - disabled

### launch extension from CLI
- get extension id
	- open manager-extensions: chrome://extensions/
	- click on 'Details' button of the related extension
	- turn on 'Developer Mode' in top-right -> you will row 'ID' with value as extension-id
- get path of index.html of extension
	- open chromium config
		- for chromium from snap: ~/snap/chromium/common/chromium
	- open `<profile-directory>/Extensions/<extension-id>/<extension-version>`
		- e.g. `/Default/Extensions/ngceodoilcgpmkijopinlkmohnfifjfb/7.0.0_0`
	- check `manifest.json` to get index.html path
		- if you did not find path yourself, paste `manifest.json` in AI chatbot for further research

#### launch Focus To-Do exension from CLI
```bash
# define profile-directory, extension-id, path of index.html
chromium --profile-directory="Default" --app="chrome-extension://ngceodoilcgpmkijopinlkmohnfifjfb/WebContent/index.html"
```

### chrome-vimium
- [vimium](https://chromewebstore.google.com/detail/vimium/dbepggeogbaibhgnhhndojpepiihcmeb?hl=en)

```json
// vimium-config.json
{
  "keyMappings": "map ; scrollPageDown\nmap a scrollPageUp\nunmap >\nunmap <",
  "settingsVersion": "2.3",
  "exclusionRules": [
    {
      "passKeys": "",
      "pattern": "https?://mail.google.com/*"
    },
    {
      "passKeys": ">,<,/,j,k,l,f",
      "pattern": "https?://www.youtube.com/*"
    },
    {
      "passKeys": "",
      "pattern": "https?://www.remnote.com/*"
    },
    {
      "passKeys": "",
      "pattern": "https?://excalidraw.com/*"
    }
  ]
}
```
## Take screenshot
1. open console `ctrl + shift + j`
2. open command menu `ctrl + shift + p`
3. search `screenshot`

## installation and config
### snap-store
- installation: https://snapcraft.io/chromium
- config file: `~/snap/chromium/common/chromium`
