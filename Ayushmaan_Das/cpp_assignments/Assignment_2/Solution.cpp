/* ISSUE FOUND:
- Line which is creating issue is line 13: std::swap(s1[i], s1[n - 1]);
- s1[i] is swapped with s1[n - 1], the last character of the string.
- Only the first character being swapped multiple times with the last character, other parts are untouched .

SOLUTION:
Instead of s1[i], we have to use s1[n - 1 - i] (opposite poles, not always the end only)
 */
#include <iostream>
#include <string>

int main()
{
    std::string s1 = "debugging";
    int n = s1.length();
    for (int i = 0; i < n / 2; i++)
    {
        //  CORRECTION IS MADE HERE:
        std::swap(s1[i], s1[n - 1 - i]);
    }
    std::cout << s1 << std::endl;
    return 0;
}
