#encryption 


## symmetric encryption
- one key does both: encrypt + decrypt
- fast
	- run extremely fast on CPUs, often hardware-accelerated (AES-NI)
	- Complexity: roughly linear in data size
	- use algorithms like: bitwise XOR, shifting/rotations, substitution boxes, simple matrix operations
	- Encrypting 1 GB with AES is under a second.
- used for files, disk encryption, VPN tunnels

### algorithms
- AES (2001)
- ChaCha20 (2014)

## asymmetric encryption
- uses a key-pair
	- public key -> encrypt
	- private key - decrypt
- slower because it works with heavy math that computers struggle with
	- Complexity: thousands of times heavier per operation.
- used for key exchange, signature

### algorithms
- RSA (1977)
	- older, slower, but widely supported
	- rely on
		- huge (2048-4096 bit) integers
		- modular exponentiation
		- prime-factorization related hardness
- ECC (Elliptic Curve Cryptography) 
	- A family of asymmetric algorithms that use math on elliptic curves
	- much faster and uses smaller keys than RSA
	- Curve25519 <- specific curve
		- 25519 represents `2^255 - 19`
			- this is prime number
			- using prime number that looks like `2^n - small_number` gives two benefits:
				- computers love numbers that are near powers of two
					- adding, multiplying, reducing modulo the prime
					- these operations become extremely efficient because the math lines up nicely with CPU word sizes
				- easy to implement/code/remember
		- Ed25519 -> digital signatures
			- used in SSH keys, GPG, etc
	- rely on
		- elliptic curve point multiplication
		- finite field arithmetic

## hybrid encryption
- combine both symmetric and asymmetric encryption 
### algorithms

- HTTPS
	- when user open an HTTPS website, browser gets server's public key
	- It uses that public key to securely send a one-time random symmetric key
	- All data (HTML, video, API calls, images, etc) is encrypted using AES or ChaCha20 which is very fast
- [[GPG]]
	- RSA + AES  + packet structure
## key derivation

### algorithms
- bcrypt
- scrypt
- Argon2


