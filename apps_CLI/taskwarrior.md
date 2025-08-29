#app/note-taking 

```bash
task add '<task-description>'  # create task
# task add <task-description> +<tag>
task add 'go to walk' +health
# get details of task with id 1, shows all stopwatch-sessions(start/stop)
task 1       
task 1 edit  # edit description, start-time, etc
task 3 done   # update status of task with ID == 3 as completed
task   # list pending tasks
task waiting # list waiting tasks
task completed # list completed tasks
# view all deleted tasks during `task purge`
# list tasks with specific tag
task +health
task all  # list all tasks, including hidden/waiting

# search
task /<keyword>/
task all /'mulitple words here'/

# change tags
task 1 2 3 modify -oldtag +newtag

# wait task until tomorrow
task 3 modify wait:tomorrow
# wait task until 3 days
task 4 modify wait:today+3d
# wait until upcoming monday
task 5 modify wait:monday
# remove hide (update status from waiting to pending)
task 4 modify wait:

task 1 start  # start task with ID=1, taskwarrior starts stopwatch
task 1 stop   # stop task with ID=1, total timestamp (start to stop) is saved in details
# use purge after delete to permanently delete
task 2 delete  # delete task with ID == 2
task status:completed delete  # delete all completed tasks
task purge  # remove all (completed and deleted) tasks permanently
# purge will prompt for each tasks specificially before removal
```

### urgency configuration
```bash
# increase urgency of tag by (0.8 + 0.5); 0.8 is constant
# task config urgency.user.tag.<tag-name>.coefficient <number>
task config urgency.user.tag.prep.coefficient 0.5
# decrease urgency of tag by (0.8 - 0.5); 0.8 is constant
task config urgency.user.tag.prep.coefficient -0.5
```

### backup

```bash
# Get today's date in the format YYYY-MM-DD
today=$(date +%Y-%m-%d)
zip -r task-backup-$today.zip ~/.task
```
### sync 
- sync `~/.task` directory

## installation

- https://taskwarrior.org/

```bash
sudo apt install taskwarrior # debian, ubuntu
# default configuration at: ~/.taskrc
task --version
task version
task help
man task  # task-documentation
task commands
```
### connect taskwarrior with [[timewarrior]]
- It is better to use taskwarrior and timewarrior separately. taskwarrior for planning and timewarrior to track/log work.

```bash
# connect with taskwarrior
# 1. download: https://github.com/GothenburgBitFactory/timewarrior/blob/develop/ext/on-modify.timewarrior
# 2. copy file to `~/.task/hooks/`
# 3. chmod +x ~/.task/hooks/on-modify.timewarrior
task diagnostics # verify activation under hooks-section

timew summary '<task-description' # get total time of task will be tracked on `task start <id>` and `task stop <id>`
```
