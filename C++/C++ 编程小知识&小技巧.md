# 1 ��ν��ڴ���е����ݿ����� `string` ������

����ָ���ڴ���ָ��Ϊ p����С�� size��string ����Ϊ str��

## 1.1 �������ַ�����

```cpp
str.resize(size);
for (int i = 0; i < size; ++i)
    str[i] = *(p + i);
```
## 1.2 ʹ�� `std::string::data()`

�� C++17 ��ʼ��`std::string::data()` ��������һ�����޸ĵ�ָ�루�� `std::vector` ���ƣ������Խ����ݰ�ȫ��д�� `std::string` ���ڲ���������

```cpp
str.resize(size);
memcpy(&str[0], p, size);   // ʹ�� &str[0] ����ȡ�ַ����������ķ� const ָ��
```

ע�����ﲻ��ʹ�� `str.c_str()`�������ص���ָ���ַ����������� `const` ָ�룬�����޸ģ�

## 1.3 ʹ�� `std::string::assign()`

`std::string::assign()` ���Զ����� `str` �Ĵ�С������ָ����**�ֽڿ飨����ָ����ʼ��ַ��ĩβ��ַ��** ���Ƶ��ַ����������С����ַ�ʽ�ȵ��� `resize()` ��ʹ�� `memcpy()` ����ࡢ��ȫ��

```cpp
str.assign(p, p + size);
// ����
str.assign(p, size)
```

## 1.4 ʹ�� `std::copy()`

�÷���Ҳ��Ҫָ���ֽڿ飬���ṩ `str` �ĵ�������

```cpp
str.resize(size);
std::copy(p, p + size, str.begin());
```

## 1.5 ʹ�� `std::string::append()`

���� `std::string::append()` ���������ַ���ĩβ׷���ַ���

```cpp
str.append(p, size);
```
