#include "CResourceMngFactory.hpp"
#include "CResourceManager.hpp"
#include <exception>
#include <iostream>

#define READ_WRITE_ACCESS 0x0666

int main() {
    //CommandLineParser cmdParser(argc, argv);

    try {
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
