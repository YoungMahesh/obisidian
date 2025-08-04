#app/note-taking

## plugins
- [vimrc support](https://github.com/esm7/obsidian-vimrc-support/)
	- need to enable 'Vim Key Bindings' in settings -> Editor -> Advanced
- [git](https://github.com/Vinzent03/obsidian-git)
- [TagFolder](https://github.com/vrtmrz/obsidian-tagfolder)
	- Obsidian have built-in Tag-support, but it does not list _Untagged_ files


## relations
1. Folders are one-to-many — one folder can hold many files that could be about anything.
2. Tags are many-to-many — a file can have multiple tags, and a tag can be used on multiple files.
3. Links are one-to-one — a specific file has a relationship with another specific file.

- Use case:
	- Tags for classification, Links for reference. 
		- e.g. Obsidian comes under #app/file-manipulation , while I use it by following [[note-taking principles]] 

### why tags instead of links
- tags can be view as list and graph, while links can be viewed only in graph
	-  list-view: top-left -> Tags -> Enable - Show nested tags
	- graph-view: left-sidebar -> Open Graph View -> Filters -> Tags - Enable
- tags are easier to assign
- tags can be searched easily outside obsidian

## Advantages of obsidian

- Better UI than neovim, vscode for markdown editing
- notes can be published in graph-view using [digital-garden](https://github.com/oleeskild/obsidian-digital-garden) plugin



## Publish
[[docs-quartz]]