# SysPulse ⚡

A lightweight terminal-based system monitoring tool built in C++ that provides real-time insights into CPU, RAM, GPU, disk, network, and system information.

SysPulse is designed to be a fast, minimal, and dependency-free alternative for users who want to monitor their Linux system resources directly from the terminal.

## 🚀 Features

### CPU Monitoring
- Real-time CPU usage calculation
- Reads CPU information directly from `/proc/stat`
- Displays CPU utilization percentage

### Memory Monitoring
- RAM usage monitoring
- Total, used, and available memory information
- Reads memory statistics from `/proc/meminfo`

### GPU Monitoring
- GPU detection
- Supports GPU information extraction
- NVIDIA GPU monitoring through `nvidia-smi` //working on it 
- AMD GPU support

### Disk Monitoring
- Disk usage statistics
- Storage information monitoring
- Displays disk utilization

### Network Monitoring
- Network interface monitoring
- Receive and transmit data statistics
- Reads network information from `/proc/net/dev`

### System Information
- System uptime monitoring
- Basic hardware information
- Lightweight resource usage tracking

## 📸 Preview

(Add terminal screenshots here)

## 🛠️ Technologies Used

- **C++17**
- Linux `/proc` filesystem
- File handling (`fstream`)
- System command execution
- Terminal UI (ncurses - planned/in development)


## ⚙️ Installation

### Clone Repository

```bash
git clone https://github.com/yourusername/SysPulse.git

navigate the project 
 bash cd SysPulse

 Compile
 make 
