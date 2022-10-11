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
        void ALogger<char>::Write(const std::basic_string<char> Message, LogLevel Level) {
                    std::fstream logFile;
                    tm time = this->_GetTimeStamp();
                    logFile.open(this->_FilePath, std::ios_base::openmode::_S_app);
                    // Still feels so very hackish to find time by adding the last millenia
                    logFile << "[" << time.tm_year + 1900 << "-" << std::setfill('0') << std::setw(2) << time.tm_mon << "-" << std::setfill('0') << std::setw(2) << time.tm_mday << " "  << std::setfill('0') << std::setw(2) << time.tm_hour << ":" << std::setfill('0') << std::setw(2) << time.tm_min << ":" << std::setfill('0') << std::setw(2) << time.tm_sec << "](" << Level << "): " << Message << std::endl;
                    logFile.close();
        }
        // template <>
        // void ALogger<string>::Write(string Message, LogLevel Level) {
        //             this->Write(Message.c_str(), Level);
        // }
        template<>
        void ALogger<wchar_t>::Write(const std::basic_string<wchar_t> Message, LogLevel Level) {
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
        // template <>
        // void ALogger<wstring>::Write(wstring Message, LogLevel Level) {
        //             std::wfstream logFile;
        //             tm time = this->_GetTimeStamp();
        //             logFile.open(this->_FilePath, std::ios_base::openmode::_S_app);
        //             // Still feels so very hackish to find time by adding the last millenia
        //             logFile << L"[" << time.tm_year + 1900 << L"-" << std::setfill(L'0') << std::setw(2) 
        //                     << time.tm_mon << "-" << std::setfill(L'0') << std::setw(2) << time.tm_mday 
        //                     << " "  << std::setfill(L'0') << std::setw(2) << time.tm_hour << ":" << std::setfill(L'0') 
        //                     << std::setw(2) << time.tm_min << ":" << std::setfill(L'0') << std::setw(2) << time.tm_sec 
        //                     << "](" << Level << "): " << Message << std::endl;
        //             logFile.close();
        // }
        template <>
        std::basic_string<wchar_t> ALogger<wchar_t>::GetLogFileLocation() {
            return this->_FilePath.filename().wstring();
        }
        template <>
        std::basic_string<wchar_t> ALogger<wchar_t>::GetLogDirectoryName() {
            return this->_FilePath.parent_path().wstring();
        }
        template <>
        std::basic_string<wchar_t> ALogger<wchar_t>::GetLogFileName() {
            return this->_FilePath.filename().wstring();
        }
        template <>
        string ALogger<char>::GetLogFileLocation() {
            return this->_FilePath.filename();
        }
        template <>
        string ALogger<char>::GetLogDirectoryName() {
            return this->_FilePath.parent_path();
        }
        template <>
        string ALogger<char>::GetLogFileName() {
            return this->_FilePath.filename();
        }
        // template <>
        // const char* ALogger<const char *>::GetLogFileLocation() {
        //     return this->_FilePath.filename().c_str();
        // }
        // template <>
        // const char* ALogger<const char*>::GetLogDirectoryName() {
        //     return this->_FilePath.parent_path().c_str();
        // }
        // template <>
        // const char* ALogger<const char*>::GetLogFileName() {
        //     return this->_FilePath.filename().c_str();
        // }
        tm _GetTimeStamp() {
            auto timePointNow = std::chrono::system_clock::now();
            std::time_t secondsFromEpochNow = std::chrono::system_clock::to_time_t(timePointNow);
            tm result = *std::localtime(&secondsFromEpochNow);
            return result;
        }

   } // NS: Simple
} // NS: IO