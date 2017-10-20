#include <serial.h>

DWORD WINAPI _asyn_thread(LPVOID pParam)
{
    auto Param = *(std::tuple<HANDLE,LPVOID,DWORD,bool,std::function<void(void)> >*)pParam;
    ClearCommError(std::get<0>(Param), NULL, NULL);
    DWORD tmp;
    if(std::get<3>(Param)) ReadFile(std::get<0>(Param),std::get<1>(Param),std::get<2>(Param),&tmp,NULL);
    else WriteFile(std::get<0>(Param),std::get<1>(Param),std::get<2>(Param),&tmp,NULL);
    std::get<4>(Param)();
    delete((std::tuple<HANDLE,LPVOID,DWORD,bool,std::function<void(void)> >*)pParam);
    ExitThread(0);
}

template<typename tFunc,typename... Args>
void SerialPort::_asyn_build(LPVOID st,DWORD rw_num,bool rw,tFunc Func,Args&&... func_param_list)
{
    std::function<void(void)> lambda;
    if(Func) lambda = [&func_param_list...,Func]{Func(std::forward<Args>(func_param_list)...);};
    else lambda = []{};
    auto pParam = new std::tuple<HANDLE,LPVOID,DWORD,bool,std::function<void(void)> >(hComm,st,rw_num,rw,lambda);
    CloseHandle(CreateThread(NULL,0,_asyn_thread,pParam,0,NULL));
}
void SerialPort::_syn_build(LPVOID st,DWORD rw_num,bool rw)
{
    ClearCommError(hComm, NULL, NULL);
    DWORD tmp;
    if(rw) ReadFile(hComm,st,rw_num,&tmp,NULL);
    else WriteFile(hComm,st,rw_num,&tmp,NULL);
}
std::string LPCTSTRTostring(TCHAR* STR)
{
#ifdef UNICODE
    int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);
    char* chRtn =new char[iLen*sizeof(char)];
    WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
    std::string str(chRtn);
#else
    std::string str(STR);
#endif
    return str;
}
LPCTSTR stringToLPCTSTR(std::string orig,TCHAR* STR)
{
#ifdef UNICODE
    size_t origsize = orig.length() + 1;
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, STR, origsize, orig.c_str(), _TRUNCATE);
    return STR;
#else
    strcpy(STR,orig.c_str());
    return STR;
#endif
}
void SerialPort::get_coms(std::vector<std::string>& strSerialList)
{
    TCHAR Name[25];
    TCHAR szPortName[25];
    int Status;
    std::vector<std::string>().swap(strSerialList);
    DWORD  dwIndex = 0;
    DWORD  dwName;
    DWORD  dwSizeofPortName;
    DWORD Type;
    HKEY hKey;
    TCHAR data_Set[] = TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM\\");
    dwName = sizeof(Name);
    dwSizeofPortName = sizeof(szPortName);
    long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey);
    if(ret0 == ERROR_SUCCESS){
        do{
            Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type,  (PUCHAR)szPortName, &dwSizeofPortName);
            if((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA)) strSerialList.push_back(LPCTSTRTostring(szPortName));
            dwName = sizeof(Name);
            dwSizeofPortName = sizeof(szPortName);
        }while((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA));
        RegCloseKey(hKey);
    }
}
bool SerialPort::bind_com(std::string name)
{
    isopen = true;
    TCHAR tcstring[30];
    hComm = CreateFile( stringToLPCTSTR(("\\\\.\\"+name),tcstring), //串口号
                        GENERIC_READ | GENERIC_WRITE, //允许读写
                        0, //通讯设备必须以独占方式打开
                        NULL, //无安全属性
                        OPEN_EXISTING, //通讯设备已存在
                        0, //同步 I/O
                        0); //通讯设备不能用模板打开
    if (hComm == INVALID_HANDLE_VALUE){
        isopen = false;
        MessageBox(NULL,TEXT("Open Serial Port Failed!"),TEXT("Error"),0);
    }else{
        DCB dcb;
        isopen &= GetCommState(hComm,&dcb);
        dcb.BaudRate = 115200;
        dcb.Parity = NOPARITY;
        dcb.fParity = 0;
        dcb.StopBits = ONESTOPBIT;
        dcb.ByteSize = 8;
        dcb.fOutxCtsFlow = 0;
        dcb.fOutxDsrFlow = 0;
        dcb.fDtrControl = DTR_CONTROL_DISABLE;
        dcb.fDsrSensitivity = 0;
        dcb.fRtsControl = RTS_CONTROL_DISABLE;
        dcb.fOutX = 0;
        dcb.fInX = 0;
        dcb.fErrorChar = 0;
        dcb.fBinary = 1;
        dcb.fNull = 0;
        dcb.fAbortOnError = 0;
        dcb.wReserved = 0;
        dcb.XonLim = 2;
        dcb.XoffLim = 4;
        dcb.XonChar = 0x1;
        dcb.XoffChar = 0x1;
        dcb.EvtChar = 0;
        if(isopen) isopen &= SetCommState(hComm,&dcb);
        COMMTIMEOUTS timeouts;
        timeouts.ReadIntervalTimeout = 0;
        timeouts.ReadTotalTimeoutConstant = 1000;
        timeouts.ReadTotalTimeoutMultiplier = 0;
        timeouts.WriteTotalTimeoutConstant = 0;
        timeouts.WriteTotalTimeoutMultiplier = 0;
        if(isopen) isopen &= SetCommTimeouts(hComm, &timeouts);
    }
    if(!isopen) CloseHandle(hComm);
    return isopen;
}
void SerialPort::close_com()
{
    if(hComm) CloseHandle(hComm);
}
