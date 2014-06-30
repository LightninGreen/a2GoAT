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
	
	//Loop over CB hits
	for(Int_t i = 0; i < GetNParticles(); i++)
	{	
		//Loop over CB hits
		for(Int_t j = i+1; j < GetNParticles(); j++)
		{
			//Check that both particles came from Crystal Ball
			if(GetApparatus(i) == EAppCB && GetApparatus(j) == EAppCB)
			{
				//Calculate invariant mass from 4-vector
				im = (GetVector(i) + GetVector(j)).M();	
					
				//Fill histogram
				GBakerCalibHist_CB_IM->Fill(im, GetCentralCrys(i));
				GBakerCalibHist_CB_IM->Fill(im, GetCentralCrys(j));
				
				//Fill histogram for neutral hits
				if(GetWC0_E(i) == 0 && GetWC1_E(i) == 0 && GetWC0_E(j) == 0 && GetWC1_E(j) == 0)
				{
					GBakerCalibHist_CB_IM_Neut->Fill(im, GetCentralCrys(i));
					GBakerCalibHist_CB_IM_Neut->Fill(im, GetCentralCrys(j));
				}
				
				//Fill histogram for 2 neutral hits
				if(GetNParticles() == 2 && GetWC0_E(i) == 0 && GetWC1_E(i) == 0 && GetWC0_E(j) == 0 && GetWC1_E(j) == 0)
				{
					GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(i));
					GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(j));
				
				}
			}
		}	
	}
}	
	
void   GBakerCalibration::DefineHistograms()
{

	cout << "Defining GBakerCalibration histograms." << endl;

	gROOT->cd();

	GBakerCalibHist_CB_IM = new TH2F("GBakerCalibHist_CB_IM", "GBakerCalib CB Energy IM", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_Neut = new TH2F("GBakerCalibHist_CB_IM_Neut", "GBakerCalib CB Energy IM Neutral", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_2Neut = new TH2F("GBakerCalibHist_CB_IM_2Neut", "GBakerCalib CB Energy IM 2 Neutral", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_2Neut_1Char = new TH2F("GBakerCalibHist_CB_IM_2Neut_1Char", "GBakerCalib CB Energy IM 2 Neutral + 1 Charged", 1000, 0, 1000, 720, 0, 720);

}

Bool_t    GBakerCalibration::WriteHistograms()
{
	
	cout << "Writing GBakerCalibration histograms." << endl;
	
	if(!GoATFile) return kFALSE;
	GoATFile->cd();
	gROOT->GetList()->Write();
	gROOT->GetList()->Delete();
	
	return kTRUE;
}                                                                                                          
