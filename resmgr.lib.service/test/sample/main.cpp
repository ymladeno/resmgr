/*
 * main.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: YMLADENO
 */

#include "CProxy.hpp"
#include <iostream>

int main() {
    srv::sample::CProxy proxy{};
    proxy.write("haha");
    std::string s{};
    proxy.read(s);
    std::cout << s << std::endl;
    return 0;
}

