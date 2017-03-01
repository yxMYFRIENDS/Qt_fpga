#ifndef CURSTE_H_INCLUDED
#define CURSTE_H_INCLUDED
#include<time.h>
#include<iostream>
#include<serial.h>
struct Reg{
    unsigned char addr;
    unsigned int value;
};
class CurrentState{
    SerialPort& sp;
    unsigned char ps; // PS2-PS0
    unsigned char oedi;//OSK,EPD,DRHOLD,IO_UPDATEW
    unsigned char drctl;//auto_flip_en,set_drctl
public:
    bool conn_state;
    Reg hdreg[28];
    friend SerialPort& operator>>(SerialPort& sp,Reg& reg);

    /*  =====oedi====== */
    void io_update();
    void set_drhold(unsigned char i);
    int get_drhold();
    void set_epd(unsigned char i);
    int get_epd();
    void set_osk(unsigned char i);
    int get_osk();

    /*  ===== PS2-PS0 ====== */
    void set_ps(int i);
    int get_ps();

    /*  ===== drctl ====== */
    void set_drctl(unsigned char i);
    int get_drctl();
    void set_auto_drctl(unsigned char i);
    int get_auto_drctl();

    void reset();        /** = reset ==*/
    bool conn_device();  /** 连接设备 **/

    /** rw reg **/
    void write_reg(const Reg& reg);
    void write_reg(unsigned char addr,unsigned int value);
    Reg  read_reg(unsigned char addr);
    void read_reg(Reg& reg);
    /**  rw reg end **/

    void update_hdreg();

    CurrentState(SerialPort& sp);
};
#endif // CURSTE_H_INCLUDED
