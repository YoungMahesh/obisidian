```bash
# access rclone using UI
rclone rcd --rc-web-gui
rclone rcd --rc-web-gui --rc-user me --rc-pass mypass

rclone [options] subcommand source destination  # syntax
rclone [options] --help  # get help for rclone-command
rclone config            # add, remove, manage accounts
rclone config show       # print config_file
rclone config file       # get configuration file location for rclone
rclone listremotes       # get list of remote accounts

rclone lsf drive1:          # list files and folders
rclone mkdir drive1:fold1   # create new folder with name - fold1
rclone tree drive1:         # list files and folders in tree-like format
rclone size drive1:sangrah  # get #size of file or folder
rclone cat drive1:names.txt # print file-content on terminal

rclone move drive1:abc drive1:xyz # move "content" of abc to xyz, REMEMBER we are moving only content not directory, after execution abc/a.txt will be xyz/a.txt instead of xyz/abc/a.txt
rclone copy drive1:abc drive1:xyz # copy "content" of abc to xyz, after execution abc/a.txt will be copied as xyz/a.txt instead of xyz/abc/a.txt

rclone copy --progress ./cat.jpg drive1:pics  # copy local data to remote account, does not transfer files that are identical on source and destination

# https://rclone.org/filtering/#files-from-read-list-of-source-file-names
# copy files from list to target; each file-name on new line; trims whitespace around file-name; comments start with #
rclone copy --files-from <list-of-files> <path-where-files-in-list-are-stored> <target-path  
rclone copy --files-from list.txt ./dir1 drive1:dir1 

rclone move -v --drive-server-side-across-configs drive1:Hosted/Books drive2:books
# move files server side
# transfer files without using local-bandwidth, used with "copy", "move", and "sync"
# "-v" to visualize the progress
# for server-side transfer, source folder should be "Public" or "Shared with destionation-user", works when source and dest is "Google Drive"

# rename file/folder
rclone moveto drive1:tiger.jpg drive1:tiger11.jpg

rclone check drive_mahesh: ./drive
# Checks the files in the source and destination match.
# It compares sizes and hashes (MD5 or SHA1) and logs a report of files which don't match.
# It doesn't alter the source or destination.

rclone sync /local-path dest:folder --dry-run    # --dry-run shows changes which will happen if you run the command

# use `sync` only to delete files, if copy is interrupted, continue with copy command as it will skip existing identical files
# sometimes, source-path and destination-path differences are seen although there are none, especially when one is unencrypted and one is encrypted, in this case use --size-only to sync actual changes
rclone sync source: dest: --dry-run --size-only

rclone sync -i --progress /home/youngmahesh/downloads/docs drive1:docs --transfers=1000
# first-location is source, second-location is destination
# Destination is updated to match source, including deleting files if necessary
# "-i" flgs prompts you for permission before deleting anything,
# "--progress" shows the transferring files and transfer speed
# "--transfers=1000" transfer 1000 files at a time;
#    --transfers=1 to fast transfer of big files to pen-drives
#    --transfers=4 to fast transfer of big files to cloud
#    --transfer=500 to fast transfer small files 

rclone purge --progress drive1:another   # delete file, folder and content inside it
# file deletions by "sync" and "purge" are preserved in "trash" of the cloud storage

# https://rclone.org/commands/rclone_deletefile/
rclone deletefile remote:path [flags]
```

### rclone crypt
1. Create new remote (11. Crypt) using 'rclone config' (e.g of name 'encrypted')
2. Choose path (remote or local) of crypt while configuration
3. Choose password - this password encrypts file, hence even if you created another "encrypt:"-remote with "same password and location" you can decrypt file
4. Now, when file is moved/copied using path 'encrypted:folder' then the data will be copied in encrypted-form in the original path
5. If you want to get data in decrypted form browse as `rclone lsf encrypted:`, as browsing through original location will show encrypted files only
6. Add password to 'rclone config' for more protection 