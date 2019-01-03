#include "CQnxResMgrImpl.hpp"
#include "CResourceManager.hpp"

#define READ_WRITE_ACCESS 0x0666

int main() {
    CQnxResMgrImpl qnxResMgr;
    CResourceManager resmgr(qnxResMgr);

    //call blocked mehtod
    resmgr.run("/dev/sample", READ_WRITE_ACCESS);
    //normally never execute code after line above

    return 0;
}
