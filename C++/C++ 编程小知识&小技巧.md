# 1 如何将内存块中的数据拷贝到 `string` 对象中

假设指向内存块的指针为 p，大小是 size，string 对象为 str。

## 1.1 遍历逐字符拷贝

```cpp
str.resize(size);
for (int i = 0; i < size; ++i)
    str[i] = *(p + i);
```
## 1.2 使用 `std::string::data()`

从 C++17 开始，`std::string::data()` 函数返回一个可修改的指针（与 `std::vector` 类似），可以将内容安全地写入 `std::string` 的内部缓冲区。

```cpp
str.resize(size);
memcpy(&str[0], p, size);   // 使用 &str[0] 来获取字符串缓冲区的非 const 指针
```

注意这里不能使用 `str.c_str()`，它返回的是指向字符串缓冲区的 `const` 指针，不能修改！

## 1.3 使用 `std::string::assign()`

`std::string::assign()` 会自动调整 `str` 的大小，并将指定的**字节块（必须指定起始地址和末尾地址）** 复制到字符串缓冲区中。这种方式比调用 `resize()` 再使用 `memcpy()` 更简洁、安全。

```cpp
str.assign(p, p + size);
// 或者
str.assign(p, size)
```

## 1.4 使用 `std::copy()`

该方法也需要指定字节块，并提供 `str` 的迭代器。

```cpp
str.resize(size);
std::copy(p, p + size, str.begin());
```

## 1.5 使用 `std::string::append()`

调用 `std::string::append()` 函数，在字符串末尾追加字符。

```cpp
str.append(p, size);
```
