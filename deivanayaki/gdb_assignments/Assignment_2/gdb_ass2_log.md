### 1. COMPILE AND OBSERVE THE OUTPUT OF THE ACTUAL SOURCE CODE.

PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> g++ -g Assignment_2 -o ass2  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> ./ass2

##### gdebgginu

### 2. DEBUG THE CODE.

PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> gdb ass2

#### a. Set breakpoints and start the execution

(gdb) b 11  
Breakpoint 1 at 0x140001470: file Assignment_2.cpp, line 11.  
(gdb) b 15  
Breakpoint 2 at 0x1400014b9: file Assignment_2.cpp, line 15.  
(gdb) info b  
Num     Type           Disp Enb Address            What  
1       breakpoint     keep y   0x0000000140001470 in main() at Assignment_2.cpp:11  
2       breakpoint     keep y   0x00000001400014b9 in main() at Assignment_2.cpp:15  
(gdb) r  
Starting program: PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> 
[New Thread 30684.0x544]  
[New Thread 30684.0x1b78]  
[New Thread 30684.0xa00]  
  
Thread 1 hit Breakpoint 1, 0x00007ff75c841470 in main () at Assignment_2.cpp:11  
warning: Source file is more recent than executable.  
11      int main() {  
(gdb) c  
Continuing.  
  
#### b. Watch the variable i, string s1 to know more about the swapping process.
  
Thread 1 hit Breakpoint 2, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-1]);  
(gdb) watch i  
Hardware watchpoint 3: i  
(gdb) p s1[i]  
$1 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe60: 100 'd'  
(gdb) p s1[n-1]  
$2 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 103 'g'  
(gdb) p s1  
$3 = "debugging"  
(gdb) c  
Continuing.  
  
Thread 1 hit Hardware watchpoint 3: i  
  
Old value = 0  
New value = 1  
0x00007ff75c8414f2 in main () at Assignment_2.cpp:14  
14          for (int i = 0; i < n/2; i++) {  
(gdb) p s1[i]  
$4 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe61: 101 'e'  
(gdb) p s1[n-1]  
$5 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 100 'd'  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 2, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-1]);  
(gdb) p s1  
$6 = "gebuggind"  
(gdb) c  
Continuing.  
  
Thread 1 hit Hardware watchpoint 3: i  
  
Old value = 1  
New value = 2  
0x00007ff75c8414f2 in main () at Assignment_2.cpp:14  
14          for (int i = 0; i < n/2; i++) {  
(gdb) p s1[i]  
$7 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe62: 98 'b'  
(gdb) p s1[n-1]  
$8 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 101 'e'  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 2, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-1]);  
(gdb) p s1  
$9 = "gdbuggine"  
(gdb) c  
Continuing.  
  
Thread 1 hit Hardware watchpoint 3: i  
  
Old value = 2  
New value = 3  
0x00007ff75c8414f2 in main () at Assignment_2.cpp:14  
14          for (int i = 0; i < n/2; i++) {  
(gdb) p s1[i]  
$10 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe63: 117 'u'  
(gdb) p s1[n-1]  
$11 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 98 'b'  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 2, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-1]);  
(gdb) p s1  
$12 = "gdeugginb"  
(gdb) c  
Continuing.  
  
Thread 1 hit Hardware watchpoint 3: i  
  
Old value = 3  
New value = 4  
0x00007ff75c8414f2 in main () at Assignment_2.cpp:14  
14          for (int i = 0; i < n/2; i++) {  
(gdb) p s1[i]  
$13 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe64: 103 'g'  
(gdb) p s1[n-1]  
$14 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 117 'u'  
(gdb) c  
Continuing.  
  
##### Inference : Based on the above log details, i gets incremented by 1 and the i<sup>th</sup> index character always get swapped with the last index character of the string.  
  
##### gdebgginu  
  
Watchpoint 3 deleted because the program has left the block in  
which its expression is valid.  
(gdb) q  
  
#### c. Changes to be needed.

##### i<sup>th</sup> character should be replaced by (n-i-1)<sup>th</sup> character of the string.

##### Line 15 : std::swap(s1[i], s1[n-i-1]);

#### d. Log details of the modified code.

Thread 1 hit Breakpoint 1, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-i-1]);  
(gdb) p s1[i]  
$1 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe60: 100 'd'  
(gdb) p s1[n-i-1]  
$2 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe68: 103 'g'  
(gdb) p s1  
$3 = "debugging"  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 1, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-i-1]);  
(gdb) p s1[i]  
$4 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe61: 101 'e'  
(gdb) p s1[n-i-1]  
$5 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe67: 110 'n'  
(gdb) p s1  
$6 = "gebuggind"  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 1, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-i-1]);  
(gdb) p s1[i]  
$7 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe62: 98 'b'  
(gdb) p s1[n-i-1]  
$8 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe66: 105 'i'  
(gdb) p s1  
$9 = "gnbuggied"  
(gdb) c  
Continuing.  
  
Thread 1 hit Breakpoint 1, main () at Assignment_2.cpp:15  
15              std::swap(s1[i], s1[n-i-1]);  
(gdb) p s1[i]  
$10 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe63: 117 'u'  
(gdb) p s1[n-i-1]  
$11 = (__gnu_cxx::__alloc_traits<std::allocator<char>, char>::value_type &) @0x5ffe65: 103 'g'  
(gdb) p s1  
$12 = "gniuggbed"  
(gdb) c  
Continuing.  
gniggubed  

### 3. FINAL OUTPUT.
  
IP : s1="debugging"  
OP :   
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> ./ass2  
gniggubed  


IP : s1 = "developer"  
OP :  
PS C:\Users\DELL\Documents\FTTU-interns\deivanayaki\gdb_assignments\Assignment_2> ./ass2  
repoleved  
