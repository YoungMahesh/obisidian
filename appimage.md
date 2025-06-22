### create icon for an AppImage in the GNOME application menu

1. move .appimage to `~/.local/bin`
1. make appimage executable `chmod +x <name>.appimage`
1. create desktop entry
   - create .desktop file in `~/.local/share/applications`
   - set icon for appimage at `~/.local/share/icons`
   - write configuration in .desktop file
     ```desktop
     [Desktop Entry]
     Type=Application
     Name=Your App Name
     Exec=/path/to/your/YourAppImage.AppImage
     Icon=/path/to/your/app-icon.png
     Comment=Brief description of your app
     Categories=Category;Of;Your;App
     ```
   - make desktop entry file executable: `chmod +x .local/share/applications/yourapp.desktop`
   - update desktop-database: `update-desktop-database ~/.local/share/applications/`
1. check log file to view errors: `sudo tail -n 30 /var/log/syslog`
