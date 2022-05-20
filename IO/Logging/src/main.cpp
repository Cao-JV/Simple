#include "Logger.hpp"
using std::string;
using namespace Simple::IO;
        std::ostream& operator<<(std::ostream& Output, const LogLevel Value){
                const char* levelText = 0;
            #define PROCESS_VAL(p) case(p): levelText = #p; break;
                switch(Value){
                    PROCESS_VAL(Trace);     
                    PROCESS_VAL(Debug);     
                    PROCESS_VAL(Info);
                    PROCESS_VAL(Warning);
                    PROCESS_VAL(Error);
                    PROCESS_VAL(Fatal);
                }
            #undef PROCESS_VAL

            return Output << levelText;
        }

int main(int argc, char** argv) {
    Simple::IO::Logger log("log/log.log");
    log.Write("Dickshit");
    return 0;
}