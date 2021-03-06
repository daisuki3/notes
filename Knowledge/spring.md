# IoC

对象A依赖一系列对象甲乙丙丁来完成其行为。

这时候不在A类的内部申请对象甲乙丙丁，因为当有成千上万个类似A类的类时，这样做会有大量的重复代码，而且耦合性太高。
这时候利用IoC(inversion of control)，先申明一系列的依赖关系，当需要对象A时，容器自动为我们注入对象A需要的甲乙丙丁。

# AOP

一系列对象都在某个相同节点需要某种服务，例如对象初始化前的日志注册，或方法执行前的安全检查，称这些共同的服务为一个切面(Aspect)关注点。
若分别在方法里编写这些逻辑，则重复代码太多，耦合性太高。
可以把这些关注点当成一个切面，面向切面编程。

Spring中实现AOP的方法：
- 代理模式，要求代理对象和原对象实现同一个接口。
  - 静态代理：每个类需要一个单独的代理类。
  - 动态代理：对于相同的Jointpoint，只使用一个代理类，为各类动态生成代理对象。
- 动态字节码生成，当原对象不实现任何借口时使用。