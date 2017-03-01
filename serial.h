#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED
#include <windows.h>
#include <vector>
#include <string>
#include <functional>
#define BL(x) ((x>>24&0x000000ff)|(x>>8&0x0000ff00)|(x<<8&0x00ff0000)|(x<<24&0xff000000))
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
#endif // SERIAL_H_INCLUDED
