#ifndef BASE_SET_H_INCLUDED
#define BASE_SET_H_INCLUDED
#include<curste.h>
#include<vector>
#include<string>
#include<serial.h>
#ifdef Debug
#include<my.h>
#endif // Debug
class BaseSet{
    double sys_freq;
    int auto_io_update;
    CurrentState cs;
    SerialPort sp;
public:
    std::vector<std::string> com_list();
    void rest();
    bool open_com(std::string s);
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

SerialPort& BaseSet::get_serial(){return sp;}
CurrentState& BaseSet::get_cur_state(){return cs;}
std::vector<std::string> BaseSet::com_list()
{
    std::vector<std::string> ret;
    SerialPort::get_coms(ret);
    return ret;
}
void BaseSet::rest()
{
    cs.reset();
}
bool BaseSet::open_com(std::string s)
{
    return   sp.bind_com(s)&&cs.conn_device();
}
void BaseSet::set_sys_freq(double freq)
{
    sys_freq = freq;
}
double& BaseSet::get_sys_freq()
{
    return sys_freq;
}
void BaseSet::set_auto_ioupdate(int i)
{
    if(i) auto_io_update = 1;
    else auto_io_update = 0;
}
int& BaseSet::get_auto_ioupdate()
{
    return auto_io_update;
}
void BaseSet::set_osk_enable(int i)
{
    i &= 0x01;
    auto cf1 = cs.read_reg(0x00);
    cf1.value = (cf1.value&0xFFFFFEFF)|i<<8;
    cs.write_reg(cf1);
    cs.io_update();
}
int BaseSet::get_osk_enable()
{
    auto cf1 = cs.read_reg(0x00);
    return (cf1.value&0x100)>>8;
}
void BaseSet::set_external_oskenable(int i)
{
    i &= 0x01;
    auto cf1 = cs.read_reg(0x00);
    cf1.value = (cf1.value&0xFFFFFDFF)|i<<9;
    cs.write_reg(cf1);
    cs.io_update();
}
int BaseSet::get_external_oskenable()
{
    auto cf1 = cs.read_reg(0x00);
    return (cf1.value&0x200)>>9;
}
void BaseSet::cal_dac()
{
    auto cf4 = cs.read_reg(0x03);
#ifdef Debug
    pf(cf4);
#endif // Debug
    if(cf4.value&0x01000000){
        cf4.value &= ~(0x01000000);
        cs.write_reg(cf4);
        cs.io_update();
    }
    cf4.value |= 0x01000000;
    cs.write_reg(cf4);
    cs.io_update();
#ifdef Debug
    pf(cf4);
#endif // Debug
}
void BaseSet::cal_pll()
{
    auto cf1 = cs.read_reg(0x00);
#ifdef Debug
    pf(cf1);
#endif // Debug
    if(cf1.value&0x01000000){
        cf1.value &= ~(0x01000000);
        cs.write_reg(cf1);
        cs.io_update();
    }
    cf1.value |= 0x01000000;
    cs.write_reg(cf1);
    cs.io_update();
#ifdef Debug
    pf(cf1);
#endif // Debug
}
#endif // BASE_SET_H_INCLUDED
