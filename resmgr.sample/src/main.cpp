#include "CResourceMngFactory.hpp"
#include "CResourceManager.hpp"

#define READ_WRITE_ACCESS 0x0666

int main() {
    res::factory::CResourceMngFactory factory;
    std::shared_ptr<res::impl::CResourceManagerImpl> p_qnxResMngImpl =
            factory.createResManagerImpl(res::factory::CResourceMngFactory::ResManagerTypes::QnxResourceManager);
    res::CResourceManager resmgr(p_qnxResMngImpl);

    //call blocked mehtod
    resmgr.run("/dev/sample", READ_WRITE_ACCESS);
    //normally never execute code after line above

    return 0;
}
