#cli/file-manipulation 

```bash
sudo apt install zip

# -r = recursive
zip -r <zip-file-name>.zip <directory-to-zip>

# add timestamp
zip -r folder_$(date +%Y%m%d_%H%M%S).zip folder
# output: folder_20250828_162230.zip
zip -r folder_$(date +%Y-%m-%d_%H-%M-%S).zip folder
# output: folder_2025-08-28_16-23-15.zip

# suppress output logs using: `> /dev/null`
zip -r folder_$(date +%Y-%m-%d_%H-%M-%S).zip folder > /dev/null
```