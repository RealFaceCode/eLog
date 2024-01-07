#include "elog.hpp"
#include "state.hpp"
#include "msg.hpp"

#include <iostream>
#include <fstream>

namespace elog
{
    namespace internal
    {
        std::vector<std::stringbuf> &GetBuffer()
        {
            auto &state = *internal::GetState();
            return state.logBuffer;
        }

        void logOut(structs::Msg<> &&msg)
        {
            auto& state = *internal::GetState();
            std::string outc;
            std::string outf;

            if(IsFlagSet(enums::StateFlag::OUT_TERMINAL) || IsFlagSet(enums::StateFlag::OUT_BUFFER))
                outc = msg.execute(true);

            if(IsFlagSet(enums::StateFlag::OUT_FILE))
                outf = msg.execute(false);

            if(IsFlagSet(enums::StateFlag::OUT_TERMINAL))
                std::cout << outc << std::endl;

            if(IsFlagSet(enums::StateFlag::OUT_FILE))
            {
                auto& file = state.logFile;
                if(!file.is_open())
                    file.open(state.logFilePath, std::ios::out | std::ios::app);
                file << outf << std::endl;
            }

            if(IsFlagSet(enums::StateFlag::OUT_BUFFER))
            {
                auto& buffer = GetBuffer();
                buffer.emplace_back(std::stringbuf(outc));
            }

            if(IsFlagSet(enums::StateFlag::OUT_NETWORK))
            {
                throw exception::StateExeption("Network output is not implemented yet");
            }
        }
    }

    void SetLogFilePath(std::string_view path)
    {
        auto& state = *internal::GetState();
        state.logFilePath = path;
    }

    void CloseFileStream()
    {
        auto& state = *internal::GetState();
        if(state.logFile.is_open())
            state.logFile.close();
    }
}