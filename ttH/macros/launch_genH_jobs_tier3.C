#include <TString.h>
#include <TSystem.h>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;



void create_scripts(){


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = "script_tier3/genH_ttH_Hnonbb_80X_reHLT_JECup.sh";
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_12/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_genH_decayMode.C+\n";
    myscript << "vector<TString> treename;\n";
    myscript << "treename.push_back(\"HTauTauTree_1l_2tau\");\n";
    myscript << "treename.push_back(\"HTauTauTree_2lSS\");\n";
    myscript << "treename.push_back(\"HTauTauTree_3l\");\n";

    myscript << "add_genH_decayMode(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_PU.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_PU_genH.root\",treename);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = "script_tier3/genH_ttH_Hnonbb_80X_reHLT_JECdown.sh";
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_12/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_genH_decayMode.C+\n";
    myscript << "vector<TString> treename;\n";
    myscript << "treename.push_back(\"HTauTauTree_1l_2tau\");\n";
    myscript << "treename.push_back(\"HTauTauTree_2lSS\");\n";
    myscript << "treename.push_back(\"HTauTauTree_3l\");\n";

    myscript << "add_genH_decayMode(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECdown/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_PU.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECdown/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_PU_genH.root\",treename);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = "script_tier3/genH_ttH_Hnonbb_80X_reHLT_TESup.sh";
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_12/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_genH_decayMode.C+\n";
    myscript << "vector<TString> treename;\n";
    myscript << "treename.push_back(\"HTauTauTree_1l_2tau\");\n";
    myscript << "treename.push_back(\"HTauTauTree_2lSS\");\n";
    myscript << "treename.push_back(\"HTauTauTree_3l\");\n";

    myscript << "add_genH_decayMode(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_PU.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_PU_genH.root\",treename);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = "script_tier3/genH_ttH_Hnonbb_80X_reHLT_TESdown.sh";
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_12/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_genH_decayMode.C+\n";
    myscript << "vector<TString> treename;\n";
    myscript << "treename.push_back(\"HTauTauTree_1l_2tau\");\n";
    myscript << "treename.push_back(\"HTauTauTree_2lSS\");\n";
    myscript << "treename.push_back(\"HTauTauTree_3l\");\n";

    myscript << "add_genH_decayMode(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_PU.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_PU_genH.root\",treename);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




}





void launch_scripts(){

  TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += "script_tier3/genH_ttH_Hnonbb_80X_reHLT_JECup.sh";
  gSystem->Exec(LaunchExec.Data());

  LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += "script_tier3/genH_ttH_Hnonbb_80X_reHLT_JECdown.sh";
  gSystem->Exec(LaunchExec.Data());

  LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += "script_tier3/genH_ttH_Hnonbb_80X_reHLT_TESup.sh";
  gSystem->Exec(LaunchExec.Data());

  LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
  LaunchExec += "script_tier3/genH_ttH_Hnonbb_80X_reHLT_TESdown.sh";
  gSystem->Exec(LaunchExec.Data());


}
