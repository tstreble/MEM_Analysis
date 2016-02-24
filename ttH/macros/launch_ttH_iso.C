#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <iostream>
#include <map>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TROOT.h>
#include <sstream>
#include <TBranchElement.h>
#include <fstream>
#include <TROOT.h>
#include <TSystem.h>

using namespace std;



void create_scripts(){

  vector<TString> iso;
  iso.push_back("byLooseCombinedIsolationDeltaBetaCorr3Hits");
  iso.push_back("byLooseCombinedIsolationDeltaBetaCorr3HitsdR03");
  iso.push_back("byLooseIsolationMVArun2v1DBdR03oldDMwLT");

  for(unsigned int j=0;j<iso.size();j++){
    
    TString ScriptName = "script_tier3/convert_ttH_" + iso[j] + ".sh";
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH.C+\n";
    myscript << "convert_tree(\"ttH\",0,\""<< iso[j] << "\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   
    
  }
  

}



void launch_scripts(){

  vector<TString> iso;
  iso.push_back("byLooseCombinedIsolationDeltaBetaCorr3Hits");
  iso.push_back("byLooseCombinedIsolationDeltaBetaCorr3HitsdR03");
  iso.push_back("byLooseIsolationMVArun2v1DBdR03oldDMwLT");

  for(unsigned int j=0;j<iso.size();j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += "script_tier3/convert_ttH_" + iso[j] + ".sh";
    gSystem->Exec(LaunchExec.Data());
      
  }

}
