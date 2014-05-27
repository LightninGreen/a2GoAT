
#include "GBakerCalibration.h"


GBakerCalibration::GBakerCalibration() :
							Identified(0),
                                                        nParticles(0),
                                                        nDaughterList(0),
                                                        Charge(0)

{
        Identified      = new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
        Charge          = new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
}


GBakerCalibration::~GBakerCalibration()
{
}

void	GBakerCalibration::Reconstruct()
{
}
