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

  for(unsigned int j=1;j<5;j++){
    
    TString ScriptName = Form("script_tier3/convert_ttH_ext3_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH.C+\n";
    myscript << "convert_tree(\"ttH_ext3\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",4,"<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   
    
  }
  

}



void launch_scripts(){

  for(unsigned int j=1;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_ttH_ext3_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
      
  }

}
