### husky + lint-staged setup

- we are considering prettier is already setup
- lint-staged package is used to format files only which are in stage-area
- huskty is used to handle git-hooks
- with husky+lint-staged+prettier, we will setup a script which will automatically format changed files before commit

1. install packages

    ```bash
    # execute folllowing in root directory of the repository where ".git" folder is placed
    npm i -D husky lint-staged
    npx husky init 
    ```

2. define pre-commit hook
    - replace content from ".husky/pre-commit" with `npx lint-staged`, ".husky/pre-commit" is auto-generated when we ran `husky init`

3. pre-commit configuration
    - <https://www.npmjs.com/package/lint-staged#packagejson-example>
    - update package.json in your project, this need not to be in root-directory, suppose you have project setup in "apps/frontent" - add following config to "apps/frontend/package.json" file

    ```json
    {
      "name": "project1", // existing config of package.json
      "lint-staged": {  // new lint-staged config
        "*.{ts,tsx}": [   // apply only on files ending with .ts and .tsx
          "npx prettier --write"
        ]
      },
    }
    ```

4. done
    - you can now test setup by commiting some code

### setup prettier for typescript/javascript project

```bash
npm i -D prettier  # install prettier
npx prettier --write src/  # execute prettier to format all files in folder`src`
```

### +solidity support

```bash
npm i -D prettier prettier-plugin-solidity
npx prettier --write --plugin=prettier-plugin-solidity contracts/ test/  # format files in `contracts` and `test` folders
    # here prettier will also format ".sol" files, as it is using plugin for solidity
```
