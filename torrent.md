```bash
sudo apt install transmission-cli

# default directory - $HOME/Downloads 
# download file at ./
transmission-cli [URL_or_PATH_of_torrent_file] -w ./ --no-seed
# -er, --no-seed, --exit   Exit after download is complete

# get size of file
transmission-show [URL_or_PATH_of_torrent_file]

# stop background running after download completion
pgrep transmission-cli  # get PID
kill <PID>
kill -9 <PID> # forcefully kill the process
```