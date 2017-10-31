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

  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttH_Hnonbb_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttH_Hnonbb_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttH/ntuple_ttH_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttH_Hnonbb_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttH/ntuple_ttH_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttH_Hnonbb_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttH/ntuple_ttH_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttH_Hnonbb_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttH/ntuple_ttH_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_ttHJet_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttH/ntuple_ttHJet_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_ttHJet_Hnonbb_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttH/ntuple_ttHJet_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_ttHJet_Hnonbb_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttH/ntuple_ttHJet_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_ttHJet_Hnonbb_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttH/ntuple_ttHJet_Hnonbb_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_ttHJet_Hnonbb_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_THQ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_THQ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THQ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_THQ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttH/ntuple_THQ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_THQ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_THQ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttH/ntuple_THQ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_THQ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_THQ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttH/ntuple_THQ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_THQ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_THQ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttH/ntuple_THQ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_THQ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_THW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_THW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THW_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_THW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttH/ntuple_THW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_THW_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_THW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttH/ntuple_THW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_THW_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_THW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttH/ntuple_THW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_THW_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_THW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttH/ntuple_THW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_THW_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }







 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_lowmass_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_lowmass_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_lowmass_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_lowmass_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttZ_lowmass_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_lowmass_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_lowmass_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttZ_lowmass_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_lowmass_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_lowmass_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttZ_lowmass_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_lowmass_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_lowmass_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttZ_lowmass_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_lowmass_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }








 for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_ext_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_ext_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttZ_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_ext_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_ext_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttZ_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_ext_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_ext_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttZ_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_ext_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_ttZ_ext_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttZ_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_ext_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_ttW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_ttW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_ttW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttW_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_ttW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_ttW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_ttW_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttW_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_ttW_ext_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttW_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_ext_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_ttW_ext_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttW_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttW_ext_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_ttW_ext_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttW_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_ext_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_ttW_ext_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttW_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_ext_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttWW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttWW_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttWW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttWW_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttWW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttWW_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttWW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttWW_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ttWW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttWW_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






 for(unsigned int j=0;j<70;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016B_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<52;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016C_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 
 for(unsigned int j=0;j<58;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016D_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<52;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016E_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016E_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<38;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016F_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016F_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<83;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016G_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016G_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<89;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016Hv2_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv2_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleEG_2016Hv3_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv3_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }


 for(unsigned int j=0;j<83;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016B_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<29;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016C_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 
 for(unsigned int j=0;j<36;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016D_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<40;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016E_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016E_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<21;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016F_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016F_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<46;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016G_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016G_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016Hv2_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv2_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_DoubleMu_2016Hv3_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv3_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<32;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016B_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016C_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 
 for(unsigned int j=0;j<24;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016D_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<22;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016E_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016E_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<18;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016F_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016F_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<34;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016G_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016G_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<29;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016Hv2_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_MuonEG_2016Hv3_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv3_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016B_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<79;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016C_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 
 for(unsigned int j=0;j<53;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016D_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<48;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016E_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016E_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016F_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016F_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016G_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016G_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<92;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016Hv2_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_SingleMu_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleMu_2016Hv3_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016B_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<55;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016C_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 
 for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016D_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 for(unsigned int j=0;j<65;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016E_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016E_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 for(unsigned int j=0;j<89;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016F_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016F_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016G_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016G_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<66;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016Hv2_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Data/ntuple_SingleEle_2016Hv3_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_" << j << ".root\",0,0,false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();

  }

 for(unsigned int j=0;j<7;j++){

    TString ScriptName = Form("script_tier3/split_ttbar_DL_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_DL_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<25;j++){

    TString ScriptName = Form("script_tier3/split_ttbar_DL_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_DL_ext_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<13;j++){

    TString ScriptName = Form("script_tier3/split_ttbar_SLfromT_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_SLfromT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/split_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_SLfromTbar_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WpWp_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WpWp_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WpWp_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_WpWp_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WpWp_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WpWp_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_WpWp_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WpWp_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WpWp_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_WpWp_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WpWp_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WpWp_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_WpWp_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WpWp_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WW_DoubleScatt_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/ntuple_WW_DoubleScatt_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WW_DoubleScatt_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WW_DoubleScat_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WW_DoubleScat_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WW_DoubleScat_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_ZG_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/ntuple_ZG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_ZG_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_ZG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_ZG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZG_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_WG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WG_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_ZZJJ_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/ntuple_ZZJJ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_ZZJJ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WW_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WW_DoubleScat_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WW_DoubleScat_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WW_DoubleScat_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_WZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WZ_powheg_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WZ_powheg_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_powheg_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_WZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/EWK/ntuple_WZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_WZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/EWK/ntuple_WZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_WZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/EWK/ntuple_WZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_WZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/EWK/ntuple_WZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WZ_powheg_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/EWK/ntuple_WZ_powheg_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_powheg_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WZ_powheg_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/EWK/ntuple_WZ_powheg_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_powheg_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WZ_powheg_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/EWK/ntuple_WZ_powheg_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_powheg_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_WZ_powheg_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/EWK/ntuple_WZ_powheg_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_powheg_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_ZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/EWK/ntuple_ZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_ZZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/EWK/ntuple_ZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_ZZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/split_ZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/EWK/ntuple_ZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_ZZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/split_ZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/EWK/ntuple_ZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_ZZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttG_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/ttV/ntuple_ttG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttG_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttG_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/ttV/ntuple_ttG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttG_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttG_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/ttV/ntuple_ttG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttG_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/split_ttG_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/ttV/ntuple_ttG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttG_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_tG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_tG_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_tG_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WWZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_WWZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WWZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_WWZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WWZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_WWZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WWZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_WWZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WWZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_WWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WWW_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_WWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WWW_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_WWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WWW_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WWW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_WWW_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WWW_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ZZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_ZZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ZZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_ZZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_ZZZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ZZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_ZZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_ZZZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ZZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_ZZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_ZZZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_ZZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_ZZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_ZZZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_WZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WZZ_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_WZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WZZ_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_WZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WZZ_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/split_WZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_WZZ_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WZZ_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_tZq_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_tZq_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_tZq_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_tZq_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_tZq_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_tZq_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_tZq_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_tZq_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/split_tZq_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_tZq_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/split_DYBJets_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/DY/ntuple_DYBJets_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/DY/HTauTauTree_DYBJets_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_TTTT_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_TTTT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_TTTT_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECup/Rares/ntuple_TTTT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_TTTT_split_JECup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_TTTT_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/JECdown/Rares/ntuple_TTTT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_JECdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_TTTT_split_JECdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_TTTT_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESup/Rares/ntuple_TTTT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESup.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_TTTT_split_TESup_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/split_TTTT_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter_v3.C+\n";
    myscript << "split_tree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/TESdown/Rares/ntuple_TTTT_"<< j <<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT_TESdown.root\" , \"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_TTTT_split_TESdown_" << j << ".root\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






}





void launch_scripts(){
       

  /*for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttH_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttH_Hnonbb_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttH_Hnonbb_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttH_Hnonbb_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttH_Hnonbb_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttHJet_Hnonbb_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THQ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THQ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THQ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THQ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THQ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_THW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }
 


  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_lowmass_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttWW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttWW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttWW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttWW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_lowmass_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_lowmass_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_lowmass_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_lowmass_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_ext_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_ext_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_ext_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttZ_ext_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<70;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<52;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<58;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<52;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<37;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<83;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<89;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<3;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<83;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<29;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<36;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<28;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<21;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<46;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<49;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<2;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<32;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<24;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<22;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<17;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<34;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<29;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<1;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<80;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/



  /*for(unsigned int j=0;j<79;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<53;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<48;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<36;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/
  
  /*for(unsigned int j=0;j<80;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<92;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

    /*for(unsigned int j=0;j<3;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMu_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<55;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<65;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<39;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

   /*for(unsigned int j=0;j<66;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<2;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());

    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_ext_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_ext_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_ext_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttW_ext_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttbar_DL_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<25;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttbar_DL_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<13;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttbar_SLfromT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<49;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WpWp_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WpWp_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WpWp_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WpWp_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WpWp_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WW_DoubleScatt_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    } */ 

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZJJ_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/  

  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_powheg_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_powheg_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_powheg_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_powheg_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_powheg_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

    /*for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttG_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttG_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttG_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ttG_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }
  
  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_WWW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_ZZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tZq_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tZq_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tZq_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/
  
  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tZq_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_tZq_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DYBJets_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_TTTT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_TTTT_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_TTTT_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_TTTT_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_TTTT_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


}
