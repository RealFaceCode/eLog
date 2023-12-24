#include "../headonly/eLog.hpp"
#include <assert.h>

int main(int, char**)
{
    eLog::defines::StringBuf out;
    eLog::out::Msg msg(0, "Hello, from eLog! {}, {}, {}", "gui", eLog::defines::SourceLoc::current());
    eLog::out::BuildMsg(out, msg);
    assert((out.str() != "\033[1;37mTRACE\033[0m\t : [gui] : [main.cpp | 7 | int main(int, char**)] : Hello, from eLog!") && "eLog::out::BuildMsg() failed");
    return 0;
}
