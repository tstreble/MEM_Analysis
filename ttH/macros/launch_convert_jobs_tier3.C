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


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttH_Hnonbb_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttH_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttH_Hnonbb_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttH_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttH_Hnonbb_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttH_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttH_Hnonbb_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttH_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttH_Hnonbb_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttH_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttHJet_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttHJet_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttHJet_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttHJet_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttHJet_Hnonbb_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_THQ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THQ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_THQ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THQ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_THQ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THQ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_THQ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THQ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_THQ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THQ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_THW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_THW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_THW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_THW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_THW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"THW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_VBF_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"VBF_HTauTau_80X_reHLT\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_lowmass_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_lowmass_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_lowmass_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_lowmass_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_lowmass_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_lowmass_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_lowmass_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_lowmass_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_lowmass_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_lowmass_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_ext_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_ext_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_ext_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_ttZ_ext_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttZ_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_TTTT_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"TTTT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_TTTT_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"TTTT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_TTTT_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"TTTT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_TTTT_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"TTTT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_TTTT_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"TTTT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_tZq_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tZq_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_tZq_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tZq_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_tZq_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tZq_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_tZq_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tZq_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_tZq_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tZq_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_ext_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_ext_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_ext_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_ttW_ext_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttW_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttWW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttWW_gpetrucc\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttWW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttWW_gpetrucc\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttWW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttWW_gpetrucc\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttWW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttWW_gpetrucc\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ttWW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttWW_gpetrucc\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WW_DoubleScat_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WW_DoubleScat_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_powheg_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_powheg_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_powheg_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_powheg_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_powheg_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_powheg_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_powheg_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_powheg_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_WZ_powheg_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZ_powheg_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/convert_ZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<70;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016B_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<52;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016C_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<58;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016D_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<52;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016E_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<52;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016F_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<83;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016G_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<89;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016Hv2_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016Hv3_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<83;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016B_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<29;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016C_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<36;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016D_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<40;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016E_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<21;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016F_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016G_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016Hv2_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016Hv3_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<32;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016B_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016C_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<24;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016D_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<22;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016E_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<17;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016F_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<34;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016G_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<29;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016Hv2_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"MuonEG_2016Hv3_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016B_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<79;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016C_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<53;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016D_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<48;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016E_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<79;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016F_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016G_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<92;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016Hv2_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMu_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleMu_2016Hv3_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016B_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016B_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<55;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016C_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016C_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016D_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016D_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<65;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016E_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016E_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<88;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016F_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016F_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016G_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016G_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<66;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016Hv2_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016Hv2_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016Hv3_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"SingleEle_2016Hv3_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<7;j++){

    TString ScriptName = Form("script_tier3/convert_ttbar_DL_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttbar_DL_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<25;j++){

    TString ScriptName = Form("script_tier3/convert_ttbar_DL_ext_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttbar_DL_ext_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<13;j++){

    TString ScriptName = Form("script_tier3/convert_ttbar_SLfromT_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttbar_SLfromT_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/convert_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttbar_SLfromTbar_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WW_DoubleScatt_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WW_DoubleScatt_80X_reHLT\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWJJ_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWJJ_80X_reHLT\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_ZZJJ_80X_reHLT_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZJJ_80X_reHLT\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/convert_ZG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/convert_WG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WpWp_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WpWp_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WpWp_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WpWp_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WpWp_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WpWp_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WpWp_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WpWp_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WpWp_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WpWp_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ZZZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ZZZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ZZZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ZZZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_ZZZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ZZZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWW_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWW_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWW_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWW_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWW_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWW_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWZ_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWZ_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWZ_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWZ_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_WWZ_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"WWZ_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/convert_tG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"tG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }

 for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/convert_ttG_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/convert_ttG_Moriond17_JECup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/convert_ttG_Moriond17_JECdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/convert_ttG_Moriond17_TESup_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,+1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/convert_ttG_Moriond17_TESdown_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"ttG_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true,0,-1);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/convert_DYBJets_Moriond17_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v6.C+\n";
    myscript << "convert_tree(\"DYBJets_Moriond17\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",true);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




}





void launch_scripts(){
       

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttH_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }



  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttH_Hnonbb_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttH_Hnonbb_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttH_Hnonbb_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttH_Hnonbb_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }



  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttHJet_Hnonbb_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THQ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }



  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THQ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THQ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THQ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THQ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }



  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_THW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  
  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_lowmass_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_ext_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_ext_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_ext_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttZ_ext_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttWW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttWW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttWW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttWW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }


  /*for(unsigned int j=0;j<70;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/


  /*for(unsigned int j=0;j<52;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<58;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<52;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<37;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<83;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<89;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<83;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<29;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<36;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<28;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<21;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<46;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/


  /*for(unsigned int j=0;j<49;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<32;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<24;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<22;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<17;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<34;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<29;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<80;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<79;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

 

  /*for(unsigned int j=0;j<53;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<48;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<36;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<80;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<92;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleMu_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

   /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016B_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<55;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016C_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016D_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<65;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016E_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<39;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016F_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<84;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016G_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<66;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016Hv2_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016Hv3_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_ext_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_ext_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_ext_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttW_ext_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttbar_DL_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }


  for(unsigned int j=0;j<25;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttbar_DL_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }

  for(unsigned int j=0;j<13;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttbar_SLfromT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }

  for(unsigned int j=0;j<49;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<25;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttbar_DL_ext_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
    
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WW_DoubleScatt_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWJJ_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZJJ_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZG_80X_reHLT_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_powheg_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_powheg_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_powheg_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_powheg_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZ_powheg_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WpWp_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WpWp_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WpWp_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WpWp_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WpWp_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttG_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttG_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttG_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ttG_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_ZZZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWW_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWW_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWW_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWW_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWZ_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWZ_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWZ_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_WWZ_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/
  

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_DYBJets_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tZq_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tZq_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tZq_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tZq_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_tZq_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_TTTT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_TTTT_Moriond17_JECup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_TTTT_Moriond17_JECdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }



  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_TTTT_Moriond17_TESup_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/convert_TTTT_Moriond17_TESdown_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


}
