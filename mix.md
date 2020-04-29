# 内存泄漏  
动态分配的堆内存由于某些原因未释放或者无法释放，造成系统内存的浪费，导致程序运行速度减慢甚至系统崩溃等严重后果。  

- 源代码插装  
源代码插装测试必须在静态测试部分获得的被测程序的结构信息、静态数据信息、控制流信息等基础上，应用插装技术向被测程序中的适当位置植入相应类型的探针，通过运行带有探针的被测程序而获得程序运行的动态数据。源代码插装要通过运行被测程序来测定程序的各种指标，如覆盖率、时间性能、内存使用等等。  
实现源代码插装的关键技术是借助于**插入到源程序中的监控语句来收集执行信息**，以达到揭示程序内部行为和特性的目的。

# cookie 和 session  
cookie是保存在客户端的用户数据
session是放在服务端用来跟踪用户状态的信息

# TCP  
- 三次握手
第一次握手 A端发送TCP报文
第二次握手 B端发送TCP报文，A端收到后，知道自己的发送和接收能力正常。但B端只知道自己的接收能力正常  
第三次握手 A端发送TCP报文，B端收到后，知道自己的发送能力正常。连接建立。  

第一二次握手不可以携带数据。防止对服务器的恶意攻击。攻击者在一次握手的报文中放入大量数据，可以使服务器花费很多时间和内存来处理这些报文。  

- 半连接队列  
服务器收到第一次握手的报文后，双方还没有建立完全的连接，把这种状态的客户端放在一个半连接队列里。  
已经完成三次握手的客户端放在全连接队列里。

- SYN攻击  
第一次握手时，攻击者伪造不存在的ip地址，服务器第二次握手后，等待client的第三次握手，不断重发，占用服务器资源。

- 四次挥手
1.A端发送FIN报文
2.B端发送ACK报文
3.B端发送FIN报文
4.A端发送ACK报文  

2和3不能融合。在2时，B端可能尚且存在需要向A端发送的报文，等待这些报文处理完毕，才能进入3。
4之后，A不能立即关闭，需要等待2MSL（maximum segment lifetime）再关闭。
理由：
1. 防止因为最后一个ACK丢失而导致服务器无法正常进入关闭连接状态.
2. 使本连接中的所有报文都从网络中消失，新连接中不会出现旧连接的报文。

# 虚函数
允许通过基类的指针来调用派生类的函数  
实现方式：函数表   

纯虚函数声明 virtual void func() = 0;  
拥有纯虚函数的类为抽象类。抽象类不能定义对象。  
抽象类的派生类必须具体地实现其基类的纯虚函数，否则派生类也是抽象类。

# 友元
friend void func()  
友元函数不是成员函数，但可以访问类中的私有成员。  
友元类的所有成员函数都是另一个类的友元函数。

# 拷贝构造函数

## 调用时机
1. 一个对象以值传递的方式作为函数参数  
2. 一个对象以值传递的方式作为函数返回值  
3. 一个对象用以给另一个对象初始化
## 原因，为什么要使用拷贝构造函数
如果对象中有指针，这时在以上三种情况调用普通的构造方法，  
会使两个指针指向同一块内存。  

``` c++
class Example(){
    Example(const Example& old){
        //code
    }
}
```  
**必须传引用，传值会再次调用拷贝构造函数，无限循环直到栈溢出。**

# 数据库范式

## 1NF
数据库表中每一列都是不可分割的基本数据项
**某个属性不能有多个值**

## 2NF
**表中其他元素都依赖于主键**

属性集C只依赖于**主键的一部分**，可能造成属性集C的数据冗余。那么它不符合2NF

## 3NF

前提：满足2NF

现象：**表中属性集C依赖于非主键属性**
上述现象可能造成属性集C数据冗余。

不存在上述现象即符合3NF
即不存在**依赖传递**  

## BCNF  

BCNF:**每个非平凡FD(Function Dependency)的左边都必须是超键** 
非平凡FD：X -> Y, 其中Y不是X的子集  
**超键**： 唯一标识元组的属性集

**BCNF比3NF更严格**  
例子；关系R存在属性集X,Y，X->Y，且X，Y都属于候选键。
此时R符合3NF，但不符合BCNF。

**3NF消除了主键外的传递依赖，但没有消除涉及主键的传递依赖**

### 异常
1. 冗余
2. 更新异常
信息不一致
3. 删除异常
信息丢失

### 分解
将一个包含异常的关系分解成多个不包含异常的关系
分解算法：
输入：R0和函数依赖集S0
输出：R0分解出的属于BCNF的子集

规定每个关系的全属性集 = T

1. 检查R是否属于BCNF，是就返回R
2. 违例X->Y,计算X<sup>+</sup>,R1=X<sup>+</sup>,R2=T-X<sup>
+</sup>
3. 计算R1和R2的最小函数依赖集
4. 用本算法递归分解R1和R2

2中计算X的闭包X<sup>+</sup>的原因,为了R1的数据一致性和完整性

# LRU换页算法

# 继承

## 子类重写方法的访问权限不能低于父类中访问权限

原因：
class B extends A
```java
void get(A a){
    a.func();
}
```

向get函数传入B类对象，如果B类的func访问权限更严格，可能产生错误。

## 子类重写方法的返回类型必须与父类相同或者是父类返回类型的子类

根本原因与访问权限的限制相同，因为**向上转型**。

# osi

1. 
2. 
3. 
4. 
5. 会话层
6. 表达层
7. 应用层

# HTTP

1. 支持客户端/服务器模式。

2. 无连接
处理完客户的请求并收到应答后立即断开连接。

3. 无状态
不需要验证对方的状态。
对于事务处理没有记忆能力，如果后续需要前面的信息必须重传。