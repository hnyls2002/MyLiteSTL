### 友元函数、友元类

- 友元函数、友元类都是不是这个类的成员。友元函数可以是全局函数，也可以是另一个类的成员函数
- A是B的友元，则A可以访问B的`private`成员和`protected`成员，反之则不行。
- 友元必须在**以它为友元的类中**申明，定义随意。
- 友元的作用域由友元定义的方式决定，全局函数的作用域是全局，类的成员函数（非静态）则只能通过该类的对象调用。
- 友元访问目标类的私有和保护成员，必须通过对对象进行引用，也就是通过函数的参数传递。

***

### `const`相关

- `const_iterator`不能修改容器的值，但是`const_iterator`本身可以`--`，`++`。
- `const_iterator`为什么不可以修改容器的值，是因为`*`的重载和`->`的重载返回的是`const`型。
- `const`型的容器（`map`）只可以申请`const_iterator`，并且要保证除了`insert`和`erase`函数之外的成员函数均有内置`const`属性，即``` ret_type fucntion (arg)cosnt{}```
- `const`型的变量其指针为`const `型，例如`const node *ptr`，同样也可以直接申请`const`指针来限制对对象的修改。值得注意的是，`const `型的指针甚至不能赋值（参数传递）给一个非`const`型的指针，反之不成立。

***

`trivial and non-trivial (for following four types of class-function)` 

- `(default) constructor`
- `deconstructor`
- `copy constructor`
- `assignment operator`

`POD (Plain Old Data)`

>A POD is a type (including classes) where the C++ compiler guarantees that there will be no "magic" going on in the structure: for example hidden pointers to vtables, offsets that get applied to the address when it is cast to other types (at least if the target's POD too), constructors, or destructors. Roughly speaking, a type is a POD when the only things in it are built-in types and combinations of them. The result is something that "acts like" a C type.

`template's specialization`

- `(explict) full template specialization`

  ```C++
  template<typename T1,typename T2,typename T3>
  class{/*...*/};
  //then to explict full specialize it
  template<>
  class<int,int*,double>{/*...*/};
  ```

- `(explict) partial template sepcialization`

  ```C++
  template<typename T1,typename T2,typename T3>
  class{/*...*/};
  //then to explict full specialize it
  template<typename T2>
  class<int,T2,double>{/*...*/};
  ```

类中对数据成员使用`value_type`

```C++
template<typename T>
class my_class{
	typedef T value_type;
};

int main(){
	// then
    my_class<int>::value_type a;
}
```

### C++ 萃取(traits)机制

- 对于一个类型，我们想知道它的一些特性，就需要用到萃取机制，通过定义一个模板类实现。模板类中的`typename`为我们想获得信息的类型，我们想获得的信息用`typedef`来定义出来。
- 值得注意的是，这些标准的**变量**都是通过类来定义的，使用`typedef `或者`using`。

```C++
struct __true_type { };
struct __false_type { };

template <class type>
struct __type_traits//萃取类
{
    typedef __false_type has_trivial_default_constructor;
    typedef __false_type has_trivial_copy_constructor;
    typedef __false_type has_trivial_assignment_constructor;
    typedef __false_type has_trivial_destructor;
    typedef __false_type is_POD_type; // Plain Old Data
};

```

- 我们当然可以直接通过用`my_type`这个已知类型来直接全特化`__type_traits`这个模板类

```asm
template<>
struct __type_traits<my_type> {
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
}
```

- 对于某一类具有相似功能（结构）的类，比如`iterator`，那么我们想知道的信息是公有的，比如：是否可以通过`iterator`修改容器的值、这个迭代器的数据类型是什么，如何对数据类型进行`pointer`和`reference`的操作。
- 那么对于所有的迭代器类，我们在里面预定义这些信息，`iterator_traits`函数就可以直接通过访问`iterator`类中的信息来进行萃取了。

```C++
template<typename my_iterator>
struct iterator_traits {
    typedef typename my_iterator::iterator_category iterator_category;
    typedef typename my_iterator::value_type value_type;
    typedef typename my_iterator::difference_type difference_type;
    typedef typename my_iterator::pointer pointer;
    typedef typename my_iterator::reference reference;
};
```
