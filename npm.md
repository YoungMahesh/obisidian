- ### npm update
- How Updates Are Handled
	- npm packages are defined as: `"react": "^18.3.1"`
		- e.g. in `18.3.1` - 18 == version , 3 == minor, 1 == patch
	- When running commands like npm update, npm evaluates these symbols to determine which versions of dependencies can be installed:
	- With Caret (^): If a newer minor or patch version exists within the allowed range, npm will update to that version.
	- With Tilde (~): Only patch updates are considered; if a newer patch version exists, it will be updated.
	- With No-Sign: No updates occur unless the specified version is changed in the configuration.
	- because of the system, `npm update` does not normally break app functionality

```bash
npm outdated # check list of packages which can be upgraded
npm update --save # upgrade node packages

# location of global node_modules
npm root -g
```
