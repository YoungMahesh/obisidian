- `Watchpack Error (watcher): Error: EMFILE: too many open files, watch '/home'`
  - check instances - `cat /proc/sys/fs/inotify/max_user_instances` is probably 128
  - increase instances: append `fs.inotify.max_user_instances=256` in `/etc/sysctl.conf`
  - reload system configuration: `sudo sysctl -p`

