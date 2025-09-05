
### concat

```ts
// wrap string with '' in CONCAT
// do not wrap variable with '' in CONCAT
select({
  id: sql<string>`CONCAT('player-', ${player.id})`,
})
```