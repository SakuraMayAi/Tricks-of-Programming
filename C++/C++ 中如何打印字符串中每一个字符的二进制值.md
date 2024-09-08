```cpp
#include <iostream>
using namespace std;

int main()
{
    const char* str = "Hello";
    while (*str != '\0')
    {
        unsigned char ch = *str;
        for (int i = 7; i >= 0; i--)
            printf("%d", (ch >> i) & 1);
        printf(" ");
        str++;
    }

    return 0;
}
```
