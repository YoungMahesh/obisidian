# App router

### default caching on server-components

- pages get pre-rendered during build, so if you put you are calling `new Date()` in component, the date remains same (equal to time at which build happened)
- this default behaviour (caching behavior) is called as static rendering
- to opt out, activate dynamic rendering

### dynamic rendering

- get some data from the incoming request and dynamic rendering will be activated

```ts
import { cookies } from "next/headers";
export default function Page() {
  cookies(); // this line will activate dynamic-rendering as we are reading cookies from incoming request
}
```

### dynamic imports or lazy loading

Next.js provides the next/dynamic function, which is a wrapper around React's lazy() and Suspense.
This function works seamlessly in both the App Router and the Pages Router.

```tsx
// sometimes if we import dynamic-component from node_module directly, we get module-not-found error
// in this case, import componet from node_module in separate file and import component dynamically from that file

// MyDocument.tsx
import { PDFDownloadLink } from "@react-pdf/renderer";
export { PDFDownloadLink };

// page.tsx
'use client'
import dynamic from "next/dynamic";
const PDFDownloadLink = dynamic(
  () => import("./MyDocument").then((mod) => mod.PDFDownloadLink),
  {
    ssr: false,
    loading: () => <p>Loading document...</p>,
  },
);
```

### route handlers

- Route handlers are functions that are executed when a user accesses a specific route on a website
