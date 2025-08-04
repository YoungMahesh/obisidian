#vps/ssh
## X11 forwarding
- here we are considering both local and remote operating system is #ubuntu 24.04
```bash
# connect to vps server with X11 forwarding enable
ssh -X user@ip-address
ssh -X <host-in-config-file>

# ---------- inside vps --------------
# verify if x11 forwarding is enabled
echo $DISPLAY
# if you see output as `localhost:10.0` or `localhost:11.0`, then x11 forwarding is enabled

# execute GUI app on vps and you will see a window of that app opened in your
# local browser
# you may need to wait for around half-minute to see window of remote vps
xclock
```