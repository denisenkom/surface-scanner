//---------------------------------------------------------------------------

#ifndef DriverH
#define DriverH
//---------------------------------------------------------------------------
enum ebutton {start_scan_btn, stop_scan_btn,
   reverse_btn, set_base_length_btn, high_freq_btn,
   low_freq_btn, increase_btn, decrease_btn, turn_on_btn,
   filter_scale_btn, ra_btn, rz_btn, rmax_btn, rp_btn,
   sm_btn, display_btn, t5_btn, t10_btn, t20_btn, t30_btn, t40_btn,
   t50_btn, t60_btn, t70_btn, t80_btn, t90_btn};

struct button
{
   ebutton id;
   std::string name;
   BYTE code;
   button() {}
   button(ebutton id, std::string name, BYTE code)
      : id(id), name(name), code(code)
   { }
};
typedef std::map<ebutton, button> t_buttons;
extern t_buttons buttons;
extern double acp_mult;

void SetSDStepsPerMm(double);
double GetSDStepsPerMm();

void SetPortName(LPCTSTR);
String GetPortName();
void SetPortMode(LPCTSTR);
String GetPortMode();

void TestProfilom();
void ReadADC(std::vector<double> &values);
double GetPlatePosition();
void DisplacePlate(double disp);
String ReadDisplay();

void PushButton(ebutton);

#endif
