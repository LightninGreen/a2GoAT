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
	
	LabelCharged();
	
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
				if(charge[i] == 0 && charge[j] == 0)
				{
					GBakerCalibHist_CB_IM_Neut->Fill(im, GetCentralCrys(i));
					GBakerCalibHist_CB_IM_Neut->Fill(im, GetCentralCrys(j));
				}
				
				//Fill histogram for 2 neutral hits
				if(GetNParticles() == 2 && charge[i] == 0 && charge[j] == 0)
				{
					GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(i));
					GBakerCalibHist_CB_IM_2Neut->Fill(im, GetCentralCrys(j));
				
				}
				
				//Fill histogram for 2 neutral hits and 1 charged hit
				if(GetNParticles() == 3 && nCharged == 1 && nNeutral ==2 && charge[i] == 0 && charge[j] == 0)
				{
					GBakerCalibHist_CB_IM_2Neut_1Char->Fill(im, GetCentralCrys(i));
					GBakerCalibHist_CB_IM_2Neut_1Char->Fill(im, GetCentralCrys(j));
				}
			}
		}	
	}

	EventCleanup();

}	

void   GBakerCalibration::LabelCharged()
{
	nCharged = 0;
	nNeutral = 0;
	charge = new Int_t[GetNParticles()];
	
	for(Int_t n = 0; n < GetNParticles(); n++)
	{
		charge[n] = 0;
		if(GetApparatus(n) == EAppCB)
		{
			if((GetWC0_E(n) > 0.0) || (GetWC1_E(n) > 0.0))
			{
				charge[n] = 1;
			}
			if((Get_dE(n) > 0.0) && (Get_dE(n) < 1000.0))
			{
				charge[n] = 1;
			}
		}
		if(GetApparatus(n) == EAppTAPS)
		{
			if((Get_dE(n) > 0.0) && (Get_dE(n) < 1000.0))
			{
				charge[n] = 1;
			}
		}
		if(charge[n] == 0)
		{
			nNeutral++;
		}
		if(charge[n] == 1)
		{
			nCharged++;
		}	
	}	
}
	
void   GBakerCalibration::EventCleanup()
{
		
		delete [] charge;
		
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
