
```bash
# this will install playwright in local node_modules and create initial files
npm init playwright
# playwright will install browsers at ~/.cache/ms-playwright

# install playwright operating-system dependencies
sudo npx playwright install-deps
# if got error: sudo: npx: command not found
# then provide path for npx, npm, node from current env
sudo env "PATH=$PATH" npx playwright install-deps

# Runs the end-to-end tests.
npx playwright test

# Starts the interactive UI mode.
npx playwright test --ui

# Runs the tests only on Desktop Chrome.
npx playwright test --project=chromium

# Runs the tests in a specific file.
npx playwright test example

# Runs the tests in debug mode.
npx playwright test --debug

# Auto generate tests with Codegen.
npx playwright codegen
```