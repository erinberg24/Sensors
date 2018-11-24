# Sensors
The “distributed” Sensor Problem using Threads and Mutex/Conditional Variables

This program simulates the notion of several "distributed" temperature sensors that feed data to a single source. Each sensor (thread) is responsible for updating a place in a linked list of temperatures initialized by the parent program (the single source). The temperatures can be positive, negative or zero positive.
The main thread creates a global linked list, then creates all the sensor threads (the number of sensors, and thus threads, can be an argument passed on the command line to main or read in by main from the user) one by one and passes to each sensor thread a struct that contains an integer seed for the random number and an ID number. 
When all the threads complete a cycle (which is placing the temperature in the linked list),  the main thread prints each temperature in the linked list of temperatures and the average temperature. Each thread does this 10 times and terminates. However, each thread can only put a number in the shard linked list only ONCE during each of the 10 cycles. T

There could have been race conditions as each thread attempts to access the shared linked list. I used a mutex to ensure that the linked list is updated correctly. 
