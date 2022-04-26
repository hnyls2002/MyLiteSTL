### 哈希函数

`std::hash<Key>`:std默认哈希函数，返回值在`size_t`范围内。

`std::equal_to<Key>`:判断两个值是不是相等的。

### 数组的扩容

- 两倍的时候扩容
- 数据删除的时候不减少数组大小

### 动态申请内存

- 指针`type *`和`new type`应该是对应的。

```c++
type* = new type;
```

- 可以一次申请连续内存，返回首地址

```c++
type *= new type[100];
```

- 连续申请的内存用`delete []`来释放。

```c++
delete []type;
```

### `pass 'classname' as 'this' argument discards qulifiers`

`const`对象调用了`non-const`函数，缺少`const`限定符。

***

## 写这一类容器的通用方式(`map,hash_map`)

### `value_type`的存储

- 为了防止没有默认构造函数的问题，一般`value_type`用指针的形式来储存。
- `typedef pair<type1,type2> value_type;`
- `value_type *data`;

### 链表的边界，存储结构，`nil`节点
- 为了保证删除的复杂度是`O(1)`的，一般要存成**双向链表**的形式。
- 注意顺序表没有找到是返回`nil`，`hash_table`没有找到是返回`nullptr`，此处应该统一成`nullptr`，表示`end()`指针。**所以以后尽量不用哨兵！！！**

### `const`问题
- 注意就好了。