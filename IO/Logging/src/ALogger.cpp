#include "ALogger.hpp"
#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>


using std::string;
using std::wstring;

namespace Simple {
    namespace IO {
        template <>
        void ALogger<string>::Write(string Message, LogLevel Level) {
                    std::fstream logFile;
                    tm time = this->_GetTimeStamp();
                    logFile.open(this->_FilePath, std::ios_base::openmode::_S_app);
                    // Still feels so very hackish to find time by adding the last millenia
                    logFile << "[" << time.tm_year + 1900 << "-" << std::setfill('0') << std::setw(2) << time.tm_mon << "-" << std::setfill('0') << std::setw(2) << time.tm_mday << " "  << std::setfill('0') << std::setw(2) << time.tm_hour << ":" << std::setfill('0') << std::setw(2) << time.tm_min << ":" << std::setfill('0') << std::setw(2) << time.tm_sec << "](" << Level << "): " << Message << std::endl;
                    logFile.close();
                }
        template <>
        void ALogger<string>::Write(string Message) {
                    this->Write(Message, this->_LogLevelDefault);
                }
        template <>
        void ALogger<wstring>::Write(wstring Message, LogLevel Level) {
                    std::wfstream logFile;
                    tm time = this->_GetTimeStamp();
                    logFile.open(this->_FilePath, std::ios_base::openmode::_S_app);
                    // Still feels so very hackish to find time by adding the last millenia
                    logFile << L"[" << time.tm_year + 1900 << L"-" << std::setfill(L'0') << std::setw(2) 
                            << time.tm_mon << "-" << std::setfill(L'0') << std::setw(2) << time.tm_mday 
                            << " "  << std::setfill(L'0') << std::setw(2) << time.tm_hour << ":" << std::setfill(L'0') 
                            << std::setw(2) << time.tm_min << ":" << std::setfill(L'0') << std::setw(2) << time.tm_sec 
                            << "](" << Level << "): " << Message << std::endl;
                    logFile.close();
                }
        template <>
        void ALogger<wstring>::Write(wstring Message) {
                    this->Write(Message, this->_LogLevelDefault);
                }
        template <>
        wstring ALogger<wstring>::GetLogFileLocation() {
            return this->_FilePath.filename().wstring();
        }
        template <>
        wstring ALogger<wstring>::GetLogDirectoryName() {
            return this->_FilePath.parent_path().wstring();
        }
        template <>
        wstring ALogger<wstring>::GetLogFileName() {
            return this->_FilePath.filename().wstring();
        }
        template <>
        string ALogger<string>::GetLogFileLocation() {
            return this->_FilePath.filename();
        }
        template <>
        string ALogger<string>::GetLogDirectoryName() {
            return this->_FilePath.parent_path();
        }
        template <>
        string ALogger<string>::GetLogFileName() {
            return this->_FilePath.filename();
        }
        tm _GetTimeStamp() {
            auto timePointNow = std::chrono::system_clock::now();
            std::time_t secondsFromEpochNow = std::chrono::system_clock::to_time_t(timePointNow);
            tm result = *std::localtime(&secondsFromEpochNow);
            return result;
        }

   } // NS: Simple
} // NS: IO