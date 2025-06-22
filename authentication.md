# architectures

## Basic Authentication

The simplest form where credentials are sent in HTTP headers.
The username and password are concatenated with a colon and encoded in base64.
While easy to implement, it's less secure since credentials are not encrypted

## Token-Based Authentication

**JSON Web Tokens (JWT)** are currently the most widely used authentication method for web applications.
The server creates a JWT containing user information and sends it to the client.
The client then includes this token with each subsequent request.

Cookies have 4KB size limit which can be problematic for larger JWT tokens; hence normally developers use localStorage to store JWT tokens
in user's browser. But cookies can be used to store jwt-tokens.

## Session-based Authentication

During login, server verifies user credentials and create a unique sessionID for user.
This sessionID is act as key in session-table in database whose value stores user-details.
This sessionID is sent as response which is stored as cookie in user's browser.
On every request, user's browser sent this sessionID to server for verification.
Expired sessionIDs are removed from server through cron-job.

## Cookie-Based Authentication

Cookies are created by server.
Cookies came from server get stored in browser automatically with domain of server.
Browser automatically send cookies connected to the domain to the server on each http request.
Cookies are specific to domain and does not get accessed by other domain in browser.
We can set expiration_time for cookies, after which they get deleted from user's browser automatically.
You can view cookies of any site using chrome-extension: cookie-editor

User authentication details are stored as cookie in user's browser which act as authentication session.
Server may or may not store this cookie for verification.

## OAuth and OpenID

- **OAuth 2.0** is used by major platforms like Google, Facebook, and Twitter for delegated access.

- **OpenID** is specifically designed for authentication and works with identity providers like Google, Facebook, WordPress, and PayPal

## Modern Authentication Methods

**WebAuthn** represents the future of authentication, using asymmetric public key cryptography instead of passwords.
It's supported by all major browsers and provides stronger security through:

- Biometric authentication
- Hardware security keys
- Platform authenticators

## Multi-Factor Authentication (MFA)

Combines multiple authentication methods for enhanced security. Common factors include:

- Password-based login
- Biometric verification
- One-time passwords (OTP)
- Email verification

## SAML Authentication

Commonly used in enterprise applications for Single Sign-On (SSO), allowing users to access multiple services with one login.
It uses XML-based assertions containing user identity information that can be signed and encrypted.

# providers

## ClerkJS

- support only metamask, not other web3 wallets
- cannot move user from development to production (need to think about this in future)

## ThirdwebJS

- complex documentation compared to clerk
- bundle too many products in subscriptions
- create a non-custodial wallet, when user sign-in with email
  - private key of which is no accesssible to intrifund, nor to web3 illiterate people
  - in ui connected user can see the private-key, then most probably thirdweb developers have access to the private key
  - no built-in ui like clerk, to connect web3-wallets, phone-number to email

## AuthJS

- takes time for implementation
