#app/note-taking 

### workflow
```bash
# check status
timew
# start a new-tracking and stop previously running tracking
timew start abc
# list all
timew summary
```

### basic commands
```bash
# check active time-trackings
timew
# list all time-trackings
timew summary
# list all time-trackings with ids
timew summary :ids
# list summary of specific tag
timew summary <tag>

# start without tag
# you can assign tag to without-tag ids with `timew retag`
timew start
# start with new tag
# this will stop currently active tags/trackings and start new one
# start new tag while keeping active tags running
timew start abc
# timew start <active-tag> <new-tag>
timew start xyz abc
# start few minutes (can use keyword - min, mins, minutes) ago
# <number> and <keyword - min, mins> must not have space between them
timew start 3min ago abc
# start at specific time
timew start 12:00 abc
# check status
timew

# remove last executed command
# when we start new task while previous is running, this start command
#   1) register end time of running task 2) register start time for new task
#   you need to use 2 undo, to go remove above 2 steps
timew undo
# cancel currently active tracking; prefer undo
timew cancel

# add new entry for specifc time
# timew track <internal/start_time - end_time> <tag>
timew track 10:00 - 10:48 pqr
# entry passing through dates
timew track 2025-08-20T23:00:00 - 2025-08-21T07:00:00 'sleep' :adjust

# stop all trackings
timew stop
# stop specific tracking out of currently running trackings
timew stop abc
# stop at specific time
timew stop 13:00 abc

# add tag to existing entries
timew tag @3 xyz
# remove tag from existing entries
timew untag @3 xyz
# replace tag of previous-trackings with different/new tags
# timew retag <list-of-ids> <list-of-tags>
timew retag @4 @5 @6 study work
# list all tasgs
timew tags

# modify/update start or end time of specific tracking
timew modify start @6 09:21
# use :adjust if time of end time of previous entry overlaps with start time of this entry
timew modify start @6 09:21 :adjust
timew modify end @6 09:51

# delete tracking with tag
timew delete @2 @3
```

## installation
- https://timewarrior.net
```bash
sudo apt install timewarrior
timew --version

timew help
timew help <command>
# default config: ~/.config/timewarrior
# default database: ~/.local/share/timewarrior
man timew
time
```

