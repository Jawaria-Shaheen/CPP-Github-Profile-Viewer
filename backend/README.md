# C++ GitHub Profile Viewer

A lightweight C++ backend using [cpp-httplib](https://github.com/yhirose/cpp-httplib) 
with OpenSSL to fetch GitHub user profiles and repositories.

## Requirements
- [MinGW-w64 (g++)](https://www.mingw-w64.org/) — C++ compiler for Windows
- [MSYS2](https://www.msys2.org/) — Package manager to install libraries
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) — Header-only HTTP server/client library (included as `httplib.h`)
- [OpenSSL](https://www.openssl.org/) — For HTTPS support when calling GitHub API
```bash
  pacman -S mingw-w64-x86_64-openssl
```
- **Windows SDK libraries** (bundled with MinGW):
  - `ws2_32` — Windows Sockets API
  - `crypt32` — Windows Cryptography API

## Build
```bash
g++ main.cpp -o main -D_WIN32_WINNT=0x0A00 -LC:\msys64\mingw64\lib -IC:\msys64\mingw64\include -lws2_32 -lssl -lcrypto -lcrypt32
```

## Run
```bash
.\main
```

## Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/github?username={username}` | Returns GitHub profile + repositories |

## Response Format
```json
{
  "profile": { ... },
  "repos": [ ... ]
}
```

## Error Responses

| Status | Meaning |
|--------|---------|
| 400 | Missing `username` parameter |
| 404 | GitHub user not found |