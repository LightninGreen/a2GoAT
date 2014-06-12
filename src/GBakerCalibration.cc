
#include "GBakerCalibration.h"


GBakerCalibration::GBakerCalibration() :
				Pi0_IM(0)

{
}

GBakerCalibration::~GBakerCalibration()
{
}

Bool_t GBakerCalibration::PostInit()
{

return kTRUE;
}


void	GBakerCalibration::Reconstruct()
{
	
	// DO CB Energy Cal
	if (GetNParticles() == 2)
	{
		// Check 2 CB
		if ((GetApparatus(0) == 1) && (GetApparatus(1) == 1))
		{
			// Check pi0 IM
			TLorentzVector p4test = GetVector(0) + GetVector(1);
			if(p4test.M() >125.0 && p4test.M() < 145.0)
			{
				cout << "Pi0!  " << p4test.M() << endl;
			}
		}
	}

}


