```bash
sudo apt install ffmpeg

# cut audio
ffmpeg -i a.ogg -ss 00:01:02.500 -to 00:01:09.250 -c copy x2.ogg
# -i    input file
# -ss   start time
# HH:MM:SS.MS   # time format, HH hours, MM minuts, SS seconds, MS milliseconds
# -to   end time
# -c    codec
```
