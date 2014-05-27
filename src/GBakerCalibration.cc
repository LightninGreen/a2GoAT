
#include "GBakerCalibration.h"


GBakerCalibration::GBakerCalibration() :
							Identified(0),
							nParticles(0),
							nDaughterList(0),
							Charge(0)
{
	Identified 	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
	Charge	 	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
}

GBakerCalibration::~GBakerCalibration()
{
}

Bool_t	GBakerCalibration::PostInit()
{
	cout << endl << "GBakerCalibration turned ON" << endl;

	config = ReadConfig("Do-Charged-Particle-Reconstruction");	
	if (strcmp(config.c_str(), "nokey") == 0) ReconstructChargedParticles = 0;	
	else if(sscanf( config.c_str(), "%d %lf %lf\n", 
		 &ReconstructChargedParticles,&charged_theta_min,&charged_theta_max) == 3)
	{
		cout << "Charged particle reconstruction is active over theta range [" << 
		charged_theta_min << "," << charged_theta_max <<"]" << endl;
	}	
	else if(sscanf( config.c_str(), "%d \n",  &ReconstructChargedParticles) == 1)
	{
		charged_theta_min = 0.0;
		charged_theta_max = 180.0;
	}
	else 
	{
		cout << "ERROR: Do-Charged-Particle-Reconstruction set improperly" << endl;
		return kFALSE;
	}
	
	if (ReconstructChargedParticles == 1) 
	{
		cout << "Full Charged particle reconstruction is active" << endl;
		
		config = ReadConfig("Cut-dE-E-CB-Proton");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_proton_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_proton_active = 1;
                Cut_CB_proton = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Proton set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-CB-Pion");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_pion_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_pion_active = 1;
                Cut_CB_pion = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Pion set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-CB-Electron");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_electron_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_electron_active = 1;
                Cut_CB_electron = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Electron set improperly" << endl;
			return kFALSE;
		}
		
		config = ReadConfig("Cut-dE-E-TAPS-Proton");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_proton_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_proton_active = 1;
                Cut_TAPS_proton = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Proton set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-TAPS-Pion");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_pion_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_pion_active = 1;
                Cut_TAPS_pion = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Pion set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-TAPS-Electron");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_electron_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_electron_active = 1;
                Cut_TAPS_electron = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Electron set improperly" << endl;
			return kFALSE;
		}
		
	}
	else cout << "Charged particle reconstruction is NOT active." << endl;
	cout << endl;
	
	config = ReadConfig("Do-Meson-Reconstruction");	
	if (strcmp(config.c_str(), "nokey") == 0) ReconstructMesons = 0;	
	else if(sscanf( config.c_str(), "%d %lf %lf\n", 
		 &ReconstructMesons,&meson_theta_min, &meson_theta_max) == 3)
	{
		cout << "meson reconstruction is active over theta range [" << 
		meson_theta_min << "," << meson_theta_max <<"]" << endl;
	}
	else if(sscanf( config.c_str(), "%d \n",  &ReconstructMesons) == 1)
	{
		cout << "Full meson reconstruction is active" << endl;
		meson_theta_min = 0.0;
		meson_theta_max = 180.0;
	}
	else 
	{
		cout << "ERROR: Do-Meson-Reconstruction set improperly" << endl;
		return kFALSE;
	}
	

	if (ReconstructMesons == 1) 
	{
		config = ReadConfig("Cut-IM-Width-Pi0");	
		sscanf( config.c_str(), "%lf\n", &width_pi0);
		if(width_pi0) cout << "Pi0 IM width cut set to " << width_pi0 << " MeV" << endl;
		else 
		{
			width_pi0 = DEFAULT_PI0_IM_WIDTH; 
			cout << "Pi0 IM width cut set to default (" << width_pi0 << " MeV)" << endl;
		}

		config = ReadConfig("Cut-IM-Width-Eta");	
		sscanf( config.c_str(), "%lf\n", &width_eta);
		if(width_pi0) cout << "Eta IM width cut set to " << width_eta << " MeV" << endl;
		else 
		{
			width_eta = DEFAULT_ETA_IM_WIDTH; 
			cout << "Pi0 IM width cut set to default (" << width_eta << " MeV)" << endl;
		}

		config = ReadConfig("Cut-IM-Width-Eta-Prime");	
		sscanf( config.c_str(), "%lf\n", &width_etaP);
		if(width_etaP) cout << "Eta-Prime IM width cut set to " << width_etaP << " MeV" << endl;
		else 
		{
			width_etaP = DEFAULT_ETAP_IM_WIDTH; 
			cout << "Eta-Prime IM width cut set to default (" << width_etaP << " MeV)" << endl;
		}		
		cout << endl;
	}
	else cout << "Meson reconstruction is NOT active." << endl;	

	return kTRUE;
}

void	GBakerCalibration::Reconstruct()
{
}

void	GBakerCalibration::InitEvent()
{
	nParticles = 0; 	SetNParticles(nParticles);
	nDaughterList = 0; 	SetNDaughterList(nDaughterList);

	// Mark everything as rootino	
	for (int i = 0; i < GetNParticles(); i++)
	{
		Identified[i] = pdg_rootino; 
		SetInputMass(i,0.0);
	}	
}

void 	GBakerCalibration::CheckNeutrality()
{

	// Rough start, this will soon be user controlled
	Bool_t considerPID 	= kFALSE;
	Bool_t considerMWPC = kTRUE;
	Bool_t considerVETO = kTRUE;

	for (int i = 0; i < GetNParticles(); i++)
	{
		Charge[i] = 0;
		if(GetApparatus(i) == EAppCB)
		{
			if(considerMWPC == kTRUE)
			{
				if ((GetWC0_E(i) > 0.0) || (GetWC1_E(i) > 0.0)) 	Charge[i] = 1;
			}
			if(considerPID == kTRUE)
			{
				if ((Get_dE(i) > 0.0) && (Get_dE(i) < 1000.0)) 		Charge[i] = 1; 
			}

		}
		if(GetApparatus(i) == EAppTAPS)
		{
			if(considerVETO == kTRUE)
			{
				if ((Get_dE(i) > 0.0) && (Get_dE(i) < 1000.0)) 		Charge[i] = 1;
			}
		}			
	}
}

void	GBakerCalibration::AddParticle(Int_t pdg_code, Int_t nindex, Int_t index_list[])
{

	TLorentzVector part  = GetVector(index_list[0]);
	
	Double_t Ek			 = GetEk(index_list[0]);
	Double_t time		 = GetTime(index_list[0]);
	Double_t dE 		 = Get_dE(index_list[0]);
	Double_t WCO_E 		 = GetWC0_E(index_list[0]);	
	Double_t WC1_E 		 = GetWC1_E(index_list[0]);	
		
	Double_t WC_Vertex_X = GetWC_Vertex_X(index_list[0]);
	Double_t WC_Vertex_Y = GetWC_Vertex_Y(index_list[0]);	
	Double_t WC_Vertex_Z = GetWC_Vertex_Z(index_list[0]);
	
	Int_t 	 clusterSize = GetClusterSize(index_list[0]);
	UChar_t  Apparatus   = GetApparatus(index_list[0]);
	Int_t  	 SumCharge   = Charge[index_list[0]];
	
	Int_t	 ndaughters  = 0;
	if (nindex > 1) 
	{	
		// store in daughter list for meson analysis
		SetDaughter_index(nDaughterList,nParticles);
		SetDaughter_E(nDaughterList,	 GetEk(index_list[0]));
		SetDaughter_Theta(nDaughterList, GetTheta(index_list[0]));
		SetDaughter_Phi(nDaughterList,	 GetPhi(index_list[0]));
		SetDaughter_PDG(nDaughterList,   Identified[index_list[0]]);
		
		ndaughters++; 	 // particle counter
		nDaughterList++; // event counter 
		
		// Set new identification
		Identified[index_list[0]] = pdg_code;
				
		// Improve this by adding check to see if it is a real value 
		// and only include in average if it is real (aka E, dE, and WC vertex)

		for(Int_t i = 1; i < nindex; i++)
		{
	
			part += GetVector(index_list[i]);

			Ek 	 	+= GetEk(index_list[i]); 	
			time 	+= GetTime(index_list[i]);
			dE 	 	+= Get_dE(index_list[i]); 		
		
			WCO_E 	+= GetWC0_E(index_list[i]);	
			WC1_E 	+= GetWC1_E(index_list[i]);	
			
			WC_Vertex_X += GetWC_Vertex_X(index_list[i]); 	
			WC_Vertex_Y += GetWC_Vertex_Y(index_list[i]);	
			WC_Vertex_Z += GetWC_Vertex_Z(index_list[i]);	
			
			clusterSize += GetClusterSize(index_list[i]);
			if(Apparatus != GetApparatus(index_list[i])) Apparatus = 3;
			
			SumCharge += Charge[index_list[i]];
			
			// store in daughter list for meson analysis
			SetDaughter_index(nDaughterList,nParticles);
			SetDaughter_E(nDaughterList,	 GetEk(index_list[i]));
			SetDaughter_Theta(nDaughterList,GetTheta(index_list[i]));
			SetDaughter_Phi(nDaughterList,	 GetPhi(index_list[i]));
			SetDaughter_PDG(nDaughterList,  Identified[index_list[i]]);

			ndaughters++; 
			nDaughterList++;			
			
			// Set new identification
			Identified[index_list[i]] = pdg_code;		
				
		}
		
		// Average some values
		time = time/nindex;
		WC_Vertex_X = WC_Vertex_X/nindex;
		WC_Vertex_Y = WC_Vertex_Y/nindex;
		WC_Vertex_Z = WC_Vertex_Z/nindex;
		
	}
	else Identified[index_list[0]] = pdg_code;
	
	Double_t Px 	= part.Px();
	Double_t Py 	= part.Py();
	Double_t Pz 	= part.Pz();
	Double_t Theta 	= part.Theta() * TMath::RadToDeg();
	Double_t Phi 	= part.Phi()   * TMath::RadToDeg();
	Double_t Mass   = part.M();
	Ek 				= part.E() - part.M();
	
	SetPDG(nParticles,pdg_code);	
	SetCharge(nParticles,SumCharge);
	SetPx(nParticles,Px);
	SetPy(nParticles,Py);
	SetPz(nParticles,Pz);
	SetTheta(nParticles,Theta);
	SetPhi(nParticles,Phi);	
	SetMass(nParticles,Mass);
	SetEk(nParticles,Ek);
	SetTime(nParticles,time);
	SetClusterSize(nParticles,clusterSize);
	SetApparatus(nParticles,Apparatus);
	Set_dE(nParticles,dE);
	SetWC0_E(nParticles,WCO_E);
	SetWC1_E(nParticles,WC1_E);
	SetWC_Vertex_X(nParticles,WC_Vertex_X);
	SetWC_Vertex_Y(nParticles,WC_Vertex_Y);
	SetWC_Vertex_Z(nParticles,WC_Vertex_Z);
	SetNDaughterList(nDaughterList);
	SetNDaughters(nParticles,ndaughters);
	
	nParticles++;
	
	SetNParticles(nParticles);
	
}


TCutG*  GBakerCalibration::OpenCutFile(Char_t* filename, Char_t* cutname)
{
        CutFile         = new TFile(filename, "READ");

    if( !CutFile || !CutFile->IsOpen() ) {
        cerr << "Can't open cut file: " << filename << endl;
        throw false;
    }


    // Try to find a TCutG with the name we want
    // GetObject checks the type to be TCutG,
    // see http://root.cern.ch/root/html534/TDirectory.html#TDirectory:GetObject
    CutFile->GetObject(cutname, Cut);
    
    if( !Cut ) {
    	cerr << "Could not find a TCutG with the name " << cutname << " in " << filename << endl;
    	throw false;
    	}
    
    TCutG* Cut_clone = Cut;
    CutFile->Close();
    
    cout << "cut file " << filename << " opened (Cut-name = " << cutname << ")"<< endl;                             return Cut_clone;
    
                                                                                                                         }
    
