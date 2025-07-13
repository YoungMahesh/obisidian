
**HTTP** stands for **HyperText Transfer Protocol**.  
It is the foundational protocol used for transferring data on the World Wide Web.  
HTTP defines how messages are formatted and transmitted, and how web servers and browsers should respond to various commands.

---

## 2. HTTP Versions

### **a. HTTP/0.9**
- **Year:** 1991
- **Features:** Very simple, only supported GET method, no headers, no status codes.
- **Usage:** Obsolete.

### **b. HTTP/1.0**
- **Year:** 1996
- **Features:** Introduced headers, status codes, and more methods (POST, HEAD).
- **Limitation:** Each request opens a new TCP connection (inefficient).

### **c. HTTP/1.1**
- **Year:** 1997 (RFC 2068, updated in RFC 2616)
- **Features:**
  - Persistent connections (keep-alive)
  - Chunked transfer encoding
  - Pipelining (limited use)
  - More cache control mechanisms
- **Status:** Still widely used.

### **d. HTTP/2**
- **Year:** 2015 (RFC 7540)
- **Features:**
  - Binary protocol (not text-based like 1.x)
  - Multiplexing (multiple requests/responses in one connection)
  - Header compression (HPACK)
  - Server push
- **Benefits:** Faster, more efficient, reduces latency.

### **e. HTTP/3**
- **Year:** 2022 (RFC 9114)
- **Features:**
  - Uses QUIC protocol (instead of TCP)
  - Even lower latency, better performance on unreliable networks
  - Built-in encryption (TLS 1.3)
- **Status:** Rapidly being adopted by major browsers and servers.

---

## 3. Protocols Used by HTTP

### **a. Underlying Transport Protocols**
- **HTTP/0.9, 1.0, 1.1, 2:** Use **TCP** (Transmission Control Protocol) as the transport layer.
- **HTTP/3:** Uses **QUIC** (Quick UDP Internet Connections), which is built on **UDP** (User Datagram Protocol).

### **b. Security Protocols**
- **HTTP:** Unencrypted (plain text)
- **HTTPS:** HTTP over **TLS/SSL** (Transport Layer Security / Secure Sockets Layer)
  - **HTTPS** is the secure version of HTTP, encrypting data between client and server.

---

## 4. Summary Table

| Version   | Year  | Transport | Security | Key Features                        |
|-----------|-------|-----------|----------|-------------------------------------|
| HTTP/0.9  | 1991  | TCP       | None     | Simple GET, no headers              |
| HTTP/1.0  | 1996  | TCP       | Optional | Headers, status codes, POST/HEAD    |
| HTTP/1.1  | 1997  | TCP       | Optional | Persistent connections, chunked     |
| HTTP/2    | 2015  | TCP       | Optional | Binary, multiplexing, compression   |
| HTTP/3    | 2022  | QUIC/UDP  | Built-in | Faster, lower latency, always secure|

---

**In summary:**  
- HTTP is the protocol for web communication.
- It has evolved from simple (0.9) to advanced (3) versions.
- It uses TCP (except HTTP/3, which uses QUIC/UDP).
- Security is provided by HTTPS (HTTP over TLS/SSL).