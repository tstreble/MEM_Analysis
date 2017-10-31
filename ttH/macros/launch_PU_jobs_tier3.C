#include <TString.h>
#include <TSystem.h>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;



void create_scripts(){


  for(unsigned int j=0;j<5;j++){

    TString ScriptName = Form("script_tier3/PU_ttH_Hnonbb_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/PU_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_ttHJet_Hnonbb_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_ttHJet_Hnonbb_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/PU_THQ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_THQ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THQ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/PU_THW_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_THW_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THW_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/PU_ttZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_ttZ_lowmass_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_lowmass_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_lowmass_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<6;j++){

    TString ScriptName = Form("script_tier3/PU_ttZ_ext_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttZ_ext_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_ext_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/PU_ttW_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttW_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttW_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/PU_ttW_ext_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttW_ext_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttW_ext_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_ttWW_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttWW_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttWW_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<4;j++){

    TString ScriptName = Form("script_tier3/PU_ttG_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_ttG_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttG_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_tG_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_tG_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_tG_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<12;j++){

    TString ScriptName = Form("script_tier3/PU_WZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


 for(unsigned int j=0;j<2;j++){

    TString ScriptName = Form("script_tier3/PU_WZ_powheg_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_WZ_powheg_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ_powheg_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<11;j++){

    TString ScriptName = Form("script_tier3/PU_ZZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_ZZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_ZZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }


  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/PU_ZG_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_ZG_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_ZG_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<7;j++){

    TString ScriptName = Form("script_tier3/PU_ttbar_DL_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_DL_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<25;j++){

    TString ScriptName = Form("script_tier3/PU_ttbar_DL_ext_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_DL_ext_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL_ext_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<13;j++){

    TString ScriptName = Form("script_tier3/PU_ttbar_SLfromT_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_SLfromT_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromT_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<49;j++){

    TString ScriptName = Form("script_tier3/PU_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_ttbar_SLfromTbar_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromTbar_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }






  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_WWW_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WWW_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWW_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_WWZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WWZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }





  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_WZZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WZZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WZZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_ZZZ_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_ZZZ_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_ZZZ_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




  for(unsigned int j=0;j<15;j++){

    TString ScriptName = Form("script_tier3/PU_tZq_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_tZq_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_tZq_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<3;j++){

    TString ScriptName = Form("script_tier3/PU_TTTT_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_TTTT_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_TTTT_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }



  for(unsigned int j=0;j<1;j++){

    TString ScriptName = Form("script_tier3/PU_WpWp_Moriond17_%i.sh",j);
    
    ofstream myscript;
    myscript.open (ScriptName.Data());
    myscript << "#!/bin/bash\n";
    myscript << "cd /home/llr/cms/strebler/CMSSW_8_0_20/src/\n";
    myscript << "eval `scramv1 runtime -sh`\n";
    myscript << "cd /home/llr/cms/strebler/MEM_Analysis/ttH/macros\n";
    myscript << "export X509_USER_PROXY=/home/llr/cms/strebler/.t3/proxy.cert\n";
    myscript << "root -b -l <<EOF\n";
    myscript << ".L add_PU_weight.C+\n";
    myscript << "create_PUtree(\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_WpWp_"<<j<<"_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root\",\"/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WpWp_"<<j<<".root\",\"HTauTauTree\");\n";
    myscript << ".q\n";
    myscript << "EOF\n";
    myscript.close();   

  }




}




void launch_scripts(){


  /*for(unsigned int j=0;j<5;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttH_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttHJet_Hnonbb_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_THQ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_THW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<6;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttZ_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttW_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  /*for(unsigned int j=0;j<4;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }


  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_tG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
  }



  for(unsigned int j=0;j<12;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<2;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WZ_powheg_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<11;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ZG_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/



  /*for(unsigned int j=0;j<7;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttbar_DL_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<25;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttbar_DL_ext_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<13;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttbar_SLfromT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<49;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ttbar_SLfromTbar_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


  /*for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WWW_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WWZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_ZZZ_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }

  for(unsigned int j=0;j<1;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_WpWp_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<15;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_tZq_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/

  /*for(unsigned int j=0;j<3;j++){
    
    TString LaunchExec = "/opt/exp_soft/cms/t3/t3submit_new ";
    LaunchExec += Form("script_tier3/PU_TTTT_Moriond17_%i.sh",j);
    gSystem->Exec(LaunchExec.Data());
        
    }*/


}
