#include "Sweep.h"
Sweep::Sweep(BaseSet& bs):cs(bs.get_cur_state()),sys_freq(bs.get_sys_freq()),auto_io_update(bs.get_auto_ioupdate())
{
    cf2 = cs.read_reg(0x01);
    lsp0 = cs.read_reg(0x04);
    lsp1 = cs.read_reg(0x05);
    rs = cs.read_reg(0x06);
    fs = cs.read_reg(0x07);
    ts = cs.read_reg(0x08);
    sk0 = cs.read_reg(0x09);
    sk1 = cs.read_reg(0x0A);
#ifdef Debug
    cf2.value = 0x00084B00; lsp0.value = 0x01409a24;
    lsp1.value = 0x2e2328f9; rs.value = 0x001f7510;
    fs.value = 0x00353719; ts.value = 0x00800005;
    sk0.value = 0x0260f5e4; sk1.value = 0x178e7726;
#endif // Debug
    rmap[0] = &lsp0; rmap[1] = &lsp1;
    rmap[2] = &rs;   rmap[3] = &fs;
    rmap[4] = &ts;   rmap[5] = &ts;
    rmap[6] = &sk0;  rmap[7] = &sk1;
    set_mode(0);
}
void Sweep::enable(int i)
{
    cf2.value = i?(0x00082000|cf2.value&0xFFFEFFFF):(cf2.value&0xFFF7FFFF);
#ifdef Debug
    pf(cf2);
#endif // Debug
    cs.write_reg(cf2);
    cs.io_update();
}
void Sweep::enable_fj(int i)
{
    cf2.value = (cf2.value&0xFFFFBFFF)|(i&0x01)<<14;
#ifdef Debug
    pf(cf2);
#endif // Debug
    cs.write_reg(cf2);
    cs.io_update();
}
void Sweep::set_mode(int i)
{
    mode = i&0x03;
    cf2.value = (cf2.value&0xFFCFFFFF)|(mode<<20);
#ifdef Debug
    pf(cf2);
#endif // Debug
    cs.write_reg(cf2);
    cs.io_update();
    switch(mode)
    {
        case 0:
            va0 = sys_freq/(1<<16)/(1<<16)*lsp0.value;
            va1 = sys_freq/(1<<16)/(1<<16)*lsp1.value;
            va2 = sys_freq/(1<<16)/(1<<16)*rs.value;
            va3 = sys_freq/(1<<16)/(1<<16)*fs.value;
            va4 = 1.0*24*(ts.value>>16)/sys_freq;
            va5 = 1.0*24*(ts.value&0x0000ffff)/sys_freq;
            va6 = sys_freq/(1<<16)/(1<<16)*sk0.value;
            va7 = sys_freq/(1<<16)/(1<<16)*sk1.value;
            break;
        case 1:
            break;
        default: break;
    }
}
void Sweep::set_Dwell_High(int i)
{
    cf2.value = (cf2.value&0xFFFBFFFF)|(i&0x01)<<18;
    cs.write_reg(cf2);
    cs.io_update();
}
void Sweep::set_Dwell_Low(int i)
{
    cf2.value = (cf2.value&0xFFFDFFFF)|(i&0x01)<<17;
    cs.write_reg(cf2);
    cs.io_update();
}
void Sweep::set_auto_drctl(int i)
{
    cs.set_auto_drctl(i);
}
void Sweep::set_drctl(int i)
{
    cs.set_drctl(i);
}
void Sweep::change_value(int id,double value)
{
    switch(mode)
    {
        case 0:
            if(id==4)
                rmap[4]->value = (rmap[4]->value&0xffff0000)|(0x0000ffff&((unsigned int)(1.0*value*sys_freq/24)));
            else if(id==5)
                rmap[5]->value = (rmap[5]->value&0x0000ffff)|(0xffff0000&((unsigned int)(1.0*value*sys_freq/24))<<16);
            else
                rmap[id]->value = (unsigned int)(1.0*(1<<12)/sys_freq*(1<<20)*value);
            cs.write_reg(*(rmap[id]));
            break;
        case 1:

        case 2:

        default:break;
    }
#ifdef Debug
    pf(*rmap[id]);
#endif // Debug
    if(auto_io_update) cs.io_update();
}
std::map<std::string,std::string> Sweep::get_info()
{
    std::map<std::string,std::string> res;
    std::string s;
    std::stringstream st;
    st<<mode;
    st>>s;

    res["mode"] = s;

    if(cf2.value&1<<19)
        res["Enable_DRG"] = "1";
    else
        res["Enable_DRG"] = "0";

    if(cf2.value&1<<14)
        res["Enable_freq_jump"] = "1";
    else
        res["Enable_freq_jump"] = "0";

    if(cf2.value&1<<18)
        res["No_dwell_high"] = "1";
    else
        res["No_dwell_high"] = "0";

    if(cf2.value&1<<17)
        res["No_dwell_low"] = "1";
    else
        res["No_dwell_low"] = "0";

    if(cs.get_auto_drctl())
        res["auto_drctl"] = "1";
    else
        res["auto_drctl"] = "0";

    if(cs.get_drctl())
        res["drctl"] = "1";
    else
        res["drctl"] = "0";

    double dtmp[8] = {va0,va1,va2,va3,va4,va5,va6,va7};
    std::string stmp[8] = {"va0","va1","va2","va3","va4","va5","va6","va7"};
    for(int i=0;i<8;++i){
        std::stringstream st;
        std::string s;
        st<<dtmp[i];
        st>>s;
        res[stmp[i]] = s;
    }
    return res;
}
