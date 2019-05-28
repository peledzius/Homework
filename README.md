# Homework
Please FORK this repository before proceeding with task! After completion, send a link to your public repository.

Write a "proxy" program: 
* You have to continuously read input from file: \\remote_server\share\file.txt, one line at a time and remove that line after reading. This must happen in 1 second intervals until the file is empty. 
* You need to check each line for a particular pattern, and then write that line to output file: \\remote_server2\share\file.txt
* If the line contains a pattern “ZZ.ZZ.ZZ” anywhere except at the very end, it means the very next line has to be reversed (backwards) before writing to destination;
* Problem is, output destination \\remote_server2\share\file.txt is connected via unreliable link and is intermittently unavailable for very short periods of time (usually no more than few seconds);
* You are not allowed to lose any text;
* Input side is very sensitive and must not notice any increase in latency (program cannot stall) when destination is unavailable. Reading must happen in stable 1s intervals regardless of availability of the destination;
* You are not allowed to read entire file at once, you must check every line for a pattern before reading the next one;
* You must write to the destination as often as possible (and as soon as it becomes available after interruption) in a sequence messages were read from source;
* You do not have access to any local storage to use as a cache (program must do all its work in RAM);
* Since latency is critical, your program has to be as resource-efficient as possible

Example input file.txt is inside this repository.
