*This project has been created as part of the 42 curriculum by ebansse.*

# minitalk

A tiny client–server messaging program in C that communicates **using only two UNIX signals**, `SIGUSR1` and `SIGUSR2`. The client sends a string to the server one bit at a time, and the server rebuilds it and prints it.

## How it works

```
 client                                   server
   │  'H' = 0 1 0 0 1 0 0 0                 │
   │ ── SIGUSR2 (bit 0) ──────────────────> │  rebuilds the byte bit by bit
   │ <───────────────────── SIGUSR1 (ack) ─ │
   │ ── SIGUSR1 (bit 1) ──────────────────> │
   │ <───────────────────── SIGUSR1 (ack) ─ │
   │              ... 8 bits ...            │  prints 'H'
   │                                        │
   │ ── '\0' (8 × SIGUSR2) ───────────────> │  end of message: prints '\n'
   │ <──────────── SIGUSR2 (message done) ─ │
   ▼  "message received by server"          ▼  waits for the next client
```

- **Encoding:** each character is sent as 8 signals, most significant bit first. `SIGUSR1` means `1` and `SIGUSR2` means `0`.
- **Acknowledgement:** after every bit, the server answers the client with `SIGUSR1`. The client waits for this answer before sending the next bit, so no signal is lost, even on long messages.
- **End of message:** the client sends a final `'\0'` byte. The server prints a newline and answers with `SIGUSR2`. The client then prints `message received by server` and exits.
- **Sender identification:** the server is set up with `sigaction` and `SA_SIGINFO`, so it reads the client's PID from `siginfo_t->si_pid` and knows where to send the acknowledgements.

## Features

- Sends messages of any length (5,000 characters take about one second)
- **Unicode support:** the text is sent byte by byte, so accented letters, emojis and other scripts arrive unchanged (`Ça marche ? 🚀 日本語`)
- The server keeps running and handles several clients one after another, without restarting
- The client confirms when the whole message has been received (bonus)
- Error messages for a wrong number of arguments or a PID with no process

## Build

```bash
make        # builds ./server and ./client (and the bundled ft_printf)
make clean  # remove object files
make fclean # remove object files and binaries
make re     # rebuild from scratch
```

Compiled with `cc -Wall -Wextra -Werror`.

## Usage

Start the server in one terminal. It prints its PID:

```bash
./server
Server PID: 4242
```

Send a message from another terminal:

```bash
./client 4242 "Hello from minitalk! 👋"
message received by server
```

The server prints:

```
Hello from minitalk! 👋
```

## Project structure

| File | Role |
|---|---|
| `server.c` | prints its PID, rebuilds characters from the signals, sends the acknowledgements |
| `client.c` | parses the PID, sends each character bit by bit, waits for each acknowledgement |
| `minitalk.h` | shared includes |
| `printf/` | my ft_printf |

## What I learned

- Handling UNIX signals with `signal()`, `sigaction()` and `SA_SIGINFO`
- Sending signals between processes with `kill()`
- Bitwise operations (`|`, `&`, `~`, `>>`) to encode and decode bytes
- Synchronising two processes with an acknowledgement after each bit, and using `volatile sig_atomic_t` for the flag shared with the signal handler
