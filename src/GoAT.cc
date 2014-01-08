#ifndef __CINT__

#include "GoAT.h"
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t start, end;
	start = clock();
	
	// Associate 1st terminal input with config file
	Char_t* configfile;
	if(argv[1]) configfile = argv[1];
	else 
	{
		cout << "Please provide a config file" << endl;
		return 0;
	}
	
	// Check that file exists:
	ifstream ifile(configfile);
	if(!ifile)
	{
		cout << "Config file " << configfile << " could not be found." << endl;
		return 0;
	}
	
	// Create instance of GoAT class
	GoAT* goat = new GoAT;

	// Perform full initialisation 
	if(!goat->Init(configfile)){
		cout << "ERROR: GoAT Init failed!" << endl;
		return 0;
	}
	
	goat->Analyse();

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}


GoAT::GoAT() :
				UseParticleReconstruction(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init(Char_t* configfile)
{
	cout << endl << "Initialising GoAT analysis:" << endl;
	cout << "==========================================================" << endl;	
	SetConfigFile(configfile);

	cout << "Opening files: " << endl;
	
	config = ReadConfig("Input-File");
	if (strcmp(config.c_str(), "nokey") == 0)
	{
		cout << "No input file set!" << endl; 
		return kFALSE;
	}
	else if( sscanf( config.c_str(), "%s\n", file_in) == 1 )
	{			
		cout << "INPUT  ";  
		if(!OpenInputFile(file_in))	 return kFALSE;	
	}
	else 
	{
		cout << "input file set incorrectly!" << endl; 
		return kFALSE;
	}		

	config = ReadConfig("Output-File");
	if (strcmp(config.c_str(), "nokey") == 0)
	{
		cout << "No output file set!" << endl; 
		return kFALSE;
	}
	else if( sscanf( config.c_str(), "%s\n", file_out) == 1 )
	{			
		cout << "OUTPUT ";  
		if(!OpenOutputFile(file_out))	return kFALSE;

	}
	else 
	{
		cout << "output file set incorrectly!" << endl; 
		return kFALSE;
	}
	cout << endl;
	
	cout << "Setting up tree files:" << endl;
	if(!OpenTreeRawEvent())			return kFALSE;
	if(!OpenTreeTagger())			return kFALSE;
	if(!OpenTreeTrigger())			return kFALSE;
	cout << endl;
	
	cout << "Checking scaler reads for valid events:" << endl;	
	if(!FindValidEvents())			return kFALSE;
	cout << endl;
		
	config = ReadConfig("Period-Macro");
	if( sscanf(config.c_str(),"%d\n", &period) == 1 ) UsePeriodMacro = 1;
		
	cout << "Setting up sorting criteria:" << endl;	
	cout << "==========================================================" << endl;	
	if(!GSort::PostInit()) 
	{
		cout << "GSort Init failed!" << endl; 
		return kFALSE;
	}
	
	cout << "Setting up analysis classes:" << endl;	
	cout << "==========================================================" << endl;	
	config = ReadConfig("DO-PARTICLE-RECONSTRUCTION");	
	sscanf( config.c_str(), "%d\n", &UseParticleReconstruction);
	if(UseParticleReconstruction) 
	{
		if(!GParticleReconstruction::PostInit())
		{
			cout << "GParticleReconstruction Init failed!" << endl; 
			return kFALSE;
		}
	}			
	cout << endl;	

	cout << "Initialisation complete." << endl;
	cout << "==========================================================" << endl << endl;

  
	return kTRUE;
}

void	GoAT::Analyse()
{
	cout << "Analysing ..." << endl;
	TraverseInputEntries();			
	CloseOutputFile();
//	OutputStatistics();
}

void	GoAT::Reconstruct()
{
	if(UsePeriodMacro == 1)
	{
		if(GetActualEvent() % period == 0) 
						printf("Event: %d\n",GetActualEvent());
	}

	if(SortAnalyseEvent())
	{
		if(UseParticleReconstruction) GParticleReconstruction::Reconstruct();
		
		if(SortFillEvent()) FillEvent();
	}
}

Bool_t 	GoAT::Write()
{
	return kTRUE;
}

#endif
