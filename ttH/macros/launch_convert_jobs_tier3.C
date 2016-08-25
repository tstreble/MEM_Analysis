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


  for(unsigned int j=0;j<67;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"MuonEG_2016B_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<33;j++){

    TString ScriptName = Form("script_tier3/convert_MuonEG_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"MuonEG_2016C_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<84;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016B_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<64;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleMu_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"DoubleMu_2016C_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<57;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016B_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




 for(unsigned int j=0;j<53;j++){

    TString ScriptName = Form("script_tier3/convert_DoubleEG_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"DoubleEG_2016C_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }
 

 for(unsigned int j=0;j<65;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMuon_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"SingleMuon_2016B_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<80;j++){

    TString ScriptName = Form("script_tier3/convert_SingleMuon_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"SingleMuon_2016C_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }
 


 for(unsigned int j=0;j<86;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"SingleEle_2016B_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



 for(unsigned int j=0;j<75;j++){

    TString ScriptName = Form("script_tier3/convert_SingleEle_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L Helpers_convert_ttH_v2.C+\n";
    myscript << "convert_tree(\"SingleEle_2016C_082016\",0,\"byLooseIsolationMVArun2v1DBdR03oldDMwLT\",false,0,"<< j << ",false);\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




}





void launch_scripts(){
       

  /*for(unsigned int j=0;j<67;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<33;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_MuonEG_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<84;j++){    

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  for(unsigned int j=0;j<64;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_DoubleMu_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  /*for(unsigned int j=0;j<57;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
       
    }*/


  /*for(unsigned int j=0;j<53;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_DoubleEG_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/



  /*for(unsigned int j=30;j<50;j++){

    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_SingleMuon_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<80;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_SingleMuon_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
       
  }*/


  /*for(unsigned int j=0;j<86;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<75;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/convert_SingleEle_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


}
