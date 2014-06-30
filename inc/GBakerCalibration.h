
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GDataChecks.h"

class	GBakerCalibration : public GDataChecks
{
private:

	Double_t im;
	Int_t* charge;
	Int_t nCharged;
	Int_t nNeutral;
	
	TH2* GBakerCalibHist_CB_IM;
	TH2* GBakerCalibHist_CB_IM_Neut;
	TH2* GBakerCalibHist_CB_IM_2Neut;
	TH2* GBakerCalibHist_CB_IM_2Neut_1Char;
   	
protected:
	    
public:

	GBakerCalibration();
	~GBakerCalibration();
	
	virtual void Reconstruct();

	Bool_t PostInit();

	void   LabelCharged();
	void   DefineHistograms();
	Bool_t WriteHistograms();

};


#endif

