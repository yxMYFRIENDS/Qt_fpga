#ifndef PROFIL_H_INCLUDED
#define PROFIL_H_INCLUDED
#include<curste.h>
#ifdef Debug
#include<my.h>
#endif // Debug
class Profil{
    double& sys_freq;
    int& auto_io_update;
    CurrentState& cs;
    Reg profiles[8][2];
    Reg cf2;
    int valid_profil;
public:
    void enable(int i); // i= 0,1
    void select_profile(int i); //i=0-7
    void change_profile(int type,double value); //type=0-2,
    int get_enable();
    int get_select();
    std::vector<std::vector<double> > get_profiles();

    Profil(BaseSet& bs):cs(bs.get_cur_state()),sys_freq(bs.get_sys_freq()),auto_io_update(bs.get_auto_ioupdate())
    {
        cf2.addr = 0x01;
        cs.read_reg(cf2);
        for(int i=0;i<8;++i){
            profiles[i][0].addr = i*2+0x0b;
            profiles[i][1].addr = i*2+0x0b+1;
            cs.read_reg(profiles[i][0]);
            cs.read_reg(profiles[i][1]);
        }
    }
};

void Profil::enable(int i)
{
    if(i) cf2.value = 0x00800000|cf2.value&0xFFF6FFFF;
    else cf2.value = 0xFF7FFFFF&cf2.value;
    cs.write_reg(cf2);
#ifdef Debug
    pf(cf2);
#endif // Debug
    cs.io_update();
}
int Profil::get_enable()
{
    return (cf2.value&0x00800000)>>23;
}
void Profil::select_profile(int i)
{
    cs.set_ps(i);
}
int Profil::get_select()
{
    return cs.get_ps();
}
void Profil::change_profile(int type,double value)
{
    int ps = get_select();
    if(type==0)
        profiles[ps][0].value = (unsigned int)(1.0*(1<<12)/sys_freq*(1<<20)*value);
    else if(type==1)
        profiles[ps][1].value = ((unsigned int)(value*(1<<13)/45))|(profiles[ps][1].value&0xffff0000);
    else
        profiles[ps][1].value = (profiles[ps][1].value&0xF000FFFF)|((unsigned int)(value*(1<<12)))<<16;

    if(type)
        cs.write_reg(profiles[ps][1]);
    else
        cs.write_reg(profiles[ps][0]);
#ifdef Debug
    pf(ps);
    if(type) pf(profiles[ps][1]);
    else pf(profiles[ps][0]);
#endif // Debug
    if(auto_io_update) cs.io_update();
}
std::vector<std::vector<double> > Profil::get_profiles()
{
    std::vector<std::vector<double> > ret(8,std::vector<double>());
    for(int i=0;i<8;++i){
        ret[i].push_back(sys_freq/(1<<16)/(1<<16)*profiles[i][0].value);
        ret[i].push_back(1.0*(profiles[i][1].value&0x0000ffff)/(1<<13)*45);
        ret[i].push_back(1.0*(profiles[i][1].value&0x0FFF0000)/(1<<28));
    }
    return ret;
}
#endif // PROFIL_H_INCLUDED
