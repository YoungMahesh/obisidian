- turso used libSql (a fork of sqlite) as it's database

```bash
# https://docs.turso.tech/reference/turso-cli
turso --version
turso auth login
turso auth token
turso db tokens create <db-name>  # create auth-token for database
turso db list  # list turso databases
turso db show <db-name> # get database information
turso db shell <db-name> # get access to database shell to execute sql-queries 
```

