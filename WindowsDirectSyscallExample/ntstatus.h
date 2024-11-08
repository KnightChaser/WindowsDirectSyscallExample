// ntstatus.h

#ifndef NTSTATUS_H
#define NTSTATUS_H

#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022L)
// Add more NTSTATUS codes as needed

typedef long NTSTATUS;

#endif // NTSTATUS_H
