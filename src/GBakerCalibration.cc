
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
	NCluster = GetClusterSize(0);
	TLorentzVector p4Gamma1;
	p4Gamma1 = GetVector(0);
		
	for(Int_t j = 1; j < NCluster; j++)
	{
		TLorentzVector p4Gamma2;
		p4Gamma2 = GetVector(j);
		Double_t im = (p4Gamma1 + p4Gamma2).M();
		GBakerCalibHist_CB_IM->Fill(im, GetCentralIndex(0));
		GBakerCalibHist_CB_IM->Fill(im, GetCentralIndex(j));
	}
}

void   GBakerCalibration::DefineHistograms()
{

	cout << "Defining GBakerCalibration histograms." << endl;

	gROOT->cd();

	GBakerCalibHist_CB_IM = new TH2F("GBakerCalibHist_CB_IM", "GBakerCalib CB Energy IM", 1000, 0, 1000, 720, 0, 720);

}

Bool_t    GBakerCalibration::WriteHistograms()
{

	cout << "Writing GBakerCalibration histograms." << endl;

	if(!GoATFile) return kFALSE;
	GoATFile->cd();

	GBakerCalibHist_CB_IM->Write();

	return kTRUE;
}
