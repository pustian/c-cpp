#include <iostream>
int main(void) {
    // 指明返回类型
    auto add = [](int a, int b) -> int { return a + b; };
    //
    // 自动推断返回类型
    auto multiply = [](int a, int b) { return a * b; };
    int sum = add(2, 5);   // 输出：7
    int product = multiply(2, 5);  // 输出：10
    std::cout<<sum<<std::endl;
    std::cout<<product<<std::endl;
    return 0;
}
