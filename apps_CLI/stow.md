### basics

```bash
# create sylink of all files in xyz to parent directory
# e.g. if there is file: xyz/.config/xyz.conf, symlink will be created in .config directory of parent link-this: parent-dir/.config/xyz.conf
stow xyz

# delete all symlinks from xyz directory
stow -D xyz


# specify in which directory you want to create symlinks
stow -t ~ xyz   # -t == target

# specify content-directory and target-directory 
stow -t ~/x/y/z .
# this will create symblink of content of current directory to target-directory

# create symlink of content inside directory ./notes to ~/x/y/z
stow -t ~/x/y/z notes

# NOTE: you cannot create symlink for file using stow (only directories
#   you need use `ln` if instead of `stow` if you want symlink of specific file

# dry-run
stow -v -n xyz # -v == verbose, -n == dry-run
```

### installation

- debian/ubuntu: `sudo apt install stow`
