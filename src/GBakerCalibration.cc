
#include "GBakerCalibration.h"


GBakerCalibration::GBakerCalibration() 
{
}

GBakerCalibration::~GBakerCalibration()
{
}

Bool_t GBakerCalibration::PostInit()
{
DefineHistograms();
return kTRUE;
}


void	GBakerCalibration::Reconstruct()
{
	//CB Energy Calibration
	NParticle = GetNParticles();

	for(Int_t i = 0; i < NParticle; i++)
	{

		p4Gamma1 = GetVector(i);
		
		for(Int_t j = i+1; j < NParticle; j++)
		{

		p4Gamma2 = GetVector(j);
		Double_t im = (p4Gamma1 + p4Gamma2).M();
		
		if(GetApparatus(i) == EAppCB && GetApparatus(j) == EAppCB)
			{
		
			GBakerCalibHist_CB_IM->Fill(im, GetCentralCrys(i));
			GBakerCalibHist_CB_IM->Fill(im, GetCentralCrys(j));

			}	
		}
	}

	if(GetNParticles() == 2)
	{	
	Double_t im = (GetVector(0) + GetVector(1)).M();
	
		if(GetApparatus(0) == EAppCB && GetApparatus(1) == EAppCB)
		
		{
			GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(0));
			GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(1));
		}
	}

}

void   GBakerCalibration::DefineHistograms()
{

	cout << "Defining GBakerCalibration histograms." << endl;

	gROOT->cd();

	GBakerCalibHist_CB_IM = new TH2F("GBakerCalibHist_CB_IM", "GBakerCalib CB Energy IM", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_2Neut = new TH2F("GBakerCalibHist_CB_IM_2Neut", "GBakerCalib CB Energy IM 2 Neutral", 1000, 0, 1000, 720, 0, 720);

}

Bool_t    GBakerCalibration::WriteHistograms()
{

	cout << "Writing GBakerCalibration histograms." << endl;

	if(!GoATFile) return kFALSE;
	GoATFile->cd();

	GBakerCalibHist_CB_IM->Write();
	GBakerCalibHist_CB_IM_2Neut->Write();

	return kTRUE;
}
