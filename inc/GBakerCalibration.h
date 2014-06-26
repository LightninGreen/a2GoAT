
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GDataChecks.h"

class	GBakerCalibration : public GDataChecks
{
private:
	Int_t NCluster;
	TH2* GBakerCalibHist_CB_IM;

   	
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

