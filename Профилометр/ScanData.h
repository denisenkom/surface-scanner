//---------------------------------------------------------------------------

#ifndef ScanDataH
#define ScanDataH
//---------------------------------------------------------------------------
class ScanDataView;
//---------------------------------------------------------------------------
class ScanData {
private:
	double *_data, _wstep, _lstep;
	int _wsteps, _lsteps;
	ScanDataView* _views[10];
	int _views_num;
public:
	ScanData(int wsteps, double wstep, int lsteps, double lstep);
   ScanData(std::string filename);
	virtual ~ScanData();

   void Save(std::string filename);

	//void setWSteps(int wsteps, double step);
	int getWSteps();
	double getWStep();

	//void setLSteps(int lsteps, double step);
	int getLSteps();
	double getLStep();

	double& Mass(int w, int l);

	void updateViews();

	void addView(ScanDataView* view);
};
//---------------------------------------------------------------------------
class ScanDataView {
public:
	virtual void update() = 0;
	virtual void setData(ScanData* data) = 0;
	virtual ScanData* getData() = 0;
};
//---------------------------------------------------------------------------
void ActionScan();

#endif
 