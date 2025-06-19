- [implementation](https://github.com/YoungMahesh/dotfiles/tree/main/i3)
- i3 window manager
- [[Bluetooth]]

## dmenu (a program launcher)

```config
bindsym $mod+f exec --no-startup-id dmenu_run
```
- to add new app to dmenu list, put their CLI at `/usr/bin` 

## status bar (at bottom)
Here’s how you can hide/show your i3 bottom bar items, here we will hide **Wifi** and **IPv6** indicator:

1. Locate or create your i3status config. By default i3status will look in  
   `~/.config/i3status/config` or `~/.i3status.conf`
   If you don’t already have one, copy the system default in (on most distros):  
   ```bash
   mkdir -p ~/.config/i3status
   cp /etc/i3status.conf ~/.config/i3status/config
   ```

2. Edit `~/.config/i3status/config` and **remove** (or comment out) the lines that show wireless and ipv6.  
   Find the `order` section, it will look something like:
   ```ini
   order += "cpu_usage"
   order += "load"
   order += "disk /"
   order += "wireless wlan0"
   order += "ipv6"
   order += "tztime local"
```
   Change it to—for example—this:
   ```ini
   order += "cpu_usage"
   order += "load"
   order += "disk /"
   # order += "wireless wlan0"
   # order += "ipv6"
   order += "tztime local"
```

3. If your config has explicit blocks for wireless or ipv6, you can also comment those out:
   ```ini
   # wireless wlan0 {
   #    format_up = "W: %quality"
   #    format_down = ""
   #    ...
   # }
   #
   # ipv6 {
   #    format = "no IPv6"
   #    ...
   # }
```

4. Point i3bar at your modified config. In your i3 config (the one you pasted) you have:
   ```ini
   bar {
       status_command i3status
       …
   }
```
   Change it to:
   ```ini
   bar {
       status_command i3status -c ~/.config/i3status/config
       wheel_up_cmd nop
       wheel_down_cmd exec ~/.i3/scripts/custom_wheel_down
   }
```

5. Reload i3 (`Mod+Shift+R`). 

## workspace
- number on bottom-left (left on status-bar) let you know your current workspace)
## auto-start applications
## gaps and window appearance