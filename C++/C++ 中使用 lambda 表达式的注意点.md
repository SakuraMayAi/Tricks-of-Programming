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

### 2. 可以通过关键字 `auto` 给 lambda 表达式定义“别名”，并通过 `别名()` 的方式调用

可以将 lambda 表达式赋值给一个对象，`auto` 关键字用于自动推导 lambda 表达式的返回值，此后就可以通过该对象调用 lambda 表达式。如下代码的执行结果是：![image](https://github.com/user-attachments/assets/7b4a5c2b-2018-4a57-905c-37205fb70880)。可以看到，通过 `fun()` 的调用修改了变量 `a` 的值。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    auto fun = [&a]() { ++a; return a; };   // Modify the value of a.

    cout << "\nBefore" << endl;
    cout << "a:" << a << endl;
    fun();
    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;

    return 0;
}
```

### 3. 可以直接访问并修改全局变量以及静态局部变量

lambda 表达式的函数体可以直接访问（不需要捕获）并修改**全局变量**（静态或者非静态）以及**静态局部变量**。如下代码的执行结果是：![image](https://github.com/user-attachments/assets/353504b8-721a-4706-bd14-026a062e0b7e)，可以发现变量 `a` 和 `b` 的值被修改了。

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

对于非静态局部变量，值捕获的变量值在表达式定义时确定，只要不修改，该**值就是固定的**；引用捕获的变量值在表达式调用时确定，如果在某次调用前该变量被修改过，会同样影响到 lambda 表达式中的变量值。其实就可以理解为，值捕获的变量是在函数中创建了一个**副本**，而引用捕获的变量是在函数中声明了外部变量的一个**引用**。如下代码的结果是：![image](https://github.com/user-attachments/assets/2496afad-1fc1-4140-8a76-a810d0adef53)。可以看到，两次调用后，变量 `a` 的值没有发生变化，而由于变量 `b` 是引用捕获的，所以两次调用结果不一致。

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

### 5. 对于非静态局部变量，通过值捕获得到的变量是常量，修改需要加上 mutable 关键字

对于非静态局部变量，lambda 表达式通过值捕获得到的变量，默认是一个**只读变量（常量）**，即便它是拷贝的副本，也不能进行修改。需要加上 `mutable` 关键字后才能进行修改，而且修改的也只是表达式内的副本，并不是外部变量。如下代码的执行结果是：![image](https://github.com/user-attachments/assets/78b2a01a-f0a1-4f8d-bea9-75144afbd34e)
。


```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    auto fun = [a]() mutable {  a = 1; return a; };

    cout << "Before" << endl;
    cout << "a:" << a << endl;
    fun();
    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;

    return 0;
}
```

### 5. 对于非静态局部变量，通过引用捕获到得到的就是引用，可以直接修改

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

### 6. 对于非静态局部指针变量的值捕获，作用等价于引用捕获，可以通过指针修改外部变量的值

在 lambda 表达式中，如果值捕获一个**非静态局部指针变量**，其作用等价于引用捕获，可以通过指针修改外部变量的值。如下代码的执行结果是：![image](https://github.com/user-attachments/assets/f21aabba-2b18-4ad2-8a9c-db6e6a63e7e2)。可以看到，在 lambda 表达式内，*p 修改了外边变量 `a` 的值。


```cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    int* p = &a;

    cout << "Before" << endl;
    cout << "a:" << a << endl;
    [p]() { *p = 1; }();    // Modify the value of a through pointer.
    cout << "\nAfter" << endl;
    cout << "a:" << a << endl;

    return 0;
}
```

在 lambda 表达式中， 给指针 `p` 加不加上引用都是一样的，即将中间的语句换成 `[&p]() { *p = 1; }();` 执行结果不变。

指针变量的本质还是变量，所以对其值捕获和引用捕获，当做普通变量看待即可：
1. 通过值捕获时，得到的是**指针的副本**，所以可以通过副本中的**地址值**，去修改其指向的对象；但是副本和值捕获普通变量得到的一样，都是**只读变量（常量）**，不能修改，只有加上 `mutable` 关键字后才能修改副本的值。
2. 通过引用捕获时，得到的是外部指针的引用。可以直接修改其中保存的地址值，让其指向一个新的对象。但是切记不要轻易让其指向 lambda 表达式中的局部变量，因为在 lambda 表达式调用结束后，其中的局部变量就被销毁了，此时的指针你不知道它指向了何处，甚至有可能导致程序崩溃！

在 lambda 表达式，我们令指针 `p` 重新指向了一个局部变量。其执行结果是：![image](https://github.com/user-attachments/assets/7d6c1871-bbbb-4bc8-97af-957c793dd369)
。可以看出，在调用 lambda 表达式后，指针 `p` 中保存的地址值确实发生了变化。但是打印其中地址指向对象的值就可以发现，预期打印变量 `b` 的值1，结果并不是。这就说明在 lambda 调用结束后，指针 `p` 指向了一个随机的地方。所以切记不要让指针指向局部变量！
