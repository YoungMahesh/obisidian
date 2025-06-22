- VPS means *virtual private server* here

- [connect to vps with ssh](./ssh.md)

```bash
# connect to vps with username and passowd
ssh username@<ip-address> -o IdentitiesOnly=yes

# transfer file using ssh
scp <source> <destination>
scp /path/to/file username@<ip-address>:/path/to/destination
scp /path/to/file <"host" name from ~/.ssh/config file>:/path/to/destination
```
