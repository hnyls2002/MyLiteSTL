### `constructor`

一个新的对象被生成，构造这个对象会调用下面的构造函数之一

- `default-constructor`
- `copy-constructor`
- `move-constructor`
- ...

`copy-constructor`和`assignment operator`都会进行复制操作，但深拷贝的时候会进行必要的析构操作，析构的时候如果原来是乱码，那么析构就会出问题，所以一个对象需要时刻保证其内存数据的合法性。

### `placement new`

有的自定义类没有默认构造函数，但我们需要先申请内存，于是便出现了对于一块已经分配的内存我们无法初始化的问题。这块内存既不能用`copy constructor`（要新申请内存），也不能用`assignment operator`（数据乱码）。

`placement new`对象的内存分配、构造给分开。

```c++
new (a) int(init_value)//将init_value初始化给a
```

内容申请用的是`malloc`函数，所以释放必须要用`free`，为了析构，可以显式调用析构函数。