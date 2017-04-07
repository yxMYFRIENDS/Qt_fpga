#ifndef BASE_SET_H_INCLUDED
#define BASE_SET_H_INCLUDED
#include<curste.h>
#include<vector>
#include<string>
#ifdef Debug
#include<my.h>
#endif // Debug
class BaseSet{
    double sys_freq;
    int auto_io_update;
    CurrentState cs;
public:
    SerialPort sp;
    std::vector<std::string> com_list();
    void rest();
    bool open_com(std::string s);
    void close_com();
    void set_sys_freq(double freq);
    void set_auto_ioupdate(int i);
    void set_osk_enable(int i);
    int get_osk_enable();
    void set_external_oskenable(int i);
    int get_external_oskenable();
    void cal_dac();
    void cal_pll();
    double& get_sys_freq();
    int& get_auto_ioupdate();
    SerialPort& get_serial();
    CurrentState& get_cur_state();
    BaseSet():cs(sp),sys_freq(3200),auto_io_update(1){};
};
#endif // BASE_SET_H_INCLUDED
