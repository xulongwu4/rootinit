// The paths to store ROOT files
const char* PATHS[] = {
    "/LaCie/data/other",
    "/LaCie/gmp12/rootfiles/Fall2016/K3-4",
    "/LaCie/gmp12/rootfiles/Fall2016/K3-6",
    "/LaCie/gmp12/rootfiles/Fall2016/K3-7",
    "/LaCie/gmp12/rootfiles/Fall2016/K3-8",
    "/LaCie/gmp12/rootfiles/Fall2016/K3-9",
    "/LaCie/gmp12/rootfiles/Fall2016/K4-10",
    "/LaCie/gmp12/rootfiles/Fall2016/K4-11",
    "/LaCie/gmp12/rootfiles/Fall2016/K4-12",
    "/LaCie/gmp12/rootfiles/Fall2016/K4-9",
    "/LaCie/gmp12/rootfiles/Fall2016/KP4",
    "/LaCie/gmp12/rootfiles/Fall2016/KP5",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K3-4",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K3-6",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K3-7",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K3-8",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K3-9",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K4-10",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K4-11",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K4-12",
    "/LaCie/gmp12/rootfiles/Fall2016/Al/K4-9",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K3-4",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K3-6",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K3-7",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K3-8",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K3-9",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K4-10",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K4-11",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K4-12",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/K4-9",
//    //"/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/KP4",
//    "/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/KP5",
//    //"/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/LOptics",
//    //"/work/halla/gmp12/longwu/gmp_analysis/rootfiles/Fall2016/ROptics",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/KP4",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/KP5",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K3-4",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K3-6",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K3-7",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K3-8",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K3-9",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K4-10",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K4-11",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K4-12",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/K4-9",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/KP4",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/KP5",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/LOptics",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/ROptics",
//    "/LaCie/gmp12/rootfiles/Fall2016-old/Inelastic",
//    "/LaCie/gmp12/rootfiles/Spring2015",
    "/LaCie/gmp12/rootfiles/other",
    0
};

// Chain all the ROOT files for a given run number and return the TChain
//      run   --- run number
//      path  --- Directory to look for the ROOT files
//      tree  --- Name of the tree to be loaded from the ROOT files. Can be "T", "E", "LEFT", ...
//      debug --- Debug level
TChain* LoadGmpRun(Int_t run, const char* path, const char* tree, Int_t debug = 1)
{
    TChain* T = new TChain(tree);

    TString basename = Form("gmp_%d",run);
    TString rootfile = basename + ".root";

    TString dir = path;
    if (!dir.EndsWith("/")) dir.Append("/");

    rootfile.Prepend(dir.Data());

    Long_t split = 0;

    while ( !gSystem->AccessPathName(rootfile.Data()) ) {
	T->Add(rootfile.Data());
	cout << "ROOT file " << rootfile << " added to TChain." << endl;
	split++;
	rootfile = basename + "_" + split + ".root";
	rootfile.Prepend(dir.Data());
    }

    if (!T->GetEntries()) {
	if (debug>0) cerr << "Can not find ROOT file for run " << run << endl;
	delete T;
	T = 0;
    }

    return T;
}

// Load TTree "tree" form all the ROOT files generated from a specific run
// The ROOT files are searched for from the given "PATHS" array given at the beginning of the file
//      run  --- run number
//      tree --- The name of the tree to be loaded
TChain* LoadGmpRun(Int_t run, const char* tree = "T")
{
    Int_t i=0;

    TChain* T = 0;

    while (PATHS[i]) {
	T = LoadGmpRun(run,PATHS[i++],tree,0);
	if (T) break;
    }

    if (!T)
	cerr << "Can not find ROOT file for run " << run << endl;

    return T;
}

// Return run number of a given run
Int_t GetRunNumber(TTree* T)
{
    Int_t runnumber = 0;

    THaRun* run = 0;

    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        runnumber = run->GetNumber();
        delete run;
    }

    return runnumber;
}

// Return date of a given run
TDatime GetRunDate(TTree* T)
{
    TDatime run_time("2018-01-01 00:00:00");

    THaRun* run = 0;

    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        run_time = run->GetDate();
        delete run;
    }

    return run_time;
}

// Load a variable from the run database
Double_t GetValueFromDB(TTree* T, const char* varname)
{
    Double_t variable = 0;
    THaRun* run = 0;
    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        Int_t run_number = run->GetNumber();
        TDatime run_time = run->GetDate();

        TString name = varname;

        FILE* file = THaAnalysisObject::OpenFile("run",run_time,"","r",0);
        if (THaAnalysisObject::LoadDBvalue(file, run_time, name, variable)!=0) {
            if (run_number<20000) 
                name.Prepend("L.");
            else
                name.Prepend("R.");

            if (THaAnalysisObject::LoadDBvalue(file, run_time, name, variable)!=0)
                variable = 0;
        }

        fclose(file);

        delete run;
    }

    return variable;
}
/*
Double_t GetCentralMom(TTree* T)
{
    Double_t mom = 0;
    THaRun* run = 0;
    THaHRS* hrs = 0;
    T->GetDirectory()->GetObject("Run_Data",run);
    if (run) {
        Int_t run_number = run->GetNumber();
        TDatime run_time = run->GetDate();
        if (run_number<20000) 
            hrs = new THaHRS("L","Left arm HRS");
        else
            hrs = new THaHRS("R","Right arm HRS");

        hrs->Init(run_time);

        mom = hrs->GetPcentral();

        delete hrs;
        delete run;
    }

    return mom;
}
*/
/*
// Return central momentum of a given run
Double_t GetCentralMom(TTree* T)
{
    Double_t mom = 0;
    THaRun* run = 0;
    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        Int_t run_number = run->GetNumber();
        TDatime run_time = run->GetDate();

        FILE* file = THaAnalysisObject::OpenFile("run",run_time,"","r",0);
        TString name = ".pcentral";
        if (run_number<20000) 
            name.Prepend("L");
        else
            name.Prepend("R");

        THaAnalysisObject::LoadDBvalue(file, run_time, name, mom);
        fclose(file);

        delete run;
    }

    return mom;
}
*/
// Return central momentum of a given run
Double_t GetCentralMom(TTree* T)
{
    return GetValueFromDB(T, "pcentral");
}

// Return prescale factor for a given trigger
Int_t GetPrescale(TTree* T, Int_t trig)
{
    if (trig<=0 || trig>8) return 0;

    Int_t prescale = 0;

    THaRun* run = 0;

    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        prescale = run->GetParameters()->GetPrescales()[trig-1];
        delete run;
    }

    return prescale;
}
/*
// Return spectrometer angle of a given run in degree
// Negative for right HRS
// Positive for left HRS
Double_t GetSpecAngle(TTree* T)
{
    Double_t angle = 0;
    THaRun* run = 0;
    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        Int_t run_number = run->GetNumber();
        TDatime run_time = run->GetDate();

        FILE* file = THaAnalysisObject::OpenFile("run",run_time,"","r",0);
        TString name = ".theta";
        if (run_number<20000) 
            name.Prepend("L");
        else
            name.Prepend("R");

        THaAnalysisObject::LoadDBvalue(file, run_time, name, angle);
        fclose(file);

        delete run;
    }

    return angle;
}
*/
// Return spectrometer angle of a given run in degree
// Negative for right HRS
// Positive for left HRS
Double_t GetSpecAngle(TTree* T)
{
    return GetValueFromDB(T, "theta");
}
/*
// Return beam energy in a given run
Double_t GetBeamEnergy(TTree* T)
{
    Double_t ebeam = 0;
    THaRun* run = 0;
    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        ebeam = run->GetParameters()->GetBeamE();
        delete run;
    }

    return ebeam;
}
*/
// Return beam energy in a given run
Double_t GetBeamEnergy(TTree* T)
{
    return GetValueFromDB(T, "ebeam");
}

/*
// Return target mass in a given run
Double_t GetTgtM(TTree* T)
{
    Double_t tmass = 0;
    THaRun* run = 0;
    if (!T->GetDirectory()) T->LoadTree(0); // Necessary if T is a TChain
    TDirectory* fDir = T->GetDirectory();
    if (fDir) fDir->GetObject("Run_Data",run);
    if (run) {
        tmass = run->GetParameters()->GetTgtM();
        delete run;
    }

    return tmass;
}
*/
