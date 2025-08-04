#auth

- https://clerk.com/


### remember
- use `auth()` instead `currentUser()` for session authentication
	-  `auth()` - 
		- does not make a backend API call for user details—so it doesn't contribute to API rate limits
		- is ideal when you just need to know if a user is authenticated without needing their user profile data
		- in nextjs, it use `import { cookies } from 'next/headers'` to store session-data
	- `currentUser()` 
		- Makes a backend API request and counts toward Clerk's API rate limits. 
		- use this only in server environments when you need deep user details, e.g. email-address, phone-number, etc
		- ref: https://clerk.com/docs/references/nextjs/current-user
		- `import {cache} from 'react'` can help reduce backend-api calls by wrapping `currentUser()` with `cache()`
			- ref: https://github.com/clerk/javascript/issues/4894
### change domain

- update domain and DNS records in dashboard.clerk.com -> project -> configure/Developers/Domains/DNS
- update clerk API keys in .env file