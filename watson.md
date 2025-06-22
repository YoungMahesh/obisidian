```bash
watson start algoexpert  # create and start project with name: `algoexpert`
watson projects # get list of projects
watson cancel # cancel the last call to the start command, the time will not be recorded
watson status # check currently running project
watson stop  # stop currently running project
watson restart # restart most recently stopped project
watson edit # rename current project or update time of current session
watson edit -1 # edit last frame, -2 for second last frame
watson edit <id> # edit frame by id, get ids from `watson log`
watson log # review total time spent of projects
watson log -c #  include currently running project in logs
watson log --project <project-name> # review total time spent on a specific project
watson remove -1 # remove last log, -2 for second-last log, and so on...
watson remove <id> # remove log by id, get ids from `watson log`
```

- Watson is cli time tracker
- [installtaion and bash-completion](https://tailordev.github.io/Watson/)
  - if last commit on [watson-repo](https://github.com/TailorDev/Watson) is 15-july-2022 then bash-completion is not working, install old version of watson in this case as mentioned [here](https://github.com/TailorDev/Watson/issues/491#issuecomment-1748119604)

### sync

- sync `~/.config/watson` directory
