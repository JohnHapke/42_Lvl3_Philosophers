# Philosophers - Multithreading and Synchronization Project

## Purpose
> The purpose of the Philosophers project is to create a C program that simulates the classic Dining Philosophers problem, demonstrating understanding of thread synchronization and mutex operations. The program must manage multiple philosopher threads sharing limited resources (forks) while preventing deadlocks and starvation.

## Explanation of Behavior
Philosophers implements a solution to the concurrency problem where multiple philosophers alternate between eating, thinking, and sleeping states while sharing access to forks. The program:

- Creates one thread per philosopher
- Manages shared resources (forks) using mutexes
- Prevents deadlocks while ensuring philosophers don't starve
- Logs each philosopher's state changes with timestamps
- Stops when a philosopher dies or all have eaten enough times

## How It Works

### Initialization
The program receives command-line arguments:
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]`

### Core Simulation
- Philosophers sit at a round table with forks between them
- Each philosopher alternates between:
  - Thinking (no forks needed)
  - Attempting to take two forks (left and right)
  - Eating (holding two forks)
  - Sleeping (releases forks)
  
### Synchronization
- Each fork is protected by a mutex
- Philosophers must acquire both adjacent forks to eat
- The program prevents deadlocks (e.g., via acquisition order)
- Timers ensure philosophers don't starve

### Termination Conditions
- Simulation stops if any philosopher starves (doesn't eat within time_to_die)
- If number_of_meals is specified, stops when all philosophers have eaten enough

## Logging Requirements
The program outputs state changes with timestamps:
- `X has taken a fork`
- `X is eating`
- `X is sleeping`
- `X is thinking`
- `X died`

## Compilation and Usage
1. Compile: Run `make` to build the program
2. Execute: `./philo 5 800 200 200 7` (example with 5 philosophers, each eating 7 times)
3. Output: Displays philosopher states until termination

## Key Concepts
- **Thread Management**: Creating and managing multiple philosopher threads
- **Mutex Operations**: Protecting shared resources (forks) from race conditions
- **Deadlock Prevention**: Ensuring philosophers don't get stuck waiting forever
- **Timing**: Accurate measurement and enforcement of time constraints
- **Synchronization**: Coordinating access to limited resources

## Bonus Part (philo_bonus)
The bonus version implements the same logic using processes and semaphores instead of threads and mutexes, with forks represented by a semaphore in the middle of the table.

## Requirements
- No data races or memory leaks
- Proper error handling
- Strict adherence to output format
- Compliance with project norms

## Grade: tbd/100
