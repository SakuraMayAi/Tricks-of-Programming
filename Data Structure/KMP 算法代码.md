本文主要是

```cpp
/**
 *  @brief  获取字符串 s 的 next 数组。
 *
 *  @param next	前缀数组，元素为 int 类型。next[i] 表示子区间 [0, i] 的最长公共前后缀的长度。
 *  @param s    模式串，string 对象。
 * 
 *  @note   确保 next 数组的大小等于模式串 s 的长度。
 */
void getNext(vector<int>& next, const string& s)
{
    int j = 0;    // j 指向后缀的最后一个字符
    next[0] = 0;
    for (int i = 1; i < s.size(); ++i)    // i 指向前缀的最后一个字符
    {
        while (j > 0 && s[j] != s[i])
            j = next[j - 1];
        if (s[j] == s[i]) ++j;
        next[i] = j;
    }
}

/**
 *  @brief  找出并返回模式串 s1 在主串 s2 中第一次出现的位置。
 * 
 *  @param s1   主串，string 对象。
 *  @param s2   模式串，string 对象。
 *  @return 返回模式串 s2 在主串 s1 中第一次出现时的索引值，如果 s2 不在 s1 中就返回 -1。
 */
int KMP(const string& s1, const string& s2)
{
    if (s2.size() == 0) return 0;
    vector<int> next(s2.size());
    getNext(next, s2);
    int j = 0;
    for (int i = 0; i < s1.size(); ++i)
    {
        while (j > 0 && s1[i] != s2[j])
            j = next[j - 1];
        if (s1[i] == s2[j]) ++j;
        if (j == s2.size())
            return (i - s2.size() + 1);
    }

    return -1;
}
```
