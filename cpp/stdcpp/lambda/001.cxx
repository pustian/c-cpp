#include <iostream>
#include <vector>
int (*func)(int, int);
int main(void) {
    // [capture](parameters)->return-type{body}
    // 没有返回值 [capture](parameters){body} 
    // C++变量传递有传值和传引用的区别。可以通过前面的[]来指定
    // []      // 沒有定义任何变量。使用未定义变量会引发错误。
    // [x, &y] // x以传值方式传入（默认），y以引用方式传入。
    // [&]     // 任何被使用到的外部变量都隐式地以引用方式加以引用。
    // [=]     // 任何被使用到的外部变量都隐式地以传值方式加以引用。
    // [&, x]  // x显式地以传值方式加以引用。其余变量以引用方式加以引用。
    // [=, &z] // z显式地以引用方式加以引用。其余变量以传值方式加以引用。
    //
    // [capture](parameters) mutable ->return-type{statement}
    // [capture]：捕捉列表。捕捉列表总是出现在 lambda 表达式的开始处。
    //      事实上，[] 是 lambda 引出符。编译器根据该引出符判断接下来的代码是否是 lambda 函数。
    //      捕捉列表能够捕捉上下文中的变量供 lambda 函数使用。
    // (parameters)：参数列表。与普通函数的参数列表一致。
    //      如果不需要参数传递，则可以连同括号 () 一起省略。
    // mutable：mutable 修饰符。默认情况下，lambda 函数总是一个 const 函数，mutable 可以取消其常量性。
    //      在使用该修饰符时，参数列表不可省略（即使参数为空）。
    // ->return_type：返回类型。用追踪返回类型形式声明函数的返回类型。
    //      出于方便，不需要返回值的时候也可以连同符号 -> 一起省略。
    //      此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导。
    // {statement}：函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。
    
    int x = 3;
    int y = 5;
    func = [](int x, int y)->int{ return x + y ; };
    std::cout<<"x="<<x<<" y="<<y<<std::endl;
    std::cout<<"x+y="<<func(x, y)<<std::endl;
    return 0;
}
