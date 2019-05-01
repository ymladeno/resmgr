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

    std::string l_write{"haha"};
    std::cout << "Write: " << l_write << std::endl;
    proxy.write("haha");

    std::string l_read{};
    proxy.read(l_read);
    std::cout << "Read: " << l_read << std::endl;

    proxy.set_font_color(Blue);
    proxy.write("This has to be in blue color");
    return 0;
}
