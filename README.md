Rishab Singh -100787473
Rupam Mittal -100640634


# OS_Lab4

## Compilation

The program can be compiled using a single command in the terminal. Navigate to the project directory where the source files are located. You will find a `Makefile` provided for ease of compilation. 

To compile the program, execute the following command:

```bash
make
```


If you prefer not to use Make, you can compile the program manually with the following command:

````
gcc -o dispatcher main.c resource_manager.c queue_manager.c dispatcher.c -I.
````

This command compiles the source files and links them into an executable named dispatcher, ensuring that all dependencies are correctly resolved.

## Execution

To run the dispatcher simulation, follow these steps after compilation:

1. **Launch the Program**: Open your terminal or command line interface and navigate to the directory containing the compiled `dispatcher` executable. Launch the program by entering:

    ```bash
    ./dispatcher
    ```

2. **Enter Dispatch List File Path**: Upon execution, the program will prompt you to enter the path to a dispatch list file. This file contains the definitions of processes that the dispatcher will manage, formatted as follows:

    ```plaintext
    arrival_time, priority, processor_time, memory, printers, scanners, modems, cds
    ```

    An example entry might look like: `0, 1, 10, 128, 1, 0, 1, 0`, where each value represents, in order, the process's arrival time, priority, processor time, memory requirement, and the numbers of printers, scanners, modems, and CD drives it requires.

3. **Provide Dispatch List Path**: Respond to the prompt by typing the path to your dispatch list file. For example, if your file is named `dispatch_list.txt` and located in the same directory as the dispatcher, simply type `dispatch_list.txt` and press Enter.

    ```bash
    Please enter the dispatch list file path: dispatch_list.txt
    ```

4. **Observe Execution**: The dispatcher will process each entry in the dispatch list according to its scheduling and resource allocation algorithms. It will output the execution status of each process, including any resource allocation issues or priority adjustments.
