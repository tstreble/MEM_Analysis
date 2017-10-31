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


vector<TString> categories={"1l2tau","2lss","2lss1tau","3l","3l1tau","4l","combined"};
vector<float> CI={-1,0.5,0.84,0.16,0.975,0.025};


void create_scripts(){
  

  for(unsigned int i=0; i<categories.size(); i++){
    for(unsigned int j=0; j<CI.size(); j++){

      TString ScriptName = "script_tier3/limit_ttH_" + categories[i]+ Form("_%i.sh",j);
      ofstream myscript;
      myscript.open (ScriptName.Data());
      myscript << "#!/bin/bash\n";
      myscript << "cd /home/llr/cms/strebler/CMSSW_7_4_7_ttH_comb/CMSSW_7_4_7/src/\n";
      myscript << "eval `scramv1 runtime -sh`\n";
      myscript << "cd /home/llr/cms/strebler/datacards_test/" << categories[i] << "\n";
      myscript << "combine -M HybridNew --frequentist --testStat LHC -H ProfileLikelihood --fork 4 ttH_" << categories[i] <<".txt";
      if(CI[j]>0)
	myscript << Form(" --expectedFromGrid=%.3f",CI[j]);
      myscript<<"\n";
      myscript << "EOF\n";
      myscript.close();   

    }
  }


}





void create_scripts_sigexp(){
  

  /*for(unsigned int i=0; i<categories.size(); i++){
 
      TString ScriptName = "script_tier3/limit_ttH_" + categories[i]+ "_6.sh";
      ofstream myscript;
      myscript.open (ScriptName.Data());
      myscript << "#!/bin/bash\n";
      myscript << "cd /home/llr/cms/strebler/CMSSW_7_4_7_ttH_comb/CMSSW_7_4_7/src/\n";
      myscript << "eval `scramv1 runtime -sh`\n";
      myscript << "cd /home/llr/cms/strebler/datacards_test/" << categories[i] << "_sigexp\n";
      myscript << "combine -M HybridNew --frequentist --testStat LHC -H ProfileLikelihood --fork 4 ttH_" << categories[i] <<".txt -t -1 --expectSignal 1";
      myscript<<"\n";
      myscript << "EOF\n";
      myscript.close();   
    

      ScriptName = "script_tier3/limit_ttH_" + categories[i]+ "_7.sh";
      ofstream myscript2;
      myscript2.open (ScriptName.Data());
      myscript2 << "#!/bin/bash\n";
      myscript2 << "cd /home/llr/cms/strebler/CMSSW_7_4_7_ttH_comb/CMSSW_7_4_7/src/\n";
      myscript2 << "eval `scramv1 runtime -sh`\n";
      myscript2 << "cd /home/llr/cms/strebler/datacards_test/" << categories[i] << "_sigexp\n";
      myscript2 << "combine -M HybridNew --frequentist --testStat LHC -H ProfileLikelihood --fork 4 -t -1 --expectSignal 1 higgsCombinebestfit.MultiDimFit.mH125.root --snapshotName MultiDimFit --toysFrequentist --bypassFrequentistFit";
      myscript2<<"\n";
      myscript2 << "EOF\n";
      myscript2.close();   

      }*/


  

  for(unsigned int i=0; i<categories.size(); i++){

      TString ScriptName = "script_tier3/limit_ttH_" + categories[i]+ "_sigexp.sh";
      ofstream myscript;
      myscript.open (ScriptName.Data());
      myscript << "#!/bin/bash\n";
      myscript << "cd /home/llr/cms/strebler/CMSSW_7_4_7_ttH_comb/CMSSW_7_4_7/src/\n";
      myscript << "eval `scramv1 runtime -sh`\n";
      myscript << "cd /home/llr/cms/strebler/datacards_test/" << categories[i] << "_sigexp\n";
      //myscript << "combine -M HybridNew --frequentist --testStat LHC -H ProfileLikelihood --fork 4 ttH_" << categories[i] <<".txt";
      myscript << "combine -M Asymptotic -m 125 -t 500 --expectSignal 1 --run observed ttH_" << categories[i] <<".txt";
      myscript<<"\n";
      myscript << "EOF\n";
      myscript.close();   

    
  }


  


}







void create_scripts_sigexp_split(){
  

  for (unsigned int j=0; j<500; j++){

    TString ScriptName = Form("script_tier3/limit_ttH_combined_sigexp_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_7_4_7_ttH_comb/CMSSW_7_4_7/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/datacards_test2/combined_sigexp\n";
    myscript << "combine -M Asymptotic -m 125 -t 1 --expectSignal 1 --run observed ttH_combined.txt -s" <<j;
    myscript<<"\n";
    myscript << "EOF\n";
    myscript.close();   
        
  }

}




void launch_scripts(){
       
  /*for(unsigned int i=0; i<categories.size(); i++){
    for(unsigned int j=0; j<CI.size(); j++){
    
      TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
      LaunchExec +="script_tier3/limit_ttH_" + categories[i]+ Form("_%i.sh",j);
      gSystem->Exec(LaunchExec.Data());
        
      }
      }*/

  /*for(unsigned int i=0; i<categories.size(); i++){
  
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec +="script_tier3/limit_ttH_" + categories[i]+ "_sigexp.sh";
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  for(unsigned int i=0; i<500; i++){
  
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec +=Form("script_tier3/limit_ttH_combined_sigexp_%i.sh",i);
    gSystem->Exec(LaunchExec.Data());
        
  }


}
