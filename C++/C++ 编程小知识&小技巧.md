# 1 ��ν��ڴ���е����ݿ����� `string` ������

����ָ���ڴ���ָ��Ϊ `p`����С�� `size`��`string` ����Ϊ `str`��

## 1.1 ���ַ�����

```cpp
str.resize(size);
for (int i = 0; i < size; ++i)
    str[i] = *(p + i);
```
## 1.2 ʹ�� `std::string::data()`

�� C++17 ��ʼ��ͨ�� `std::string::data()` ���������Եõ�һ��ָ�� `std::string` ���ڲ���������**�ǳ���ָ��**���Ӷ����Խ����ݰ�ȫ��д�롣

```cpp
str.resize(size);
memcpy(&str[0], p, size);   // ʹ�� &str[0] ����ȡ�ַ����������ķǳ���ָ��
```

ע�����ﲻ��ʹ�� `str.c_str()`�������ص��� `const` ָ�룬�����޸ģ�

## 1.3 ʹ�� `std::string::assign()`

`std::string::assign()` ���Զ����� `str` �Ĵ�С������ָ����**�ֽڿ飨����ָ����ʼ��ַ��ĩβ��ַ��** �������ַ����������С�

```cpp
str.assign(p, p + size);    // ͨ����ʼ��ַ��ĩβ��ַ�����ֽڿ�
// ����
str.assign(p, size)         // ָ����ʼ��ַ���ֽڿ��С
```

## 1.4 ʹ�� `std::copy()`

�÷���Ҳ��Ҫָ���ֽڿ飬���ṩ `str` ���׵�������

```cpp
str.resize(size);
std::copy(p, p + size, str.begin());
```

## 1.5 ʹ�� `std::string::append()`

���� `std::string::append()` ���������ַ���ĩβ׷���ַ���

```cpp
str.append(p, size);
```

# 2 `cout` ��ô��ӡָ���ֵ

`cout` ������ `printf` һ�������ָ�����ݵĴ�ӡ��ʽ������ `cout` �� << ��������������أ����� `cout` ����ֱ�Ӵ�ӡָ���ֵ��Ҫ���ӡ����Ҫ��ָ��ת���� `void*` ���͡�

```cpp
// ��ӡ�����ַ
char p[0x10] = { 'a', 'b', 'c' };
cout << (void*)p;
// ��ӡ string �����ַ
std::string s = "abc";
cout << &s;
```