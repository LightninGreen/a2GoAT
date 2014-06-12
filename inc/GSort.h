
#ifndef __GSort_h__
#define __GSort_h__

#include "GBakerCalibration.h"
#include "GoATTreeManager.h"

#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

class	GSort : public GBakerCalibration 
{
private:

	Int_t 		SortRawNParticles;	 			// Sort on-off
	Int_t  		SR_nPart_total;
	Int_t  		SR_nPart_total_condition;
    Int_t   	SR_nPart_CB;
    Int_t   	SR_nPart_CB_condition;        
    Int_t   	SR_nPart_TAPS;
    Int_t   	SR_nPart_TAPS_condition;       	
 
 	Int_t 		SortRawCBESum;	 				// Sort on-off
	Double_t  	SR_CBESum;
	Int_t  		SR_CBESum_condition;
 
    Int_t 		SortNParticles;					// Sort on-off
    Int_t 		S_nParticles;
    Int_t		S_nParticles_condition;

	Int_t		n_cut_SP;				// Sort on Particles
	Int_t*		SP_n;
	Int_t*		SP_type;
	Int_t*		SP_condition;
	Double_t* 	SP_theta_min;
	Double_t* 	SP_theta_max;

	Int_t		n_cut_SN;				// Sort on Neutrality
	Int_t*		SN_n;
	Int_t*		SN_type;
	Int_t*		SN_condition;
	Double_t* 	SN_theta_min;
	Double_t* 	SN_theta_max;
 
	char string_in1[256], string_in2[256], string_in3[256];
	std::string string_out1, string_out2, string_out3;
			    
protected:
	    
public:

	GSort();
	~GSort();

	virtual void	Analyse() {;}
	virtual void	Reconstruct();
	Bool_t	PostInit();

    Bool_t	SortAnalyseEvent();
    Bool_t	SortFillEvent();
    Bool_t 	SortOnParticle(Int_t PDG, Int_t Num, Int_t cond, Double_t ThetaMin, Double_t ThetaMax);
    Bool_t 	SortOnNeutrality(Int_t charge, Int_t Num, Int_t cond, Double_t ThetaMin, Double_t ThetaMax);    
    void	CheckConfigCondition(char string[], int *condition, std::string& string_out);
};


#endif

