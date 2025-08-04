#app/video

- show video as a mirror (e.g. when we raise left hand, it should see on our left in screen also)
	- Right-click on video -> Transform -> Flip Horizontal


### camera + screen recording
- Go to Sources (2nd in bottom half) section 
- Add - Video Capture Device
- Add - Display Capture 
- Keep _Video Capture_ above _Display Capture_ in sources-section 
	- This will bring _Video Capture_ on forefront and _Display Capture_ to background
- Resize _Video Capture_ to bottom-right, so we can see display in background
- Add - Audio Capture Device
	- Device: Default (OBS Studio will not show name of your Bluetooth-earphone)
	- In `pavucontrol` -> Recording -> `OBS: Mic/Aux from` -> Select your device
	
- Go to Controls (at bottom-right) section
	- Start/Stop Recording

### installation
- https://obsproject.com/kb/linux-installation