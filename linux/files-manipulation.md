```bash
# find
find .  # recursively list all files in current directory
# -maxdepth 1   # for subdirectory depth, 1 = only current directory, 2 == current directory and it's direct sub-directories, etc
# -type f   - find only files
# -size -20k  - '-' represents less than, '+' represents larger than, 'k' == kilo-bytes, 'M' == mega-bytes
# -delete  - delete files

find . -type f -size +20M -delete  # delete files >20MB from current directory recursively
find . -maxdepth 1 -type f -size -20k # list files <20kb from current directory

find . -type f -exec du -sh {} \;  # print files alonwith file-size
find . -type f -exec du -sh {} \ | grep 343;  # filter list with grep


# ------------------ collect file names --------------------------------------------------
find . -type f -size +7M | awk -F'/' '{print substr($NF, 1, length($NF)-4)}'
find . -type f | awk -F'/' '{print substr($NF, 1, length($NF)-4)}'
# 1. output of find cmd (find . -type f)
#./153.gif
#./116.gif

# 2. |: This is a pipe symbol (|), which takes the output from the find command and passes it as input to awk.
# 3. awk -F'/': This sets the field separator (-F) for awk to /, so it will split each line of input at each /.
# 4. '{print substr($NF, 1, length($NF)-4)}':
#   $NF refers to the last field in the line (which, after splitting by /, will be the filename like 153.gif).
#   substr($NF, 1, length($NF)-4): This extracts a substring starting from the first character (1) of $NF and with a length that is 4 characters
#       less than the total length of $NF. This effectively removes the last 4 characters (.gif in this case).
#   So, awk will print only the part of the filename you're interested in (e.g., 153 from ./153.gif).

# --------------------------------------- cat --------------------------------------------------------------------------------------
cat file1       # print data from file1 (cat = concatenation)
cat > file1     # data typed after this comand will be the content of the file1
cat >> file1     # data typed after this comand, will be appended to the file1
cat input | python app.py  # send/pipe data in 'input' file to the programme - python app.py

#-------------------- grep --------------------------
grep siddharth file1.txt -i  #search 'siddharth' in 'file1', -i == case-insensitivity
grep shiva *         # #search 'shiva' in all files in current folder

# view large files
less file1 # top to bottom
less +G file1 # bottom to top

# print lines
cat file1 # whole file
head -n 5 file1 # first 5 lines
tail -n 5 file1 # last 5 lines

# remaining
touch file1.txt # create file named `file1.txt`
file fileName        # get #file-information
sort fileName       # #sort lines of file in alphanumeric order
sort -n fileName    # #sort lines of file in numeric order
ls photos/ | sort -n > list1.txt  # sort filenames in `photos` folder in alphanumeric order and store it in `list1.txt`
```

```bash
#------------------------------ file management --------------------------------------------
pwd           # print present-working-directory/current-folder
cd            # change-folder to home folder ($HOME)
cd ..         # go to parent folder of current folder
cd Documents  # go to folder 'Documents' present in current folder
echo 'mahesh'     # print string -> mahesh
echo $HOME        # print value of "HOME" environment-variable
echo *s           # print all files in current folder ending with 's'
echo *m*          # print all files in current folder containing word 'm'
ls            # list files&folders in current folder
ls --all      # list all files including hidden(.) files
ls -l         # long(detailed) listing
ls -l app.js  # get details of a single-file
mkdir github      # create folder
mv file1 file3  # rename 'file1' -> 'file3'
mv file1 file3 dirName  # move 'file1', 'file3' to folder 'dirName'
mv /path/folder1 ./folder2  # move folder1 to folder2
mv /path/folder1/* /path/folder2   # move files&folders from folder1 to folder2
cp file1 file2            # create copy of file1 -> as 'file2'
cp file1 file2 dirName    # create copy of 'file1', 'file2' into folder 'dirName'
cp -r folder1/* folder2   # copy all files&folders from folder1 to folder2
du -sh <fileName>  # get size of folder
du -sh *    # get sizes of all files and folder in current folder
# -s == summerize, display total size for folder by caculation size of all files in it
# -h == size in human readable format, M==MB, K==KB
ln -s /usr/bin/python3 /usr/bin/python  # create symlink/soft-link to access "python3" as "python"
rm file_name         # delete file
rm -rf folder_name    # delete folder
```
