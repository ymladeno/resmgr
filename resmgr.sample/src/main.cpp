#include "CResourceMngFactory.hpp"
#include "CResourceManager.hpp"
#include "CommandLine.hpp"
#include <exception>
#include <iostream>
#include <sstream>

#define READ_WRITE_ACCESS 0x0666

int main(int argc, const char* argv[]) {
    //CommandLineParser cmdParser(argc, argv);
//    logi << hex;
//    logi << "Start a resource manager";
//    LOGI("Start a resource manager");

    try {
        res::parser::CommandLine cmdLine{};
        cmdLine.add_option('c', "config", "Ini file configuration");
        cmdLine.add_option('h', "help", "This is help");
        cmdLine.parse(argc, argv);

        std::string l_ini_path = cmdLine.get_program_argument('c');
        if (l_ini_path == "") {
            std::cout << "Error taking ini file\n";
            return 1;
        }

        std::cout << l_ini_path << std::endl;

        res::factory::CResourceMngFactory factory;
        std::shared_ptr<res::impl::CResourceManagerImpl> p_qnxResMngImpl =
                factory.createResManagerImpl(res::factory::CResourceMngFactory::ResManagerTypes::QnxResourceManager);
        res::CResourceManager resmgr(p_qnxResMngImpl);

        //call blocked mehtod
        resmgr.run("/dev/sample", READ_WRITE_ACCESS);
        //normally never execute code after line above
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
