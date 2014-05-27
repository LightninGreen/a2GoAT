
#ifndef __GBakerCalibration_h__
#define __GBakerCalibration_h__

#include "GoATTreeManager.h"
#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

#define	pdg_rootino 0
#define	pdg_pi0 1
#define	pdg_eta 2
#define	pdg_etaP 3
#define	pdg_proton 4
#define	pdg_chpion 5
#define	pdg_electron 6
#define pdg_photon 7
#define pdg_neutron 8

#define m_pi0 135.0
#define	m_eta 545.0
#define	m_etaP 958.0
#define	m_proton 938.3
#define	m_chpion 139.6
#define	m_electron 0.511

class	GBakerCalibration : public GoATTreeManager
{
private:


	Int_t* 	        Identified;
	Int_t*	        Charge;	

	Int_t 		nParticles;
	Int_t 		nDaughterList;
   	Int_t 		i;
   	
protected:
	    
public:

	GBakerCalibration();
	~GBakerCalibration();
	
	virtual void Reconstruct();

};


#endif

