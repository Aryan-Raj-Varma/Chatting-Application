# Chatting-Application

# Chatting Application - Server (Socket Programming in C)

## 📌 Project Overview

This is the implementation of a simple **Chatting Application** using **TCP socket programming in C**. The server handles client connections, receives messages, and sends responses over a network using the socket API.

This project is ideal for understanding:
- TCP/IP communication
- Multi-client handling (if extended with threads or `select`)
- Basic socket functions like `socket()`, `bind()`, `listen()`, `accept()`, `recv()`, and `send()`

---

## ⚙️ Features

- Listens for client connections on a specified port.
- Receives messages from the client and prints them to the server terminal.
- Sends responses typed by the server operator back to the client.
- Graceful shutdown on client disconnection.

---

## 🖥️ Technologies Used

- **Language**: C
- **Concepts**: TCP Sockets, System Calls, Networking
- **Platform**: Linux (recommended for `socket.h` compatibility)

---
