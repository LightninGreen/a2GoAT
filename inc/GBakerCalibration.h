
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GDataChecks.h"

class	GBakerCalibration : public GDataChecks
{
private:
	Double_t Pi0_IM;
   	
protected:
	    
public:

	GBakerCalibration();
	~GBakerCalibration();
	
	virtual void Reconstruct();

	Bool_t PostInit();

};


#endif

