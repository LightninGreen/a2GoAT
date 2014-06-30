
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GDataChecks.h"

class	GBakerCalibration : public GDataChecks
{
private:
	Int_t NParticle;
	TH2* GBakerCalibHist_CB_IM;
	TH2* GBakerCalibHist_CB_IM_2Neut;
	TLorentzVector p4Gamma1, p4Gamma2;
   	
protected:
	    
public:

	GBakerCalibration();
	~GBakerCalibration();
	
	virtual void Reconstruct();

	Bool_t PostInit();

	void   DefineHistograms();
	Bool_t WriteHistograms();

};


#endif

