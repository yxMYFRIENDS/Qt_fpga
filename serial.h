#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED
#include <windows.h>
#include <vector>
#include <functional>
#define BL(x) ((x>>24&0x000000ff)|(x>>8&0x0000ff00)|(x<<8&0x00ff0000)|(x<<24&0xff000000))


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
class SerialPort{
    HANDLE hComm = NULL;
    template<typename tFunc,typename... Args> void _asyn_build(LPVOID st,DWORD rw_num,bool rw,tFunc Func,Args&&... func_param_list);
    void _syn_build(LPVOID st,DWORD rw_num,bool rw);
public:
    bool isopen = 0;

    SerialPort() = default;
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(std::string name){
        bind_com(name);
    }
    ~SerialPort(){
        if(isopen) CloseHandle(hComm);
    };

    bool clear_iobuf(){
        if(isopen) return PurgeComm(hComm,PURGE_RXCLEAR | PURGE_TXCLEAR);
        else return false;
    };
    template<typename tFunc = void(*)(void),typename... Args>
    void asyn_read(LPVOID st,DWORD rw_num,tFunc Func= (tFunc)NULL,Args&&... func_param_list){
        _asyn_build(st,rw_num,true,Func,std::forward<Args>(func_param_list)...);
    }
    template<typename tFunc = void(*)(void),typename... Args>
    void asyn_write(LPVOID st,DWORD rw_num,tFunc Func= (tFunc)NULL,Args&&... func_param_list){
        _asyn_build(st,rw_num,false,Func,std::forward<Args>(func_param_list)...);
    }
    void syn_read(LPVOID st,DWORD rw_num){
        _syn_build(st,rw_num,true);
    }
    void syn_write(LPVOID st,DWORD rw_num){
        _syn_build(st,rw_num,false);
    }
    SerialPort& operator>>(unsigned char &t) {syn_read(&t,1); return *this;};
    SerialPort& operator>>(char &t)          {syn_read(&t,1); return *this;};
    SerialPort& operator>>(unsigned int &t)  {syn_read(&t,4); t = BL(t); return *this;};
    SerialPort& operator>>(int &t)           {syn_read(&t,4); t = BL(t); return *this;};
    SerialPort& operator<<(unsigned char t)  {syn_write(&t,1); return *this;};
    SerialPort& operator<<(char t)           {syn_write(&t,1); return *this;};
    SerialPort& operator<<(unsigned int t)   {t = BL(t);syn_write(&t,4); return *this;};
    SerialPort& operator<<(int t)            {t = BL(t);syn_write(&t,4); return *this;};
    SerialPort& operator<<(char* t)          {while(*t!= '\0') *this<<*t++; return *this;}

    bool bind_com(std::string name);
    static void get_coms(std::vector<std::string>& strSerialList);
};

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
void SerialPort::get_coms(std::vector<std::string>& strSerialList)
{
    char Name[25];
    unsigned char szPortName[25];
    int Status;
    std::vector<std::string>().swap(strSerialList);
    DWORD  dwIndex = 0;
    DWORD  dwName;
    DWORD  dwSizeofPortName;
    DWORD Type;
    HKEY hKey;
    LPCTSTR data_Set=(LPCTSTR)"HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
    dwName = sizeof(Name);
    dwSizeofPortName = sizeof(szPortName);
    long ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey);
    if(ret0 == ERROR_SUCCESS){
        do{
            Status = RegEnumValue(hKey, dwIndex++, (LPWSTR)Name, &dwName, NULL, &Type, szPortName, &dwSizeofPortName);
            if((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA)) strSerialList.push_back((char*)(szPortName));
            dwName = sizeof(Name);
            dwSizeofPortName = sizeof(szPortName);
        }while((Status == ERROR_SUCCESS)||(Status == ERROR_MORE_DATA));
        RegCloseKey(hKey);
    }
}
bool SerialPort::bind_com(std::string name)
{
    isopen = true;
    hComm = CreateFile( (const wchar_t*)(("\\\\.\\"+name).c_str()), //串口号
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
        dcb.BaudRate = 128000;
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
#endif // SERIAL_H_INCLUDED
