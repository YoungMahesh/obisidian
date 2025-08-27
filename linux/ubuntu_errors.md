- `Watchpack Error (watcher): Error: EMFILE: too many open files, watch '/home'`
  - check instances - `cat /proc/sys/fs/inotify/max_user_instances` is probably 128
  - increase instances: append `fs.inotify.max_user_instances=256` in `/etc/sysctl.conf`
  - reload system configuration: `sudo sysctl -p`



#### USB drive is auto-supending in background #auto-suspend #usb-drive 

```bash
# The Linux kernel's autosuspend feature can power down USB devices to save energy, unintentionally disconnecting them. Run the following command to check your current value:
cat /sys/module/usbcore/parameters/autosuspend
# If this outputs 2 (the default timeout in seconds), autosuspend is enabled and could be causing periodic unmounts.

# To temporarily disable autosuspend:
sudo sh -c 'echo -1 > /sys/module/usbcore/parameters/autosuspend'
```
