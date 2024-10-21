# CSCE 412 Project 3 - Load Balancer

## Overview
This project implements a load balancer in C++ designed to efficiently distribute incoming network requests across multiple servers. The load balancer dynamically scales the number of servers based on the current load, ensuring optimal performance and resource utilization.

## Features
- **Dynamic Scaling:** Adjusts the number of servers based on request volume.
- **Thread Management:** Each server is represented as a separate thread.
- **Load Distribution Algorithms:** Supports various algorithms for load distribution (e.g., round-robin, least connections).
- **Real-time Monitoring:** Monitors server health and performance metrics.
- **User-friendly Interface:** Provides a simple command-line interface for configuration.

## Getting Started

### Prerequisites
- C++11 or later
- The G++ compiler
- CMake (optional, for build configuration)

### Installation
Clone the repository:
   ```bash
   git clone https://github.com/simonvaradaraj/csce-412-proj3.git
   ```


### Usage
To run the load balancer and view logs, execute the following commands:
```bash
make main
./main.exe > out.txt
make clean
 ```

## License
This project is licensed under the MIT License