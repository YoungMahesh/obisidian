#note-publish

- [quartz - v4](https://quartz.jzhao.xyz/)

## content
- write content in `/content` directory
- `/content/index.md` is homepage file, without it site will break

## title
### update page title above explorer
update config in `quartz.config.ts`
```tsx
const config: QuartzConfig = {
  configuration: {
    pageTitle: "XYZ Docs",
   }
}
```

## footer
### update footer links

update  configuration in `quartz.layout.ts`

```tsx
export const sharedPageComponents: SharedLayout = {
  head: Component.Head(),
  header: [],
  afterBody: [],
  footer: Component.Footer({
    links: {
      GitHub: "https://github.com/xyz/xyz.git",
      //"Discord Community": "https://discord.gg/xyz",
    },
  }),
}
```
### remove footer
Return `<></>` from `quartz/components/Footer.tsx`

