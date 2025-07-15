#include <array>
#include <iostream>

constexpr int cal(int x) {
    int su = 1;
    for (int i = 1; i <= 100000; i++) {
        su = (su * i) % x;
    }
    return su;
}

template <size_t... I>
constexpr std::array<int, sizeof...(I)> make_array(std::integer_sequence<size_t, I...>) {
    
    return {cal(I + 1)...};  // 计算 cal(1), cal(2), ..., cal(1000)
}

constexpr auto a = make_array(std::make_integer_sequence<size_t, 1000>{});

int main() {
    for (int i = 0; i < 1000; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}
