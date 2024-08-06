### 1. 允许使用默认参数

lambda 表达式的参数列表可以使用默认参数（C++11 之后的标准），如下代码的执行结果是1。

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << [](int a = 1) { return a; }();

    return 0;
}
```

细心的读者可以看到，我在 lambda 表达式后面加上了 `()`，这表示调用该 lambda 表达式。如果不加上 `()`，就不能产生返回值给 `cout`，然后 `cout` 会尝试打印一个**函数对象**，从而导致编译错误（在某些编译器中做了优化，会编译通过并输出调用的结果，这实际上是不严谨的，在 visual studio 的环境中是不能通过的）。

但是也不要简单地认为 lambda 表达式就是没有名称的函数，它实际上是被编译器转化为一个匿名类（anonymous class）的**实例**，这个类包含了 lambda 的捕获环境（capture context）、状态（如果有的话）以及一个重载的函数调用运算符（`operator()`）。这个匿名类的实例可以存储在不同的存储区域，具体取决于 lambda 表达式的使用情况。

所以，在你需要 lambda 表达式返回值的地方，请加上 `()` 来调用它。

### 2. 可以通过关键字 `auto` 给 lambda 表达式定义别名，并通过 `别名()` 的方式调用



### 3. 可以直接访问并修改全局变量以及静态局部变量

lambda 表达式的函数体可以直接访问（不需要捕获）并修改**全局变量**（静态或者非静态）以及**静态局部变量**，但且修改**会影响表达式外部**的变量。下面代码的执行结果是：，变量 `a` 和 `b` 的值被修改了。

```cpp
#include <iostream>
using namespace std;

int a = 0;  // Global variable.
int main()
{
    static int b = 0;   // Static local variable.
    cout << "Before" << endl;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    []() { ++a; return a; }();  // Expression 1 modifies the value of a.
    []() { ++b; return b; }();  // Expression 2 modifies the value of b.

    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    return 0;
}
```

### 4. 对于非静态局部变量，值捕获的变量值在表达式定义时确定，引用捕获的变量值在表达式调用时确定

对于非静态局部变量，值捕获的变量值在表达式定义时确定，只要不修改，该**值就是固定的**；引用捕获的变量值在表达式调用时确定，如果在某次调用前该变量被修改过，会同样影响到 lambda 表达式中的变量值。其实就可以理解为，值捕获的变量是在函数中创建了一个**副本**，而引用捕获的变量是在在函数中声明了外部变量的一个**引用**。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    // value capture of variable a, reference capture of variable b.
    auto fun = [a, &b]()
    { 
        cout << "a:" << a << endl;
        cout << "b:" << b << endl;
    };

    cout << "Before" << endl;
    fun();
    a = 1;
    b = 1;
    cout << "\nAfter" << endl;
    fun();

    return 0;
}
```

上述代码的执行结果是：![image](https://github.com/user-attachments/assets/2496afad-1fc1-4140-8a76-a810d0adef53)。可以看到，两次调用后，变量 `a` 的值没有发生变化，而由于变量 `b` 是引用捕获的，所以两次调用结果不一致。

### 5. 对于非静态局部变量，通过值捕获到的变量是常量，修改需要加上 mutable 关键字

对于非静态局部变量，lambda 表达式通过值捕获到的变量，默认是一个**只读变量（常量）**，即便它是拷贝的副本，也不能进行修改。需要加上 `mutable` 关键字后才能进行修改，而且修改的也只是表达式内的副本，并不是外部变量。如下代码的执行结果是：![image](https://github.com/user-attachments/assets/78b2a01a-f0a1-4f8d-bea9-75144afbd34e)
。


```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    // value capture of variable a.
    cout << "Before" << endl;
	
    auto fun = [a]() mutable {  a = 1; return a; };

    cout << "a:" << a << endl;
    fun();
    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;

    return 0;
}
```

### 5. 对于非静态局部变量，通过引用捕获到的就是引用，可以直接修改

对于非静态局部变量，lambda 表达式通过引用捕获到的变量，就是外部变量的引用，可以直接修改，会同时影响到外部变量。下面代码的执行结果是：![image](https://github.com/user-attachments/assets/cb3af06b-16ca-4edb-969a-63d54975f667)。


```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    cout << "Before" << endl;
    cout << "a:" << a << endl;
    auto fun = [&a]() {  a = 1; };
    fun();
    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;

    return 0;
}
```
