# Tamagotchi Server (C)

A client-server Tamagotchi project implemented in C using both UDP and TCP sockets.

This project was developed as a networking and systems programming exercise to explore socket communication, server architecture, and persistent client-server interactions.

## Project Overview

The project was built in three stages:

### 1. UDP Server
Implemented a simple UDP server where:
- the server waits for a message from a client,
- sends a response,
- and immediately closes the communication.

### 2. TCP Server
The project was then extended into a TCP server with:
- reliable communication,
- bidirectional exchanges,
- and persistent client-server connections.

The server accepts incoming client connections and maintains a continuous communication flow.

### 3. Tamagotchi Implementation
To make the project more interactive and creative, a Tamagotchi system was implemented on top of the TCP server.

The virtual pet has several states:
- hunger
- sleep
- happiness

The client can send commands to:
- feed the animal,
- let it sleep,
- play with it.

The server responds with feedback and updates the pet's state over time.

To make the game more dynamic:
- the stats evolve continuously,
- and the animal can die if it becomes too tired or neglected.

## Technologies
- C
- TCP sockets
- UDP sockets
- Client-server architecture
- Linux / POSIX networking

## Build & Run

```bash
make
make server
make client ARGS="127.0.0.1 9600"
