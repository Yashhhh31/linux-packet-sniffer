# Linux Packet Sniffer (C++)

A Linux-based packet sniffer built using raw socket programming in C++ to capture and analyze live network traffic at the protocol level.

## Features

- Captures live TCP packets
- Extracts source and destination IP addresses
- Extracts source and destination port numbers
- Detects protocol-level traffic
- Identifies HTTPS traffic (port 443)
- Runs on Linux (WSL supported)

## Technologies Used

- C++
- Linux
- Raw Socket Programming
- TCP/IP Networking

## How It Works

The program creates a raw socket and listens for incoming packets.  
It parses IP headers and TCP headers to extract:

- Source IP
- Destination IP
- Source Port
- Destination Port
- Protocol Type

## Run Instructions

Compile:

```bash
g++ sniffer.cpp -o sniffer