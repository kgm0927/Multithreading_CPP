#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_THREADS 3
#define BUF_SIZE 255

typedef struct MyData{
    int val1;
    int val2;

}MYDATA, *PMYDATA;


DWORD WINAPI worker(LPVOID lpParam){
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(hStdout==INVALID_HANDLE_VALUE){
        return 1;
    }

    PMYDATA pDataArray=(PMYDATA) lpParam;

TCHAR msgBuf[BUF_SIZE];
size_t cchStringSize;
DWORD dwChars;

StringCchPrintf(msgBuf,BUF_SIZE,TEXT("Parameters=%d %d \n"),pDataArray->val1,pDataArray->val2);

StringCchLength(msgBuf,BUF_SIZE,&cchStringSize);
WriteConsole(hStdout,msgBuf,(DWORD)cchStringSize,&dwChars,NULL);

return 0;
}

void errorHandler(LPTSTR lpszFunction){
    LPVOID lPMsgBuf;
    LPVOID lPDisplayBuf;
    DWORD dw=GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER|
        FORMAT_MESSAGE_FROM_SYSTEM|
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
        (LPTSTR)&lPMsgBuf,
        0,NULL
    );

    lPDisplayBuf=(LPVOID)LocalAlloc(LMEM_ZEROINIT,(lstrlen((LPCTSTR)lPMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));

    StringCchPrintf((LPTSTR)lPDisplayBuf,LocalSize(lPDisplayBuf)/sizeof(TCHAR),TEXT("%s failed with error %d: %s"),lpszFunction,
    dw,lPMsgBuf);

    MessageBox(NULL,(LPCTSTR)lPDisplayBuf,TEXT("Error"),MB_OK);

    LocalFree(lPMsgBuf);
    LocalFree(lPDisplayBuf);
}

int _tmain(){
    PMYDATA pDataArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++)
    {
       pDataArray[i]=(PMYDATA)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(MYDATA));
       if(pDataArray[i]==0){
        ExitProcess(2);
       }

    pDataArray[i]->val1=i;
    pDataArray[i]->val2=i+100;

    hThreadArray[i]=CreateThread(
        NULL,
        0,
        worker,
        pDataArray[i],
        0,
        &dwThreadIdArray[i]
    );

if(hThreadArray[i]==0){
    errorHandler(TEXT("CreateThread"));
    ExitProcess(3);
}
    }

WaitForMultipleObjects(MAX_THREADS,hThreadArray,TRUE,INFINITE);
for (int i = 0; i < MAX_THREADS; i++)
{
    CloseHandle(hThreadArray[i]);
    if(pDataArray[i]!=0){
        HeapFree(GetProcessHeap(),0,pDataArray[i]);
    }
    
}
return 0;

    
}