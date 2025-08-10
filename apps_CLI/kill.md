#errors/processes #cli/proccess

```bash
# if you see you more than expected high RAM or CPU usage, check via
htop

# list top resources consuming processes
ps aux --sort=-%mem | head -5
# you will get process-id under 'PID' column

# kill bloatware processes
kill <pid>

# force kill (if normal kill command above does not worked)
kill -9 <pid>
```