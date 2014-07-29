
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GDataChecks.h"

class	GBakerCalibration : public GDataChecks
{
private:

	Int_t Target_Position;
	Int_t CB_Energy_Calib;
	Int_t CB_Quad_Energy_Calib;
	Int_t CB_Time_Calib;
	Int_t TAPS_Energy_Calib;
	Int_t TAPS_Quad_Energy_Calib;
	Int_t TAPS_Time_Calib;

	Double_t targetPos;
	Double_t im;
	Double_t meanE;
	Double_t theta;
	Double_t time_i;
	Double_t time_j;
	
	Int_t goodEvent;
	Int_t indexTAPS;
	Int_t indexCB;
	
	Int_t* charge;
	Int_t nCharged;
	Int_t nNeutral;
	
	TH2* GBakerCalibHist_Target_Pos;
	
	TH2* GBakerCalibHist_CB_IM;
	TH2* GBakerCalibHist_CB_IM_Neut;
	TH2* GBakerCalibHist_CB_IM_2Neut;
	TH2* GBakerCalibHist_CB_IM_2Neut_1Char;

	TH2* GBakerCalibHist_CB_Quad_IM;
	TH2* GBakerCalibHist_CB_Quad_Pi0_Mean_E;
	TH2* GBakerCalibHist_CB_Quad_Eta_Mean_E;

	TH2* GBakerCalibHist_CB_Time;
	TH2* GBakerCalibHist_CB_Time_Neut;
    
	TH2* GBakerCalibHist_TAPS_IM;
	TH2* GBakerCalibHist_TAPS_IM_Neut;
	TH2* GBakerCalibHist_TAPS_IM_2Neut;
	
	TH2* GBakerCalibHist_TAPS_Quad_IM;
	TH2* GBakerCalibHist_TAPS_Quad_Pi0_Mean_E;
	TH2* GBakerCalibHist_TAPS_Quad_Eta_Mean_E;
    
 	TH2* GBakerCalibHist_TAPS_Time;
 	TH2* GBakerCalibHist_TAPS_Time_Neut;
   	
protected:
	    
public:

	GBakerCalibration();
	~GBakerCalibration();
	
	virtual void Reconstruct();

	Bool_t PostInit();

	void   LabelCharged();
	void   EventStartup();
	void   EventCleanup();
	void   DefineHistograms();
	Bool_t WriteHistograms();

};


#endif

