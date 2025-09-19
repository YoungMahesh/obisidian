- interactive process viewer and system monitor

```bash
sudo apt install htop

htop
```


### fix RAM consumption

1. open htop, click on MEM% column to sort consumption by processes from highest to lowest
2. copy PID of processes you suspect, put pid in this command to get details of process origin: `ps -p 17145 -O command= >> a`, then open details with `nvim a`
3. common processes of apps
	1. vscode - `/proc/self/exe --type=utility --utility-sub-type=node.mojom.NodeService` 