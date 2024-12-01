# Day 0 - Set up

So it's been a while since I've done any serious programming purely in a compiled language. I will be working in either WSL2 Ubuntu or my Kubuntu depending on the machine I happen to be using at the time. I plan on doing this super bare bones and manually (no CMake/Make for C++) so here are my setup notes:

1. Install `gcc`/`g++`:
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
2. Install Rust: [https://rustup.rs/](https://rustup.rs/)
    ```bash
    curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh
    source ~/.bashrc
    rustup update
    rustc --version
    ```

## Hello worlds

**C++**
```bash
g++ -o hello_world_cpp hello_world.cpp
```

**Rust**
```bash
rustc hello_world.rs
```