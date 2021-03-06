
#include "curste.h"

std::ostream& operator<<(std::ostream& os,const Reg& reg)
{
    os<<std::hex<<"addr:0x"<<(int)reg.addr<<" value:0x"<<reg.value<<std::dec;
    return os;
}

SerialPort& operator>>(SerialPort& sp,Reg& reg)
{
    if(reg.addr>=0x0B && reg.addr<=0x1A)
        sp<<(unsigned char)((reg.addr-0x0B)/2 | 0x48);
    sp<<(char)(reg.addr|0x80);
    sp>>reg.value;
    return sp;
}
SerialPort& operator<<(SerialPort& sp,const Reg& reg)
{
    return sp<<reg.addr<<reg.value;
}

/*  =====oedi====== */
void CurrentState::io_update()
{
    oedi &= 0xfe;
    sp<<oedi<<(unsigned char)(oedi|0x01)<<oedi;
}
void CurrentState::set_drhold(unsigned char i)
{
    oedi = (oedi&0xfd)|(i&0x01)<<1;
    sp<<oedi;
}
int CurrentState::get_drhold()
{
    return (oedi&0x02)>>1;
}
void CurrentState::set_epd(unsigned char i)
{
    oedi = (oedi&0xfb)|(i&0x01)<<2;
    sp<<oedi;
}
int CurrentState::get_epd()
{
    return (oedi&0x04)>>2;
}
void CurrentState::set_osk(unsigned char i)
{
    oedi = (oedi&0xf7)|(i&0x01)<<3;
    sp<<oedi;
}
int CurrentState::get_osk()
{
    return (oedi&0x08)>>3;
}
/*  =====oedi END====== */


/*  ===== PS2-PS0 ====== */
void CurrentState::set_ps(int i)  //0-7
{
    ps = (ps&0xf8) | (0x00000007 & i);
    sp<<ps;
}
int CurrentState::get_ps()
{
    return ps&0x07;
}
/*  ===== PS END ====== */

/*  ===== drctl ====== */
void CurrentState::set_drctl(unsigned char i)
{
    drctl = (drctl&0xfe)|(i&0x01);
    sp<<drctl;
}
int CurrentState::get_drctl()
{
    return drctl&0x01;
}
void CurrentState::set_auto_drctl(unsigned char i)
{
    drctl = (drctl&0xfd)|(i&0x01)<<1;
    sp<<drctl;
}
int CurrentState::get_auto_drctl()
{
    return (drctl&0x02)>>1;
}
/*  ===== drctl END ====== */

/*  ===== reset ====== */
void CurrentState::reset()
{
    if(conn_device()){
        sp<<ps<<oedi<<drctl;
        sp<<(char)0x43<<(char)0x42;
        update_hdreg();
    }
}
/*  ===== reset END ====== */

/** 连接设备 **/
bool CurrentState::conn_device()
{
    char cmd = 0x80;
    int value = 0xaaaaaaaf;
    size_t time_cnt = clock();
    if(!sp.clear_iobuf()){
        MessageBox(NULL,TEXT("串口未连接"),TEXT("Warning"),0);
        return conn_state = false;
    }
    sp<<cmd; sp>>value;
    if(clock()-time_cnt>950){
       MessageBox(NULL,TEXT("FPGA未连接"),TEXT("Warning"),0);
        return conn_state = false;
    }
    if((value&0x00000003)==2)
        return conn_state = true;
    else{
        sp<<0x00000100<<0x0A515080;
        sp>>value;
        if((value&0x00000003)==2)
            return conn_state = true;
        else{
            MessageBox(NULL,TEXT("DDS未连接"),TEXT("Warning"),0);
            return conn_state = false;
        }
    }
}
/** conn_device END **/

/** rw reg **/
void CurrentState::write_reg(const Reg& reg)
{
    sp<<reg;
}
void CurrentState::write_reg(unsigned char addr,unsigned int value)
{
    sp<<addr<<value;
}
Reg CurrentState::read_reg(unsigned char addr)
{
    Reg tmp;
    tmp.addr = addr;
    sp>>tmp;
    set_ps(ps);
    return tmp;
}
void CurrentState::read_reg(Reg& reg)
{
    sp>>reg;
    set_ps(ps);
}
/**  rw reg end **/

void CurrentState::update_hdreg() //更新hdreg
{
    sp.clear_iobuf();
    for(auto& i:hdreg)
        sp>>i;
    set_ps(ps);
}

CurrentState::CurrentState(SerialPort& sp):sp(sp),ps(0x48),oedi(0x50),drctl(0x44),conn_state(false)
{
    for(unsigned char i=0;i<28;++i)
        hdreg[i].addr = i;
}
