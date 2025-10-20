#cli/env #encryption 

- https://dotenvx.com/

```bash
npm install @dotenvx/dotenvx --save
npx dotenvx help

# set a single environment variable
npx dotenvx set <KEY> <value>  
# return a single environment variable
npx dotenvx get [KEY]
npx dotenvx get [KEY] -f [FileName]
# convert .env file(s) to encrypted .env file(s)
npx dotenvx encrypt -f [FileName]
npx dotenvx encrypt -f .env.dev
# convert encrypted .env file(s) to plain .env file(s)
npx dotenvx decrypt -f [FileName]

# inject env variables in decrypted form to the cli command 
npx dotenvx run -f [envFileName] -- [CLI_Command]
npx dotenvx run -f ./.env.dev -- next dev
```