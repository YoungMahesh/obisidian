### basics

```bash
# create sylink of all files in xyz to parent directory
# e.g. if there is file: xyz/.config/xyz.conf, symlink will be created in .config directory of parent link-this: parent-dir/.config/xyz.conf
stow xyz

# delete all symlinks from xyz directory
stow -D xyz


# specify in which directory you want to create symlinks
stow -t ~ xyz   # -t == target

# dry-run
stow -v -n xyz # -v == verbose, -n == dry-run
```

### installation

- debian/ubuntu: `sudo apt install stow`
