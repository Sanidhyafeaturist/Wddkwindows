#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class DriverGenerator {
public:
    void generateDriver(const std::string& deviceType) {
        auto it = templates.find(deviceType);
        if (it != templates.end()) {
            std::string driverCode = it->second;
            std::string fileName = deviceType + "_driver.cpp";

            std::ofstream outFile(fileName);
            if (outFile.is_open()) {
                outFile << driverCode;
                outFile.close();
                std::cout << "Driver for " << deviceType << " generated as " << fileName << std::endl;
            } else {
                std::cerr << "Error creating file: " << fileName << std::endl;
            }
        } else {
            std::cerr << "Unsupported device type: " << deviceType << std::endl;
        }
    }

private:
    std::unordered_map<std::string, std::string> templates {
        {"keyboard", R"(
#include <ntddk.h>

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = DriverUnload;
    KdPrint(("Keyboard Driver Loaded\\n"));
    return STATUS_SUCCESS;
}

extern "C" VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    KdPrint(("Keyboard Driver Unloaded\\n"));
}
)"},
        {"mouse", R"(
#include <ntddk.h>

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = DriverUnload;
    KdPrint(("Mouse Driver Loaded\\n"));
    return STATUS_SUCCESS;
}

extern "C" VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    KdPrint(("Mouse Driver Unloaded\\n"));
}
)"},
        {"speaker", R"(
#include <ntddk.h>

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = DriverUnload;
    KdPrint(("Speaker Driver Loaded\\n"));
    return STATUS_SUCCESS;
}

extern "C" VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    KdPrint(("Speaker Driver Unloaded\\n"));
}
)"},
    };
};

int main() {
    DriverGenerator generator;

    std::cout << "Device Driver Generator\n";
    std::string deviceTypes[] = {"keyboard", "mouse", "speaker"};

    for (const auto& device : deviceTypes) {
        generator.generateDriver(device);
    }

    return 0;
}
