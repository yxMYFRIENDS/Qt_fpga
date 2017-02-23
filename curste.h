#ifndef CURSTE_H_INCLUDED਍⌀搀攀昀椀渀攀 䌀唀刀匀吀䔀开䠀开䤀一䌀䰀唀䐀䔀䐀ഀ
਍⌀椀渀挀氀甀搀攀㰀琀椀洀攀⸀栀㸀ഀ
#include<iostream>਍⌀椀渀挀氀甀搀攀 㰀猀攀爀椀愀氀⸀栀㸀ഀ
struct Reg{਍    甀渀猀椀最渀攀搀 挀栀愀爀 愀搀搀爀㬀ഀ
    unsigned int value;਍紀㬀ഀ
std::ostream& operator<<(std::ostream& os,const Reg& reg)਍笀ഀ
    os<<std::hex<<"addr:0x"<<(int)reg.addr<<" value:0x"<<reg.value<<std::dec;਍    爀攀琀甀爀渀 漀猀㬀ഀ
}਍ഀ
SerialPort& operator>>(SerialPort& sp,Reg& reg)਍笀ഀ
    if(reg.addr>=0x0B && reg.addr<=0x1A)਍        猀瀀㰀㰀⠀甀渀猀椀最渀攀搀 挀栀愀爀⤀⠀⠀爀攀最⸀愀搀搀爀ⴀ　砀　䈀⤀⼀㈀ 簀 　砀㐀㠀⤀㬀ഀ
    sp<<(char)(reg.addr|0x80);਍    猀瀀㸀㸀爀攀最⸀瘀愀氀甀攀㬀ഀ
    return sp;਍紀ഀ
SerialPort& operator<<(SerialPort& sp,const Reg& reg)਍笀ഀ
    return sp<<reg.addr<<reg.value;਍紀ഀ
class CurrentState{਍    匀攀爀椀愀氀倀漀爀琀☀ 猀瀀㬀ഀ
    unsigned char ps; // PS2-PS0਍    甀渀猀椀最渀攀搀 挀栀愀爀 漀攀搀椀㬀⼀⼀伀匀䬀Ⰰ䔀倀䐀Ⰰ䐀刀䠀伀䰀䐀Ⰰ䤀伀开唀倀䐀䄀吀䔀圀ഀ
    unsigned char drctl;//auto_flip_en,set_drctl਍瀀甀戀氀椀挀㨀ഀ
    bool conn_state;਍    刀攀最 栀搀爀攀最嬀㈀㠀崀㬀ഀ
    friend SerialPort& operator>>(SerialPort& sp,Reg& reg);਍ഀ
    /*  =====oedi====== */਍    瘀漀椀搀 椀漀开甀瀀搀愀琀攀⠀⤀ഀ
    {਍        猀瀀㰀㰀⠀甀渀猀椀最渀攀搀 挀栀愀爀⤀⠀漀攀搀椀簀　砀　㄀⤀㰀㰀漀攀搀椀㬀ഀ
        oedi &= 0xfe;਍    紀ഀ
    void set_drhold(unsigned char i)਍    笀ഀ
        oedi = (oedi&0xfd)|(i&0x01)<<1;਍        猀瀀㰀㰀漀攀搀椀㬀ഀ
    }਍    椀渀琀 最攀琀开搀爀栀漀氀搀⠀⤀ഀ
    {਍        爀攀琀甀爀渀 ⠀漀攀搀椀☀　砀　㈀⤀㸀㸀㄀㬀ഀ
    }਍    瘀漀椀搀 猀攀琀开攀瀀搀⠀甀渀猀椀最渀攀搀 挀栀愀爀 椀⤀ഀ
    {਍        漀攀搀椀 㴀 ⠀漀攀搀椀☀　砀昀戀⤀簀⠀椀☀　砀　㄀⤀㰀㰀㈀㬀ഀ
        sp<<oedi;਍    紀ഀ
    int get_epd()਍    笀ഀ
        return (oedi&0x04)>>2;਍    紀ഀ
    void set_osk(unsigned char i)਍    笀ഀ
        oedi = (oedi&0xf7)|(i&0x01)<<3;਍        猀瀀㰀㰀漀攀搀椀㬀ഀ
    }਍    椀渀琀 最攀琀开漀猀欀⠀⤀ഀ
    {਍        爀攀琀甀爀渀 ⠀漀攀搀椀☀　砀　㠀⤀㸀㸀㌀㬀ഀ
    }਍    ⼀⨀  㴀㴀㴀㴀㴀漀攀搀椀 䔀一䐀㴀㴀㴀㴀㴀㴀 ⨀⼀ഀ
਍ഀ
    /*  ===== PS2-PS0 ====== */਍    瘀漀椀搀 猀攀琀开瀀猀⠀椀渀琀 椀⤀ഀ
    {਍        瀀猀 㴀 ⠀瀀猀☀　砀昀㠀⤀ 簀 ⠀　砀　　　　　　　㜀 ☀ 椀⤀㬀ഀ
        sp<<ps;਍    紀ഀ
    int get_ps()਍    笀ഀ
        return ps&0x07;਍    紀ഀ
    /*  ===== PS END ====== */਍ഀ
    /*  ===== drctl ====== */਍    瘀漀椀搀 猀攀琀开搀爀挀琀氀⠀甀渀猀椀最渀攀搀 挀栀愀爀 椀⤀ഀ
    {਍        搀爀挀琀氀 㴀 ⠀搀爀挀琀氀☀　砀昀攀⤀簀⠀椀☀　砀　㄀⤀㬀ഀ
        sp<<drctl;਍    紀ഀ
    int get_drctl()਍    笀ഀ
        return drctl&0x01;਍    紀ഀ
    void set_auto_drctl(unsigned char i)਍    笀ഀ
        drctl = (drctl&0xfd)|(i&0x01)<<1;਍        猀瀀㰀㰀搀爀挀琀氀㬀ഀ
    }਍    椀渀琀 最攀琀开愀甀琀漀开搀爀挀琀氀⠀⤀ഀ
    {਍        爀攀琀甀爀渀 ⠀搀爀挀琀氀☀　砀　㈀⤀㸀㸀㄀㬀ഀ
    }਍    ⼀⨀  㴀㴀㴀㴀㴀 搀爀挀琀氀 䔀一䐀 㴀㴀㴀㴀㴀㴀 ⨀⼀ഀ
਍    ⼀⨀  㴀㴀㴀㴀㴀 爀攀猀攀琀 㴀㴀㴀㴀㴀㴀 ⨀⼀ഀ
    void reset()਍    笀ഀ
        if(conn_device()){਍            猀瀀㰀㰀瀀猀㰀㰀漀攀搀椀㰀㰀搀爀挀琀氀㬀ഀ
            sp<<(char)0x43<<(char)0x42;਍            甀瀀搀愀琀攀开栀搀爀攀最⠀⤀㬀ഀ
        }਍    紀ഀ
    /*  ===== reset END ====== */਍ഀ
    /** �����豸 **/਍    戀漀漀氀 挀漀渀渀开搀攀瘀椀挀攀⠀⤀ഀ
    {਍        挀栀愀爀 挀洀搀 㴀 　砀㠀　㬀ഀ
        int value = 0xaaaaaaaf;਍        猀椀稀攀开琀 琀椀洀攀开挀渀琀 㴀 挀氀漀挀欀⠀⤀㬀ഀ
        if(!sp.clear_iobuf()){਍            䴀攀猀猀愀最攀䈀漀砀⠀一唀䰀䰀Ⰰ吀䔀堀吀⠀∀ﴀ﷿﷿﷿듿ﴃ﷿﷿﷿⋿⤀Ⰰ吀䔀堀吀⠀∀圀愀爀渀椀渀最∀⤀Ⰰ　⤀㬀ഀ
            return conn_state = false;਍        紀ഀ
        sp<<cmd; sp>>value;਍        椀昀⠀挀氀漀挀欀⠀⤀ⴀ琀椀洀攀开挀渀琀㸀㤀㔀　⤀笀ഀ
            MessageBox(NULL,TEXT("FPGAδ����"),TEXT("Warning"),0);਍            爀攀琀甀爀渀 挀漀渀渀开猀琀愀琀攀 㴀 昀愀氀猀攀㬀ഀ
        }਍        椀昀⠀⠀瘀愀氀甀攀☀　砀　　　　　　　㌀⤀㴀㴀㈀⤀ഀ
            return conn_state = true;਍        攀氀猀攀笀ഀ
            sp<<0x00000100<<0x0A515080;਍            猀瀀㸀㸀瘀愀氀甀攀㬀ഀ
            if((value&0x00000003)==2)਍                爀攀琀甀爀渀 挀漀渀渀开猀琀愀琀攀 㴀 琀爀甀攀㬀ഀ
            else{਍                䴀攀猀猀愀最攀䈀漀砀⠀一唀䰀䰀Ⰰ吀䔀堀吀⠀∀䐀䐀匀됀ﴃ﷿﷿﷿⋿⤀Ⰰ吀䔀堀吀⠀∀圀愀爀渀椀渀最∀⤀Ⰰ　⤀㬀ഀ
                return conn_state = false;਍            紀ഀ
        }਍    紀ഀ
    /** conn_device END **/਍ഀ
    /** rw reg **/਍    瘀漀椀搀 眀爀椀琀攀开爀攀最⠀挀漀渀猀琀 刀攀最☀ 爀攀最⤀ഀ
    {਍        猀瀀㰀㰀爀攀最㬀ഀ
    }਍    瘀漀椀搀 眀爀椀琀攀开爀攀最⠀甀渀猀椀最渀攀搀 挀栀愀爀 愀搀搀爀Ⰰ甀渀猀椀最渀攀搀 椀渀琀 瘀愀氀甀攀⤀ഀ
    {਍        猀瀀㰀㰀愀搀搀爀㰀㰀瘀愀氀甀攀㬀ഀ
    }਍    刀攀最 爀攀愀搀开爀攀最⠀甀渀猀椀最渀攀搀 挀栀愀爀 愀搀搀爀⤀ഀ
    {਍        刀攀最 琀洀瀀㬀ഀ
        tmp.addr = addr;਍        猀瀀㸀㸀琀洀瀀㬀ഀ
        set_ps(ps);਍        爀攀琀甀爀渀 琀洀瀀㬀ഀ
    }਍    瘀漀椀搀 爀攀愀搀开爀攀最⠀刀攀最☀ 爀攀最⤀ഀ
    {਍        猀瀀㸀㸀爀攀最㬀ഀ
        set_ps(ps);਍    紀ഀ
    /**  rw reg end **/਍ഀ
    void update_hdreg() //����hdreg਍    笀ഀ
        sp.clear_iobuf();਍        昀漀爀⠀愀甀琀漀☀ 椀㨀栀搀爀攀最⤀ഀ
            sp>>i;਍        猀攀琀开瀀猀⠀瀀猀⤀㬀ഀ
    }਍ഀ
    CurrentState(SerialPort& sp):sp(sp),ps(0x48),oedi(0x50),drctl(0x44),conn_state(false)਍    笀ഀ
        for(unsigned char i=0;i<28;++i)਍            栀搀爀攀最嬀椀崀⸀愀搀搀爀 㴀 椀㬀ഀ
    }਍紀㬀ഀ
#endif // CURSTE_H_INCLUDED਍�