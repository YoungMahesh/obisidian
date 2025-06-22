### caching

- localStorage (browser api)
- memoization (useMemo, useCallback)
- react cache api (`import {cache} from 'react'`)
  - only to use with react server components
- libraries - react useQuery

### lazy loading

Dynamic imports in React allow you to load components or modules on-demand, improving performance by splitting your code into smaller chunks.

React provides the React.lazy() function to implement dynamic imports easily.

This can be achieved also by using useEffect with useState, so component will be opened only when button is clicked.
