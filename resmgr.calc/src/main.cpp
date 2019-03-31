#include "CResourceMngFactory.hpp"
#include "CResourceManager.hpp"
#include "CommandLine.hpp"
#include "Callback.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <functional>

#define READ_WRITE_ACCESS 0x0666

int main(int argc, const char* argv[]) {
    try {
        res::parser::CommandLine cmdLine{};
        cmdLine.add_option('c', "config",           "Ini file configuration");
        cmdLine.add_option('h', "help",             "This is help");
        cmdLine.add_option('f', "font_color",       "This is font color");
        cmdLine.add_option('b', "background_color", "This is background color");
        cmdLine.add_option('d', "debug_mode",       "This is debug mode");
        cmdLine.parse(argc, argv);

        std::string l_ini_path = cmdLine.get_program_argument('c');
        if (l_ini_path.empty()) {
            std::cout << "No ini file\n";
        }

        Editor editor{};
        const auto& l_font_color = cmdLine.get_program_argument("font_color");
        if (!l_font_color.empty()) {
            editor.set_font_color(l_font_color);
        }

        const auto& l_background_color = cmdLine.get_program_argument("background_color");
        if (!l_background_color.empty()) {
            editor.set_background_color(l_background_color);
        }

        Callback callback{editor};
        res::factory::CResourceMngFactory factory;
        std::shared_ptr<res::CResourceManagerImpl> p_qnxResMngImpl =
                factory.createResManagerImpl(res::factory::CResourceMngFactory::ResManagerTypes::QnxResourceManager);

        res::CResourceManager resmgr(p_qnxResMngImpl);

        resmgr.init("/dev/calc", READ_WRITE_ACCESS);
        resmgr.initcallback("read",  std::bind(&Callback::read,  &callback, std::placeholders::_1));
        resmgr.initcallback("write", std::bind(&Callback::write, &callback, std::placeholders::_1));

        //call blocked method
        resmgr.run();
        //normally never execute code after line above
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
