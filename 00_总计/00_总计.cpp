// 00_总计.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
    return 0;
}

//  [6/16/2017 YXP]
// ---------------------------------The More Effictive CPlusPlus-----------------

//3.1 M1:指针和引用的区别:
// 1.引用必须被初始化并且不能指向空值，因此当需要使用一个变量指向一个对象时，
// 如果该变量的值可以改变那么应该申明为指针，否则应该为引用
// 2.不存在空值的问题使得引用的效率更高，使用指针前总应该if(p==null){...}来测试其合法性
// 3.指针可以指向不同的对象，引用不能，只能初始化的时候指定
// 4.重载操作符的时候防止出现语义错误，应该使用引用


//3.2 M2:
// 1.因为传统C风格的不对去掉const和改变对象类型进行区分
// 2.并且不利于阅读，主要是grep等工具不好处理
// 3.static_cast和C风格类型转换一样，除了不能去掉const和从基本类型与引用类型相互转换
// 4.const_cast用于去掉const
// 5.dynamic_cast用于安全的沿着类的继承关系向下进行类型转换，
// 即把基类的指针或引用转换成指向其派生类或兄弟类的指针或引用
// 转换失败会返回空指针或者报异常
// 6.reinterpret_cast用于函数指针之间的转换，但是基本建议少用

//3.3 M3:不要对数组使用多态
// 1.如果对数组使用多态，其地址(由指针计算)还是基类的大小，因此各种操作都可能出错
// 编译器假设数组中元素和基类对象大小一致
// 2.尽量不要从一个具体类派生出另一个具体类能够尽可能避免这个问题

//4.1 M5:谨慎定义类型转换函数
// 1.隐式类型转换函数的声明和定义参见05_01
// 2.proxy ckasses解决方法

//4.2 M6:前置和后置版本的++
// 1.后置版本效率更低，因为要创建临时对象，但是返回的对象是const的，所以禁止使用i++++,但是可以++++i;
// 2.自己的类的increment和decrement应该都根据其前缀形式来实现，便于维护并且效率更好。

//4.3 M7:不要自己重载&&或者||,','
// 1.C++对布尔表达式采取短路求值法，所以自己重载后，调用函数的时候，两个表达式都是注定要被计算的，
// 便不能实现高效的判断了
// 2.对于逗号运算符，其是先运算最左边的再依次往右，但是自行重载的却不能确保能够有这样的效果。
// 3.不能重载的运算符:.	.*	::	?:
//					new	delete	sizof	typeif
//					static_cast等四个转换函数


//4.4 M8:operator new 和 new operator
// 1.new 一个对象的时候，调用的是new operator,这个是系统的操作符，不能修改
// 2.new Widget()的内部会调用operator new,再调用构造函数，所以
//operator new的作用就类似于malloc，负责分配内存，但是完全和构造函数无关
// 3.placement new的作用是对于已经分配好的raw内存，显示调用构造函数构造对象再返回其指针
// 4.如果想要定制堆对象创建的内存分配过程，可以重写operator new

//5.1 M9:使用析构函数防止资源泄露
// 1.资源应该被封装在一个对象里面(比如unique_ptr)，这样，即使报异常的情况下，也不会出现资源泄露
// 因为构造完成的对象，都会经过析构函数

//5.2 M10:在构造函数中防止资源泄露
// 1.如果构造函数过程中报了异常(有一部分内存已经分配，另一部分还没分配)，这时new出来的指针是空值，是无法通过delete删掉的
// 而且对象本身此时也构造失败，不会调用其析构函数。
// 2.解决:面对组合型对象的时候，用unique_ptr代替传统指针，只要任何一部分构造成功了，那么unique_ptr都会调用其析构函数进行delete

//5.3 M11:禁止异常传递到析构函数之外
// 1.在异常转递的过程中，防止terminate被调用(没看懂)
// 2.帮助我们确保析构函数能够完成执行

//M17:考虑使用layzy evaluation
// 1.不需要拷贝的地方就不要拷贝，使用引用
// 2.区别对待读和写
// 3.使用懒惰提取
// 4.懒惰表达式计算

//M18:over-eager evaluation
// 1.如果你认为一个计算需要频繁进行，就可以设计一个数据结构高效的处理这些计算需求，这样可以降低每次计算需求的开销
// 2.比如vector的实现方式，capacity和size是不一样的，每次分配新空间的时候，
// 总是会提前分配两倍当前大小的容量，以备下次使用,这是以空间换时间的做法

//6.4 M19:临时对象的来源搞清楚
// 1.临时对象出现在(1):返回对象值的时候(2):为了是函数成功调用而进行隐式类型转换的时候
// 2.非常量引用进行隐式类型转换是直接被禁止的，常量引用虽然没被禁止(因此可以成功调用)
//，但是不应该用，产生了多余的开销。

//6.5 M20:返回值里的临时对象的优化
// 1.通过在return里面运用constructor argument可以产生优化
// 2.这个没什么好优化的，只能忍受

//6.6 M21:通过重载避免隐式类型转换
// 1.当可能出现隐式类型转换的时候，可以通过重载来避免
// 比如UInt类只有一个int成员的时候，重载+号运算符就可以避免+号的时候出现类型转换
// const UInt operator+(const UInt& lhs,int rhs);

//6.7 M22:尽量用运算符的赋值形式代替其单独形式
// 1.x = x - y和x-=y的区别在于，前者产生返回值，会生成临时对象，因此效率更低
// 2.自定义类型必须显式实现-=这种赋值运算符，光实现了operator-是不行的，两者无关
// 3.operator(stand-alone形式)建议根据assignment version来实现，
// 并且自己在设计类的时候，一定要两者都提供，用户用的时候才能选择
// 比如Rational a,b,c,d; result=a+b+c+d;虽然效率第一点点，但是可读性更好
// 而result+=a;+=b;+=c;...虽然效率高但是不利于维护，因此要让用户自己选择
// 4.返回值里面需要产生新对象的话，尽量用returl constructor(argument);的形式,
// 非命名对象可能能够享受到编译器的优化。
// 5.作为开发者从效率考虑的话，尽量用assignment version

//6.8 M23:当程序性能遇到瓶颈的时候，考虑更换程序库
// 1.iostream 相比于 stdio而言，效率更低，但是类型安全且可扩展


//七:效率
//7.1 M25: