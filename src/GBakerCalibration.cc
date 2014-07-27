#include "GBakerCalibration.h"

GBakerCalibration::GBakerCalibration() 
{
}

GBakerCalibration::~GBakerCalibration()
{
}

Bool_t GBakerCalibration::PostInit()
{
//DefineHistograms(); (Currently called within GoAT.cc)
return kTRUE;
}


void	GBakerCalibration::Reconstruct()
{
	
	EventStartup();
	
	//CB Energy Calibration
	if(CB_Energy_Calib == 1)
	{
		//Loop over hits
		for(Int_t i = 0; i < GetNParticles(); i++)
		{	
			//Loop over hits
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
	}

	//CB Time Calibration
	if(CB_Time_Calib == 1)
	{
		//Loop over hits
		for(Int_t i = 0; i < GetNParticles(); i++)
		{
			//Get the time
			time_i = GetTime(i);
			//Loop over hits
			for(Int_t j = 0; j < GetNParticles(); j++)
			{
				//Get the time
				time_j = GetTime(j);
				//Ensure both hits are from CB
				if(GetApparatus(i) == EAppCB && GetApparatus(j) == EAppCB)
				{
					//Fill histogram
					GBakerCalibHist_CB_Time->Fill(time_i - time_j, GetCentralCrys(i));
					GBakerCalibHist_CB_Time->Fill(time_j - time_i, GetCentralCrys(j));
					//Fill histogram for only two neutral hits
					if(charge[i] == 0 && charge[j] == 0)
					{
						GBakerCalibHist_CB_Time_Neut->Fill(time_i - time_j, GetCentralCrys(i));
						GBakerCalibHist_CB_Time_Neut->Fill(time_j - time_i, GetCentralCrys(j));
					}
				}
			}
		}
	}

	//TAPS Energy Calibration
	if(TAPS_Energy_Calib == 1)
	{
		//Loop over hits
		for(Int_t i = 0; i < GetNParticles(); i++)
		{
			//Loop over hits
			for(Int_t j = 0; j < GetNParticles(); j++)
			{
				//Calculate the invariant mass
				im = (GetVector(i) + GetVector(j)).M();
				if(GetApparatus(i) == EAppCB && GetApparatus(j) == EAppTAPS)
				{	
					GBakerCalibHist_TAPS_IM->Fill(im, GetCentralCrys(j));
					if(charge[i] == 0 && charge[j] == 0)
					{
						GBakerCalibHist_TAPS_IM_Neut->Fill(im, GetCentralCrys(j));
						if(nNeutral == 2)
						{
							GBakerCalibHist_TAPS_IM_2Neut->Fill(im, GetCentralCrys(j));
						}
					}
				}
				else if(GetApparatus(i) == EAppTAPS && GetApparatus(j) == EAppCB)
				{
					GBakerCalibHist_TAPS_IM->Fill(im, GetCentralCrys(i));
					if(charge[i] == 0 && charge[j] == 0)
					{
						GBakerCalibHist_TAPS_IM_Neut->Fill(im, GetCentralCrys(i));
						if(nNeutral == 2)
						{
							GBakerCalibHist_TAPS_IM_2Neut->Fill(im, GetCentralCrys(i));
						}
					}
				}
			}
		}
	}

	//TAPS Time Calibration
	if(TAPS_Time_Calib == 1)
	{
		//Loop over hits
		for(Int_t i = 0; i < GetNParticles(); i++)
		{
			//Get the time
			time_i = GetTime(i);
			//Loop over hits
			for(Int_t j = 0; j < GetNParticles(); j++)
			{
				//Get the time
				time_j = GetTime(j);
				//Ensure both hits are from TAPS
				if(GetApparatus(i) == EAppTAPS && GetApparatus(j) == EAppTAPS)
				{
					//Fill histogram
					GBakerCalibHist_TAPS_Time->Fill(time_i - time_j, GetCentralCrys(i));
					GBakerCalibHist_TAPS_Time->Fill(time_j - time_i, GetCentralCrys(j));
					//Fill histogram for only neutral hits
					if(charge[i] == 0 && charge[j] == 0)
					{
						GBakerCalibHist_TAPS_Time_Neut->Fill(time_i - time_j, GetCentralCrys(i));
						GBakerCalibHist_TAPS_Time_Neut->Fill(time_j - time_i, GetCentralCrys(j));
					}
				}
			}
		}
	}

	EventCleanup();

}	

void   GBakerCalibration::EventStartup()
{
		CB_Energy_Calib = 1;
		CB_Time_Calib = 1;
		TAPS_Energy_Calib = 1;
		TAPS_Time_Calib = 1;
		
		LabelCharged();
		
}
	
void   GBakerCalibration::EventCleanup()
{
		
		delete [] charge;
		
}

void   GBakerCalibration::LabelCharged()
{
	//This function labels the charge for each particle in an event,
	//As well as counting the total number of neutral hits and charged hits
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
	
void   GBakerCalibration::DefineHistograms()
{

	cout << "Defining GBakerCalibration histograms." << endl;

	gROOT->cd();

	//CB Energy Calibration

	GBakerCalibHist_CB_IM = new TH2F("GBakerCalibHist_CB_IM", "GBakerCalib CB Energy IM;Energy [MeV];CB Index", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM->SetStats(kFALSE);
	GBakerCalibHist_CB_IM_Neut = new TH2F("GBakerCalibHist_CB_IM_Neut", "GBakerCalib CB Energy IM Neutral;Energy [MeV];CB Index", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_Neut->SetStats(kFALSE);
	GBakerCalibHist_CB_IM_2Neut = new TH2F("GBakerCalibHist_CB_IM_2Neut", "GBakerCalib CB Energy IM 2 Neutral;Energy [MeV];CB Index", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_2Neut->SetStats(kFALSE);
	GBakerCalibHist_CB_IM_2Neut_1Char = new TH2F("GBakerCalibHist_CB_IM_2Neut_1Char", "GBakerCalib CB Energy IM 2 Neutral + 1 Charged;Energy [MeV];CB Index", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_CB_IM_2Neut_1Char->SetStats(kFALSE);

    //CB Time Calibration

    GBakerCalibHist_CB_Time = new TH2F("GBakerCalibHist_CB_Time", "GBakerCalib CB Time;CB cluster time [ns];CB element", 10000, -1000, 1000, 720, 0, 720);
    GBakerCalibHist_CB_Time->SetStats(kFALSE);
    GBakerCalibHist_CB_Time_Neut = new TH2F("GBakerCalibHist_CB_Time_Neut", "GBakerCalib CB Time Neutral;CB cluster time [ns];CB element", 10000, -1000, 1000, 720, 0, 720);
	GBakerCalibHist_CB_Time_Neut->SetStats(kFALSE);

	//TAPS Energy Calibration
	
	GBakerCalibHist_TAPS_IM = new TH2F("GBakerCalibHist_TAPS_IM", "GBakerCalib TAPS Energy IM", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_TAPS_IM->SetStats(kFALSE);
	GBakerCalibHist_TAPS_IM_Neut = new TH2F("GBakerCalibHist_TAPS_IM_Neut", "GBakerCalib TAPS Energy IM Neutral", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_TAPS_IM_Neut->SetStats(kFALSE);
	GBakerCalibHist_TAPS_IM_2Neut = new TH2F("GBakerCalibHist_TAPS_IM_2Neut", "GBakerCalib TAPS Energy IM 2 Neutral", 1000, 0, 1000, 720, 0, 720);
	GBakerCalibHist_TAPS_IM_2Neut->SetStats(kFALSE);
	
	//TAPS Time Calibration

	GBakerCalibHist_TAPS_Time = new TH2F("GBakerCalibHist_TAPS_Time", "GBakerCalib TAPS Time", 10000, -1000, 1000, 720, 0, 720);
    GBakerCalibHist_TAPS_Time->SetStats(kFALSE);
    GBakerCalibHist_TAPS_Time_Neut = new TH2F("GBakerCalibHist_TAPS_Time_Neut", "GBakerCalib TAPS Time Neutral", 10000, -1000, 1000, 720, 0, 720);
	GBakerCalibHist_TAPS_Time_Neut->SetStats(kFALSE);
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
