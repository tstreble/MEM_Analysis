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

  for(unsigned int j=0;j<7;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"MuonEG_2016B\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/split_MuonEG_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"MuonEG_2016C\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<9;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"DoubleMu_2016B\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<7;j++){

    TString ScriptName = Form("script_tier3/split_DoubleMu_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"DoubleMu_2016C\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016B_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"DoubleEG_2016B\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/split_DoubleEG_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"DoubleEG_2016C\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<7;j++){

    for(unsigned int i_split=0;i_split<10;i_split++){

      TString ScriptName = Form("script_tier3/split_SingleMuon_2016B_082016_%i_%i.sh",j,i_split);
      ofstream myscript;
      myscript.open (ScriptName.Data());
      myscript << "#!/bin/bash\n";
      myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
      myscript << "eval `scramv1 runtime -sh`\n";
      myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
      myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
      myscript << "root -b -l <<EOF\n";
      myscript << ".L tree_splitter.C+\n";
      myscript << "split_tree(\"SingleMuon_2016B\","<< j << "," << 10 << "," << i_split << ");\n";
      myscript << ".q\n";
      myscript << "EOF\n";
      myscript.close();   

    }

  }


  for(unsigned int j=0;j<8;j++){

    TString ScriptName = Form("script_tier3/split_SingleMuon_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"SingleMuon_2016C\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<9;j++){

    for(unsigned int i_split=0;i_split<10;i_split++){

      TString ScriptName = Form("script_tier3/split_SingleEle_2016B_082016_%i_%i.sh",j,i_split);
      ofstream myscript;
      myscript.open (ScriptName.Data());
      myscript << "#!/bin/bash\n";
      myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
      myscript << "eval `scramv1 runtime -sh`\n";
      myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
      myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
      myscript << "root -b -l <<EOF\n";
      myscript << ".L tree_splitter.C+\n";
      myscript << "split_tree(\"SingleEle_2016B\","<< j << "," << 10 << "," << i_split<< ");\n";
      myscript << ".q\n";
      myscript << "EOF\n";
      myscript.close();   

    }

  }


  for(unsigned int j=0;j<8;j++){

    TString ScriptName = Form("script_tier3/split_SingleEle_2016C_082016_%i.sh",j);
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_6_ttHprod_082016/CMSSW_8_0_6/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L tree_splitter.C+\n";
    myscript << "split_tree(\"SingleEle_2016C\","<< j << ");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


}





void launch_scripts(){
       

  /*for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_MuonEG_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<9;j++){    

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleMu_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016B_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  for(unsigned int j=0;j<5;j++){

    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_DoubleEG_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  for(unsigned int j=0;j<10;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMuon_2016B_082016_0_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  /*for(unsigned int j=0;j<8;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleMuon_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<10;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016B_082016_1_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit ";
    LaunchExec += Form("script_tier3/split_SingleEle_2016C_082016_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


}
