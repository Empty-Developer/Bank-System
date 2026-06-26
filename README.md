# Bank System Simulator

Console-based C++ application simulating a multi-threaded banking system with concurrent client operations.

## Requirements

- C++17 compatible compiler
- Thread support (pthread for Linux/Mac, native for Windows)

## Commands

| Command | Description |
|---------|-------------|
| `top N` | Show top N accounts by balance |
| `stats` | Show system statistics |
| `history ID` | Show transaction history for account |
| `balance ID` | Show account balance |
| `help` | Show available commands |
| `quit` | Stop system and exit |

## Architecture

The project follows a **modular monolith** design with **4 core modules**:

| Module | Responsibility |
|--------|----------------|
| **Account** | Single account management (balance, history, per-account mutex) |
| **Bank** | Account registry, transfers, statistics, top-N queries |
| **Client** | Thread client performing random operations |
| **Logger** | Thread-safe file output |


## Contributors

<a href="https://github.com/Empty-Developer/Bank-System/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Empty-Developer/Bank-System" />
</a>

## Algorithms

| Feature | Implementation | Complexity |
|---------|---------------|------------|
| Top-N Accounts | `std::partial_sort` | O(k log N) |
| Transaction History | `std::deque` | O(1) push/pop |
| Account Lookup | `std::unordered_map` | O(1) average |

## Design Patterns

| Pattern | Application |
|---------|-------------|
| **Dependency Injection** | Logger injected into Bank via constructor |
| **Facade** | Bank hides synchronization complexity from Client |
| **RAII** | Automatic mutex management via `lock_guard` / `unique_lock` |
| **Single Responsibility** | Each class has one clear responsibility |
| **Ordered Locking** | Mutexes always acquired in ID order to prevent deadlocks |

## Thread Safety

- **Per-account mutex** - each account has its own mutex
- **Shared mutex** - accounts map with multiple readers, single writer
- **Ordered locking** - always lock smaller ID first (deadlock prevention)
- **Atomic counters** - lock-free statistics increments
- **Atomic stop flag** - safe thread termination

## Quick Start

1. Run `start.bat` to build and launch the application
2. Two consoles will open:
   - **Bank Menu** - for commands input
   - **Bank Logs** - for real-time transaction logs
3. Enter commands in the menu console

## Contributors

<a href="https://github.com/Empty-Developer/Bank-System/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Empty-Developer/Bank-System" />
</a>
