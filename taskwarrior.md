```bash
task add <task-description>  # create task
task   # list all non-completed, non-deleted tasks
task all  # list all tasks
task status:completed all  # list all completed tasks
task 1       # get details of task1, shows all stopwatch-sessions(start/stop)
task 1 start  # start task with ID=1, taskwarrior starts stopwatch
task 1 stop   # stop task with ID=1, total timestamp (start to stop) is saved in details
task 1 edit  # edit description, start-time, etc
task 3 done   # mark task with ID == 3 as completed
task 2 delete  # delete task with ID == 2
task status:completed delete  # delete all completed tasks
task purge  # remove all deleted tasks permanently
```


### backup

```bash
# Get today's date in the format YYYY-MM-DD
today=$(date +%Y-%m-%d)
zip -r task-backup-$today.zip ~/.task
```
### sync 
- sync `~/.task` directory

### installation

- https://taskwarrior.org/

```bash
sudo apt install taskwarrior # debian, ubuntu
task help
task version
man task  # task-documentation
task commands

---

```
## timewarrior

- [watson](./watson.md) is far more convenient to use than timewarrior if you care about how much time you spent throughout the day
- https://timewarrior.net/

```bash
sudo apt install timewarrior

# connect with taskwarrior
# 1. download: https://github.com/GothenburgBitFactory/timewarrior/blob/develop/ext/on-modify.timewarrior
# 2. copy file to `~/.task/hooks/`
# 3. chmod +x ~/.task/hooks/on-modify.timewarrior
task diagnostics # verify activation under hooks-section

timew summary '<task-description' # get total time of task will be tracked on `task start <id>` and `task stop <id>`
```
