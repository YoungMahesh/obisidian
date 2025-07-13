### extensions
- [control panel for twitter](https://chromewebstore.google.com/detail/control-panel-for-twitter/kpmjjdhbcfebfjgdnpjagcndoelnidfj?hl=en&pli=1)
- [unhook - Remove YouTube Recommended](https://chromewebstore.google.com/detail/unhook-remove-youtube-rec/khncfooichmfjbepaaaebmommgaepoid)
- [vimium](https://chromewebstore.google.com/detail/vimium/dbepggeogbaibhgnhhndojpepiihcmeb?hl=en)
- [excalisave](https://chromewebstore.google.com/detail/excalisave/obnjfbgikjcdfnbnmdamffacjfpankih)
- [focustodo](https://chromewebstore.google.com/detail/focus-to-do-pomodoro-time/ngceodoilcgpmkijopinlkmohnfifjfb?hl=en) - disabled
- [gnome-shell-extension](https://chromewebstore.google.com/detail/gnome-shell-integration/gphhapmejobijbbhgpjhcjognlahblep?hl=en) - disabled

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
### Take screenshot
1. open console `ctrl + shift + j`
2. open command menu `ctrl + shift + p`
3. search `screenshot`