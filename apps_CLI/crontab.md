#cli/cron

```bash
# check current content of crontab
crontab -l

# edit crontab
crontab -e

# import/copy specific file to crontab
crontab ~/dotfiles/cron/crontab.sh
```


### crontab entry
- verify syntax at: https://crontab.guru/
```sh
# run a backup of all your user accounts
# at 5 a.m every week with:
# m h  dom mon dow   command
# 0 5 * * 1 tar -zcf /var/backups/home.tgz /home/

# 0 means the job runs at the 0th minute (on the hour).
# 7-21/2 means every 2 hours starting from 7 AM to 9 PM (21 in 24-hour format).
# * * * means every day, every month, and every day of the week.
# sync-data is the command to be executed.
0 7-21/2 * * * bash ~/.config/sync/main.bash
```

## Description
Crontab is a system utility for scheduling and automating repetitive tasks or jobs. 
It is a text file, known as the "cron table," that contains a list of commands to be executed at specified times or intervals by the cron daemon running in the background. 
Each user on the system, including root, has their own crontab file, which can be edited using the `crontab` command.

### Key Points about Crontab in Ubuntu:
- The crontab file stores scheduled tasks and environment settings.
- Scheduled tasks are executed automatically at the times specified in the crontab entries.
- Users should edit their crontab files using the command `crontab -e`.
- To list the current scheduled tasks in the crontab, use `crontab -l`.
- To remove all scheduled tasks in the crontab, use `crontab -r`.
- The basic syntax for a crontab entry is:
  ```
  * * * * * /path/to/command arg1 arg2
  ```
  where the five asterisks represent scheduling fields for minute, hour, day of the month, month, and day of the week, respectively.
- Crontab files are stored in `/var/spool/cron/crontabs` but should only be edited via the crontab command.
- System-wide crontab configurations can be found in `/etc/crontab`.