### 1. COMPILE AND OBSERVE THE OUTPUT OF THE ACTUAL SOURCE CODE.
  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1> g++ -g Assignment_1 -o ass1  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1> ./ass1  
  
6 2    
5 3  
6 2    
7 1    
  
### 2. DEBUG THE CODE.  
  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1> gdb ass1    
  
#### a. Set breakpoints and start the execution  
  
(gdb) b main  
Breakpoint 1 at 0x1400016bc: file Assignment_1.cpp, line 48.  
(gdb) b 50  
Breakpoint 2 at 0x14000171c: file Assignment_1.cpp, line 50.  
(gdb) b 25  
Breakpoint 3 at 0x1400014db: file Assignment_1.cpp, line 26.  
(gdb) b 27  
Breakpoint 4 at 0x1400014e0: file Assignment_1.cpp, line 27.  
(gdb) b 44  
Breakpoint 5 at 0x14000167e: file Assignment_1.cpp, line 44.  
(gdb) b 52  
Breakpoint 6 at 0x140001761: file Assignment_1.cpp, line 52.  
(gdb) r  
Starting program: C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1\ass1.exe  
[New Thread 25928.0x1524]  
[New Thread 25928.0x4ac]  
[New Thread 25928.0x3938]  
  
Thread 1 hit Breakpoint 1, main () at Assignment_1.cpp:48  
48          long a[] = {6,5,7,5,5,6};  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 2, main () at Assignment_1.cpp:50  
50          vector<pair<long, long>> v2 = sortWithFrequency(v1);  
(gdb) p v1  
$1 = std::vector of length 6, capacity 6 = {6, 5, 7, 5, 5, 6}  
(gdb) c  
Continuing.  
  
#### b. Analyse the sortWithFrequency function and the while loop inside it.  
  
Thread 1 hit Breakpoint 3, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:26  
26          while (i < v1.size()) {  
(gdb) p v1  
$2 = std::vector of length 6, capacity 6 = {6, 5, 5, 5, 6, 7}  
(gdb) c  
Continuing.  
  
##### Inference : Sort the vector v1 only begins at 1, which exclude the 0<sup>th</sup> index value.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$3 = std::vector of length 0, capacity 0  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$4 = std::vector of length 1, capacity 1 = {{first = 6, second = 2}}  
(gdb) c    
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$5 = std::vector of length 2, capacity 2 = {{first = 6, second = 2}, {first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$6 = std::vector of length 2, capacity 2 = {{first = 6, second = 2}, {first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$7 = std::vector of length 2, capacity 2 = {{first = 6, second = 2}, {first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;  
(gdb) p v2  
$8 = std::vector of length 3, capacity 4 = {{first = 6, second = 2}, {first = 5, second = 3}, {first = 6,       
    second = 2}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 5, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:44  
44          return v2;  
(gdb) p v2  
$9 = std::vector of length 4, capacity 4 = {{first = 6, second = 2}, {first = 5, second = 3}, {first = 6,       
    second = 2}, {first = 7, second = 1}}  
(gdb) c  
Continuing.  
  
##### Inference : Sorting the vector of pair values based on the frequency also not included the 0<sup>th</sup> index value.
  
Thread 1 hit Breakpoint 6, main () at Assignment_1.cpp:52  
52          for (int i =0; i != v2.size(); i++) {  
(gdb) p v2  
$10 = std::vector of length 4, capacity 4 = {{first = 6, second = 2}, {first = 5, second = 3}, {first = 6,      
    second = 2}, {first = 7, second = 1}}  
(gdb) c  
Continuing.  
6 2  
5 3  
6 2  
7 1  
[Thread 25928.0x4ac exited with code 0]  
[Thread 25928.0x1524 exited with code 0]  
[Thread 25928.0x3938 exited with code 0]  
[Inferior 1 (process 25928) exited normally]  
(gdb) q  
  
#### c. Changes to be needed.
  
##### Line 24 : sort(v1.begin(), v1.end());
  
##### Sorting the vector should be done from the starting index.
  
##### Line 28 :  if (v2.size() == 0 || v2[v2.size()-1].first != v1[i])
  
##### Combine the if and else part and remove the increment of i and continue statments to avoid redundancy
  
##### Line 43 : sort(v2.begin(), v2.end(),  comparecount);
  
##### Sorting the vector of pair values should also be done from the starting index.
  
##### Line 51 : vector<pair<long, long>>::iterator it = v2.begin();
  
##### Remove this line because it does not used anywhere
  
#### d. Log details of the modified code.
  
Thread 1 hit Breakpoint 1, main () at Assignment_1.cpp:40  
40          long a[] = {6,5,7,5,5,6};  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 2, main () at Assignment_1.cpp:42  
42          vector<pair<long, long>> v2 = sortWithFrequency(v1); // Remove unused line  
(gdb) p v1  
$1 = std::vector of length 6, capacity 6 = {6, 5, 7, 5, 5, 6}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 3, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:26  
26          while (i < v1.size()) {  
(gdb) p v1  
$2 = std::vector of length 6, capacity 6 = {5, 5, 5, 6, 6, 7}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$3 = std::vector of length 0, capacity 0  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$4 = std::vector of length 1, capacity 1 = {{first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$5 = std::vector of length 1, capacity 1 = {{first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$6 = std::vector of length 1, capacity 1 = {{first = 5, second = 3}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$7 = std::vector of length 2, capacity 2 = {{first = 5, second = 3}, {first = 6, second = 2}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 4, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:27  
27              pair<long,long> p;   // Remove redundant codes  
(gdb) p v2  
$8 = std::vector of length 2, capacity 2 = {{first = 5, second = 3}, {first = 6, second = 2}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 5, sortWithFrequency (v1=std::vector of length 6, capacity 6 = {...})  
    at Assignment_1.cpp:36  
36          return v2;  
(gdb) p v2  
$9 = std::vector of length 3, capacity 4 = {{first = 5, second = 3}, {first = 6, second = 2}, {first = 7,       
    second = 1}}  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 6, main () at Assignment_1.cpp:43  
43          for (int i =0; i != v2.size(); i++) {  
(gdb) p v2  
$10 = std::vector of length 3, capacity 4 = {{first = 5, second = 3}, {first = 6, second = 2}, {first = 7,      
    second = 1}}  
(gdb) c  
Continuing.  
5 3  
6 2  
7 1  
[Thread 12464.0x4228 exited with code 0]  
[Thread 12464.0x3fd0 exited with code 0]  
[Thread 12464.0x47d4 exited with code 0]  
[Inferior 1 (process 12464) exited normally]  
(gdb) q  
  
### 3. FINAL OUTPUT
  
IP : long a[] = {6,5,7,5,5,6};  
OP :  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1> ./ass1  
5 3  
6 2  
7 1  
  
IP : long a[] = {6,8,8,5,7,8,5,6,8,7};  
OP :  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_1> ./ass1  
8 4  
5 2  
6 2  
7 2  

