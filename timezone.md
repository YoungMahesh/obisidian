### ubuntu server timezone

```bash
# set timezone of server to utc 
sudo timedatectl set-timezone UTC

# verify current timzone of server
timedatectl

# if you are running cronjobs using crontab, you need to restart it to  adjust it to new timezone
sudo service cron restart
```