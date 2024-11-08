#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#include "ntstatus.h"

typedef NTSTATUS(NTAPI* NtCreateProcessPrototype)(
    PHANDLE             ProcessHandle,
    ACCESS_MASK         DesiredAccess,
    POBJECT_ATTRIBUTES  ObjectAttributes,
    HANDLE              ParentProcess,
    BOOLEAN             InheritObjectTable,
    HANDLE              SectionHandle,
    HANDLE              DebugPort,
    HANDLE              TokenHandle
);

void printNTSTATUS(NTSTATUS status) {
    switch (status) {
    case STATUS_SUCCESS:
        printf("NtCreateProcess: Success\n");
        break;
    case STATUS_ACCESS_DENIED:
        printf("NtCreateProcess: Access Denied\n");
        break;
    case STATUS_UNSUCCESSFUL:
        printf("NtCreateProcess: Unsuccessful\n");
        break;
    default:
        printf("NtCreateProcess failed with NTSTATUS code: 0x%08X\n", status);
        break;
    }
}

int main() {
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    if (!ntdll) {
        printf("Failed to load ntdll.dll\n");
        return 1;
    }

    NtCreateProcessPrototype NtCreateProcess = (NtCreateProcessPrototype)GetProcAddress(ntdll, "NtCreateProcess");
    if (!NtCreateProcess) {
        printf("Failed to find NtCreateProcess\n");
        FreeLibrary(ntdll);
        return 1;
    }

    HANDLE calcProcess;
    OBJECT_ATTRIBUTES objAttributes;
    InitializeObjectAttributes(&objAttributes, NULL, 0, NULL, NULL);

    // Open a handle to the parent process, usually set to current process (self).
    HANDLE parentProcess = GetCurrentProcess();

    NTSTATUS status = NtCreateProcess(
        &calcProcess,
        PROCESS_ALL_ACCESS,
        &objAttributes,
        parentProcess,
        FALSE,          // InheritObjectTable - False means we don't inherit
        NULL,           // SectionHandle - Needs a section of the executable image (complicated)
        NULL,           // DebugPort - Typically NULL
        NULL            // TokenHandle - Typically NULL for default token inheritance
    );

    printNTSTATUS(status);

    // Clean up
    if (calcProcess) {
        CloseHandle(calcProcess);
    }
    FreeLibrary(ntdll);

    printf("Now we are exiting the program...\n");

    return 0;
}
