# 1 如何将内存块中的数据拷贝到 `string` 对象中

假设指向内存块的指针为 `p`，大小是 `size`，`string` 对象为 `str`。

## 1.1 逐字符拷贝

```cpp
str.resize(size);
for (int i = 0; i < size; ++i)
    str[i] = *(p + i);
```
## 1.2 使用 `std::string::data()`

从 C++17 开始，通过 `std::string::data()` 函数，可以得到一个指向 `std::string` 的内部缓冲区的**非常量指针**，从而可以将数据安全地写入。

```cpp
str.resize(size);
memcpy(&str[0], p, size);   // 使用 &str[0] 来获取字符串缓冲区的非常量指针
```

注意这里不能使用 `str.c_str()`，它返回的是 `const` 指针，不能修改！

## 1.3 使用 `std::string::assign()`

`std::string::assign()` 会自动调整 `str` 的大小，并将指定的**字节块（必须指定起始地址和末尾地址）** 拷贝到字符串缓冲区中。

```cpp
str.assign(p, p + size);    // 通过起始地址和末尾地址划定字节块
// 或者
str.assign(p, size)         // 指定起始地址和字节块大小
```

## 1.4 使用 `std::copy()`

该方法也需要指定字节块，并提供 `str` 的首迭代器。

```cpp
str.resize(size);
std::copy(p, p + size, str.begin());
```

## 1.5 使用 `std::string::append()`

调用 `std::string::append()` 函数，在字符串末尾追加字符。

```cpp
str.append(p, size);
```

# 2 `cout` 怎么打印指针的值

`cout` 不能像 `printf` 一样方便地指定数据的打印格式，而且 `cout` 对 << 运算符进行了重载，所以 `cout` 不能直接打印指针的值。要想打印，需要将指针转换成 `void*` 类型。

```cpp
// 打印数组地址
char p[0x10] = { 'a', 'b', 'c' };
cout << (void*)p;
// 打印 string 对象地址
std::string s = "abc";
cout << &s;
```