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


  /*TString ScriptName = Form("script_tier3/convert_ttH_Htautau.sh");
  ofstream myscript;
  myscript.open (ScriptName.Data());
  myscript << "#!/bin/bash\n";
  myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
  myscript << "root -b -l <<EOF\n";
  myscript << ".L Helpers_convert_ttH_v2.C+\n";
  myscript << "convert_tree(\"ttH_Htautau\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\");\n";
  myscript << ".q\n";
  myscript << "EOF\n";
  myscript.close();  */

  TString ScriptName = Form("script_tier3/convert_TTJets_DL.sh");
  ofstream myscript;
  myscript.open (ScriptName.Data());
  myscript << "#!/bin/bash\n";
  myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
  myscript << "root -b -l <<EOF\n";
  myscript << ".L Helpers_convert_ttH_v2.C+\n";
  myscript << "convert_tree(\"TTJets_DL\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\");\n";
  myscript << ".q\n";
  myscript << "EOF\n";
  myscript.close(); 




  /*for(unsigned int j=1;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_TTJets_DL_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"TTJets_DL\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",10,"<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

    }*/

}



void launch_scripts(){

  /*TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
  LaunchExec +="script_tier3/convert_ttH_Htautau.sh";
  gSystem->Exec(LaunchExec.Data());*/

  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
  LaunchExec +="script_tier3/convert_TTJets_DL.sh";
  gSystem->Exec(LaunchExec.Data());
        
  
  /*for(unsigned int j=1;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_TTJets_SLfromTbar_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

}
