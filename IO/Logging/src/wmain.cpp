
#include "WLogger.hpp"
int main(int argc, char** argv) {
    Simple::IO::WLogger log(L"log/log.log");
    log.Write(L"New Wide Test");
    return 0;
}