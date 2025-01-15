### 1. COMPILE AND OBSERVE THE OUTPUT OF THE ACTUAL SOURCE CODE.  
    
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3> g++ -g Assignment_3.cpp -o ass3  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3> ./ass3  
Enter the rows:  
8  
Enter the cols:  
13  
Enter content  
Enter 1 row:  
0 0 1 0 0 0 0 1 0 0 0 0 0  
Enter 2 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 3 row:  
0 1 1 0 1 0 0 0 0 0 0 0 0  
Enter 4 row:  
0 1 0 0 1 1 0 0 1 0 1 0 0  
Enter 5 row:  
0 1 0 0 1 1 0 0 1 1 1 0 0  
Enter 6 row:  
0 0 0 0 0 0 0 0 0 0 1 0 0  
Enter 7 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 8 row:  
0 0 0 0 0 0 0 1 1 0 0 0 0  
  
Print the group  
0 0 1 0 0 0 0 1 0 0 0 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 1 1 0 1 0 0 0 0 0 0 0 0  
0 1 0 0 1 1 0 0 1 0 1 0 0  
0 1 0 0 1 1 0 0 1 1 1 0 0  
0 0 0 0 0 0 0 0 0 0 1 0 0   
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 0 0 0 0 0 0 1 1 0 0 0 0  
Max area of Island: -2    
  
### 2. DEBUG THE CODE.  
  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3> gdb ass3  
  
#### a. Set breakpoints and start the execution  

(gdb) b main  
Breakpoint 1 at 0x140001828: file Assignment_3.cpp, line 63.  
(gdb) b 82  
Breakpoint 2 at 0x1400019ad: file Assignment_3.cpp, line 83.  
(gdb) b 45  
Breakpoint 3 at 0x140001668: file Assignment_3.cpp, line 45.  
(gdb) b 33  
Breakpoint 4 at 0x140001567: file Assignment_3.cpp, line 33.  
(gdb) info b  
Num     Type           Disp Enb Address            What  
1       breakpoint     keep y   0x0000000140001828 in main() at Assignment_3.cpp:63  
2       breakpoint     keep y   0x00000001400019ad in main() at Assignment_3.cpp:83  
3       breakpoint     keep y   0x0000000140001668 in maxAreaOfIsland  
4       breakpoint     keep y   0x0000000140001567 in dfs(int, int,   
(gdb) r  
Starting program: C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3\ass3.exe  
[New Thread 24464.0x82f8]  
[New Thread 24464.0x8138]  
[New Thread 24464.0x3420]  
  
Thread 1 hit Breakpoint 1, main () at Assignment_3.cpp:63  
63          vector<vector<int>> grid;  
  
#### b. Verify the user input  
  
Thread 1 hit Breakpoint 1, main () at Assignment_3.cpp:63  
63          vector<vector<int>> grid;  
(gdb) c  
Continuing.  
Enter the rows:  
8  
Enter the cols:  
13  
Enter content  
Enter 1 row:  
0 0 1 0 0 0 0 1 0 0 0 0 0  
Enter 2 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 3 row:  
0 1 1 0 1 0 0 0 0 0 0 0 0  
Enter 4 row:  
0 1 0 0 1 1 0 0 1 0 1 0 0  
Enter 5 row:  
0 1 0 0 1 1 0 0 1 1 1 0 0  
Enter 6 row:  
0 0 0 0 0 0 0 0 0 0 1 0 0  
Enter 7 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 8 row:  
0 0 0 0 0 0 0 1 1 0 0 0 0  
  
Thread 1 hit Breakpoint 2, main () at Assignment_3.cpp:83  
83          printIsland(grid);  
(gdb) p grid  
$1 = std::vector of length 8, capacity 8 = {std::vector of length 13, capacity 13 = {0, 0, 1, 0, 0, 0, 0, 1,    
    0, 0, 0, 0, 0}, std::vector of length 13, capacity 13 = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, 
  std::vector of length 13, capacity 13 = {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  std::vector of length 13, capacity 13 = {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
  std::vector of length 13, capacity 13 = {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
  std::vector of length 13, capacity 13 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
  std::vector of length 13, capacity 13 = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
  std::vector of length 13, capacity 13 = {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}}  
(gdb) c  
Continuing.  
  
Print the group  
0 0 1 0 0 0 0 1 0 0 0 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 1 1 0 1 0 0 0 0 0 0 0 0  
0 1 0 0 1 1 0 0 1 0 1 0 0   
0 1 0 0 1 1 0 0 1 1 1 0 0  
0 0 0 0 0 0 0 0 0 0 1 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 0 0 0 0 0 0 1 1 0 0 0 0  
  
#### c. Analyse the DFS Flow.  
  
Thread 1 hit Breakpoint 4, dfs (i=0, j=2, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) p i  
$2 = 0  
(gdb) p j  
$3 = 2  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 3, maxAreaOfIsland (grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:45  
45                      max_number = (max_number + 2 < val) ? val : max_number-5;  
(gdb) p val  
$4 = 1  
(gdb) p max_number  
$5 = 0  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, dfs (i=0, j=7, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) p i  
$6 = 0  
(gdb) p j  
$7 = 7  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 3, maxAreaOfIsland (grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:45  
45                      max_number = (max_number + 2 < val) ? val : max_number-5;  
(gdb) p max_number  
$8 = -5  
(gdb) p val  
$9 = 1  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, dfs (i=1, j=7, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) p i  
$10 = 1  
(gdb) p j  
$11 = 7  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, dfs (i=1, j=8, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) p i  
$12 = 1  
(gdb) p j  
$13 = 8  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, dfs (i=1, j=9, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) p i  
$14 = 1  
(gdb) p j  
$15 = 9  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 3, maxAreaOfIsland (grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:45  
45                      max_number = (max_number + 2 < val) ? val : max_number-5;  
(gdb) p max_number  
$16 = 1  
(gdb) p val  
$17 = 3  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, dfs (i=2, j=1, grid=std::vector of length 8, capacity 8 = {...})
    at Assignment_3.cpp:33  
33          return 1 + dfs(i-1,j,grid) + dfs(i-1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);  
(gdb) n  
[New Thread 24464.0x6548]  
  
##### Inference : In DFS code, the downside is not checked instead of this upside is called 2 times and  improper calculation of max area is found.
  
#### d. Changes to be needed
  
##### Line 45 : max_number = (max_number < val) ? val : max_number;
##### Remove improper max area calculation
  
##### Line 33 : return 1 + dfs(i-1,j,grid) + dfs(i+1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);
##### Replace the 2nd upside checking with the downside checking condition (i-1,j -> i+1,j)
  
### 3. FINAL OUTPUT.

IP :  
  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3> ./ass3  
Enter the rows:  
8  
Enter the cols:  
13  
Enter content  
Enter 1 row:  
0 0 1 0 0 0 0 1 0 0 0 0 0  
Enter 2 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 3 row:  
0 1 1 0 1 0 0 0 0 0 0 0 0  
Enter 4 row:  
0 1 0 0 1 1 0 0 1 0 1 0 0  
Enter 5 row:  
0 1 0 0 1 1 0 0 1 1 1 0 0  
Enter 6 row:  
0 0 0 0 0 0 0 0 0 0 1 0 0  
Enter 7 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 8 row:  
0 0 0 0 0 0 0 1 1 0 0 0 0  
  
OP :  
  
Print the group  
0 0 1 0 0 0 0 1 0 0 0 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 1 1 0 1 0 0 0 0 0 0 0 0  
0 1 0 0 1 1 0 0 1 0 1 0 0  
0 1 0 0 1 1 0 0 1 1 1 0 0  
0 0 0 0 0 0 0 0 0 0 1 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 0 0 0 0 0 0 1 1 0 0 0 0  
Max area of Island: 6  
  
IP :   
  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_3> ./ass3  
Enter the rows:  
8  
Enter the cols:  
13  
Enter content  
Enter 1 row:  
0 0 1 0 0 0 0 1 0 0 0 0 0  
Enter 2 row:  
0 0 0 0 0 0 0 1 1 1 0 0 0  
Enter 3 row:  
0 1 1 0 1 0 0 0 0 0 0 0 0  
Enter 4 row:  
0 1 0 0 1 1 0 0 1 0 1 0 0  
Enter 5 row:  
0 1 0 0 1 1 0 0 1 1 1 0 0  
Enter 6 row:  
0 0 0 0 0 0 0 0 0 0 1 0 0  
Enter 7 row:  
0 0 0 0 0 0 0 1 1 1 1 0 0  
Enter 8 row:  
0 0 0 0 0 0 0 1 1 0 0 0 0  
  
OP :  
  
Print the group  
0 0 1 0 0 0 0 1 0 0 0 0 0  
0 0 0 0 0 0 0 1 1 1 0 0 0  
0 1 1 0 1 0 0 0 0 0 0 0 0  
0 1 0 0 1 1 0 0 1 0 1 0 0  
0 1 0 0 1 1 0 0 1 1 1 0 0  
0 0 0 0 0 0 0 0 0 0 1 0 0  
0 0 0 0 0 0 0 1 1 1 1 0 0  
0 0 0 0 0 0 0 1 1 0 0 0 0   
Max area of Island: 12  