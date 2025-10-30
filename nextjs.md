
## errors
### `unhandledRejection: ReferenceError: indexedDB is not define at ignore-listed frames`

- `indexedDB` is part of browser, but somehow it is getting executed on server-side
- if this is happening due to project's component, make that component client component with `"use client"` on top of the file
- if this is happening due to some node_module, then import that component inside client component dynamically with server-side rendering disabled as given below :

```tsx
// providers-wrap.tsx
"use client";
import dynamic from "next/dynamic";
import { ReactNode } from "react";
const Providers = dynamic(
  () => import("./providers").then((mod) => mod.Providers),
  { ssr: false }
);

export default function ProvidersWrap({ children }: { children: ReactNode }) {
  return <Providers>{children}</Providers>;
}
```

```tsx
// providers.ts
// In this file multiple node_modules (e.g. WagmiProvider, RainbowKitProvider) calling indexedDB, hence we imported whole file dynamically in 'providers-wrap.tsx'
import type React from "react";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { WagmiProvider } from "wagmi";
import { RainbowKitProvider } from "@rainbow-me/rainbowkit";
import { config } from "../lib/wagmi";

const queryClient = new QueryClient();
export function Providers({ children }: { children: React.ReactNode }) {
  return (
    <WagmiProvider config={config}>
      <QueryClientProvider client={queryClient}>
        <RainbowKitProvider modalSize="compact">{children}</RainbowKitProvider>
      </QueryClientProvider>
    </WagmiProvider>
  );
}
```

### cookies
- https://nextjs.org/docs/app/api-reference/functions/cookies
- cookies are fundamentally a client-side storage mechanism; cookies are actually stored by the browser, not the server
- Reading cookies works in Server Components because you're accessing the cookie data that the client's browser sends to the server in the HTTP request headers.
