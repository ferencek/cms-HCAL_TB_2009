#include "DQM/HcalMonitorTasks/interface/H2BeamLineMonitor.h"

using namespace std;


// constructor
H2BeamLineMonitor::H2BeamLineMonitor() {}

// destructor
H2BeamLineMonitor::~H2BeamLineMonitor() {}

void H2BeamLineMonitor::reset() {}

void H2BeamLineMonitor::done() {}

void H2BeamLineMonitor::clearME()
{
  if (m_dbe) 
    {
      m_dbe->setCurrentFolder(baseFolder_);
      m_dbe->removeContents();
    } // if (m_dbe)
  meEVT_=0;
} // void H2BeamLineMonitor::clearME()


void H2BeamLineMonitor::setup(const edm::ParameterSet& ps, DQMStore* dbe){

  HcalBaseMonitor::setup(ps,dbe);  // perform setups of base class

  ievt_=0; // set event counter to 0
  tbbeamEvt_=0;
  tbpedEvt_=0;
  
  baseFolder_ = rootFolder_ + "H2BeamLineMonitor"; // Will create an "H2BeamLineMonitor" subfolder in .root output
  if (fVerbosity) cout <<"<H2BeamLineMonitor::setup> Setup in progress"<<endl;

  if (m_dbe)
    {
      m_dbe->setCurrentFolder(baseFolder_);
      meEVT_ = m_dbe->bookInt("H2BeamLineMonitor Event Number"); // store event number
    
      // Wire chambers: Beam position: 2D: Xhits vs Yhits, and 1D Xhits, Yhits
      m_dbe->setCurrentFolder(baseFolder_+"/Event_Position_Monitor");
        
      char name[250];
      char title[250];
      int col1 = 1, col2 = 2, col3 = 3;
      
      for(char i = 'A'; i<='H'; i++)
        layers_.push_back(i);
      
      for(unsigned int i=0; i<layers_.size(); i++) {
        
        sprintf(name,"h%02d_Wire_Chamber_%c_Hits", col1, layers_[i] );
        col1 = col1+3;
        sprintf(title,"Wire Chamber %c Hits;X [mm];Y [mm]", layers_[i] );
        mePlanes_[i] = m_dbe->book2D(name,title,100,-50,50,100,-50,50);
        if ( i<3 ) {
          sprintf(name,"h%02d_Wire_Chamber_%c_Hits_with_cut", col1, layers_[i] );
          col1 = col1+3;
          sprintf(title,"Wire Chamber %c Hits with cut;X [mm];Y [mm]", layers_[i] );
          mePlanesT_[i] = m_dbe->book2D(name,title,100,-50,50,100,-50,50);   
        }
    
        sprintf(name,"h%02d_Wire_Chamber_%c_XHits", col2, layers_[i] );
        col2 = col2+3;
        sprintf(title,"Wire Chamber %c XHits;X [mm]", layers_[i] );
        meXvalue_[i] = m_dbe->book1D(name,title,100,-50,50);
        if ( i<3 ) {
          sprintf(name,"h%02d_Wire_Chamber_%c_XHits_with_cut", col2, layers_[i] );
          col2 = col2+3;
          sprintf(title,"Wire Chamber %c XHits with cut;X [mm]", layers_[i] );
          meXvalueT_[i]= m_dbe->book1D(name,title,100,-50,50);
        }
    
        sprintf(name,"h%02d_Wire_Chamber_%c_YHits", col3, layers_[i] );
        col3 = col3+3;
        sprintf(title,"Wire Chamber %c YHits;Y [mm]", layers_[i] );
        meYvalue_[i] = m_dbe->book1D(name,title,100,-50,50);
        if ( i<3 ) {
          sprintf(name,"h%02d_Wire_Chamber_%c_YHits_with_cut", col3, layers_[i] );
          col3 = col3+3;
          sprintf(title,"Wire Chamber %c YHits with cut;Y [mm]", layers_[i] );
          meYvalueT_[i] = m_dbe->book1D(name,title,100,-50,50);
        }
      }
      // Wire chamber efficiency histogram
      m_dbe->setCurrentFolder(baseFolder_+"/Wire_Chamber_Efficiency");
      meWCeff_ = m_dbe->bookProfile("WC_eff","Wire Chamber Efficiency by Plane;Plane;Efficiency",10,-0.5,9.5,100,0.,1.);
      meWCeff_->setBinLabel(1,"A X");
      meWCeff_->setBinLabel(2,"A Y");
      meWCeff_->setBinLabel(3,"B X");
      meWCeff_->setBinLabel(4,"B Y");
      meWCeff_->setBinLabel(5,"C X");
      meWCeff_->setBinLabel(6,"C Y");
      meWCeff_->setBinLabel(7,"D X");
      meWCeff_->setBinLabel(8,"D Y");
      meWCeff_->setBinLabel(9,"E X");
      meWCeff_->setBinLabel(10,"E Y");
     
      
      int nBin1=100;
      // QADCs for cherenkov:
      m_dbe->setCurrentFolder(baseFolder_+"/QADC_Monitor/Cherenkovs");
      
      meCHER1_ = m_dbe->book1D("h1_Cherenkov_QADC_1","Cherenkov QADC 1;ADC;Hits/ADC",nBin1,0,1000);
      meCHER2_ = m_dbe->book1D("h2_Cherenkov_QADC_2","Cherenkov QADC 2;ADC;Hits/ADC",nBin1,0,3000);
      meCHER3_ = m_dbe->book1D("h3_Cherenkov_QADC_3","Cherenkov QADC 3;ADC;Hits/ADC",nBin1,0,4000);
    
      meCHER1ped_ = m_dbe->book1D("h4_Cherenkov_QADC_1_ped","Cherenkov QADC 1, pedestal events;ADC;Hits/ADC",nBin1,0,1000);
      meCHER2ped_ = m_dbe->book1D("h5_Cherenkov_QADC_2_ped","Cherenkov QADC 2, pedestal events;ADC;Hits/ADC",nBin1,0,3000);
      meCHER3ped_ = m_dbe->book1D("h6_Cherenkov_QADC_3_ped","Cherenkov QADC 3, pedestal events;ADC;Hits/ADC",nBin1,0,4000);
      
      // QADCs for TOFs :
      m_dbe->setCurrentFolder(baseFolder_+"/QADC_Monitor/TOF_ADCs");
            
      meTOF1Sadc_ = m_dbe->book1D("h1_TOF_QADC_1S","TOF QADC 1 Saleve side;ADC;Hits/ADC",nBin1,0,1200);
      meTOF2Sadc_ = m_dbe->book1D("h2_TOF_QADC_2S","TOF QADC 2 Saleve side;ADC;Hits/ADC",nBin1,0,1200);
      meTOF1Jadc_ = m_dbe->book1D("h3_TOF_QADC 1J","TOF QADC 1 Jura side;ADC;Hits/ADC",nBin1,0,1200);
      meTOF2Jadc_ = m_dbe->book1D("h4_TOF_QADC_2J","TOF QADC 2 Jura side;ADC;Hits/ADC",nBin1,0,1200);
      
      meTOF1Spedadc_ = m_dbe->book1D("h5_TOF_QADC_1S_ped","TOF QADC 1 Saleve side, pedestal events;ADC;Hits/ADC",nBin1,0,600);
      meTOF2Spedadc_ = m_dbe->book1D("h6_TOF_QADC_2S_ped","TOF QADC 2 Saleve side, pedestal events;ADC;Hits/ADC",nBin1,0,600);
      meTOF1Jpedadc_ = m_dbe->book1D("h7_TOF_QADC_1J_ped","TOF QADC 1 Jura side, pedestal events;ADC;Hits/ADC",nBin1,0,600);
      meTOF2Jpedadc_ = m_dbe->book1D("h8_TOF_QADC_2J_ped","TOF QADC 2 Jura side, pedestal events;ADC;Hits/ADC",nBin1,0,600);

      // Book Trigger Scintillators: 14x14 cm, 4x4 cm, 2x2 cm, 14x14 cm
      m_dbe->setCurrentFolder(baseFolder_+"/QADC_Monitor/Trigger_Scintillators");
      
      meTrigSc1_ = m_dbe->book1D("h1_Trigger_Scint_1","Scintillator 1;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc2_ = m_dbe->book1D("h2_Trigger_Scint_2","Scintillator 2;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc3_ = m_dbe->book1D("h3_Trigger_Scint_3","Scintillator 3;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc4_ = m_dbe->book1D("h4_Trigger_Scint_4","Scintillator 4;ADC;Hits/ADC",nBin1,0,1000); 
    
      meTrigSc1ped_ = m_dbe->book1D("h5_Trigger_Scint_1_ped","Scintillator 1, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc2ped_ = m_dbe->book1D("h6_Trigger_Scint_2_ped","Scintillator 2, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc3ped_ = m_dbe->book1D("h7_Trigger_Scint_3_ped","Scintillator 3, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      meTrigSc4ped_ = m_dbe->book1D("h8_Trigger_Scint_4_ped","Scintillator 4, pedestal events;ADC;Hits/ADC",nBin1,0,1000);
      
      m_dbe->setCurrentFolder(baseFolder_+"/QADC_Monitor/Muon_Vetos");
      // Book VM front and back
      meVMF_ = m_dbe->book1D("h01_VM_front","VM front;ADC;Hits/ADC",nBin1,0,4100);
      meVMB_ = m_dbe->book1D("h02_VM_back","VM back;ADC;Hits/ADC",nBin1,0,4100);
    
      meVMFped_ = m_dbe->book1D("h04_VM_front_ped","VM front, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMBped_ = m_dbe->book1D("h05_VM_back_ped","VM back, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
    
      // Book Upstream Muon Veto (UVM in channel 24 on adc patchpannel)
      meUVMadc_ = m_dbe->book1D("h03_Upstream_Muon_Veto","Upstream Muon veto;ADC;Hits/ADC",nBin1,0,4100);
    
      meUVMadcped_ = m_dbe->book1D("h06_Upstream_Muon_Veto_ped","Upstream Muon veto, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      
      // Book Muon veto wall
      meVMu1_ = m_dbe->book1D("h07_Muon_veto_wall_1","Muon veto wall 1;ADC;Hits/ADC",nBin1,0,4100);
      meVMu2_ = m_dbe->book1D("h08_Muon_veto_wall_2","Muon veto wall 2;ADC;Hits/ADC",nBin1,0,4100);
      meVMu3_ = m_dbe->book1D("h09_Muon_veto_wall_3","Muon veto wall 3;ADC;Hits/ADC",nBin1,0,4100);
      meVMu4_ = m_dbe->book1D("h13_Muon_veto_wall_4","Muon veto wall 4;ADC;Hits/ADC",nBin1,0,4100);
      meVMu5_ = m_dbe->book1D("h14_Muon_veto_wall_5","Muon veto wall 5;ADC;Hits/ADC",nBin1,0,4100);
      meVMu6_ = m_dbe->book1D("h15_Muon_veto_wall_6","Muon veto wall 6;ADC;Hits/ADC",nBin1,0,4100);
      meVMu7_ = m_dbe->book1D("h19_Muon_veto_wall_7","Muon veto wall 7;ADC;Hits/ADC",nBin1,0,4100);
      meVMu8_ = m_dbe->book1D("h20_Muon_veto_wall_8","Muon veto wall 8;ADC;Hits/ADC",nBin1,0,4100);
    
      meVMu1ped_ = m_dbe->book1D("h10_Muon_veto_wall_1_ped","Muon veto wall 1, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu2ped_ = m_dbe->book1D("h11_Muon_veto_wall_2_ped","Muon veto wall 2, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu3ped_ = m_dbe->book1D("h12_Muon_veto_wall_3_ped","Muon veto wall 3, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu4ped_ = m_dbe->book1D("h16_Muon_veto_wall_4_ped","Muon veto wall 4, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu5ped_ = m_dbe->book1D("h17_Muon_veto_wall_5_ped","Muon veto wall 5, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu6ped_ = m_dbe->book1D("h18_Muon_veto_wall_6_ped","Muon veto wall 6, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu7ped_ = m_dbe->book1D("h21_Muon_veto_wall_7_ped","Muon veto wall 7, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
      meVMu8ped_ = m_dbe->book1D("h22_Muon_veto_wall_8_ped","Muon veto wall 8, pedestal events;ADC;Hits/ADC",nBin1,0,4100);
    
      
      // Book Beam halo info: (up, left, right, down) 
      // in the TBDataFormats/HcalTBObjects/interface/HcalTBBeamCounters.h
      m_dbe->setCurrentFolder(baseFolder_+"/QADC_Monitor/Beam_Halo");
      
      meBHalo1_ = m_dbe->book1D("h1_BV1_Beam_Halo_right","BV1, Beam Halo right;ADC;Hits/ADC",nBin1,0,1000);
      meBHalo2_ = m_dbe->book1D("h2_BV2_Beam_Halo_left","BV2, Beam Halo left;ADC;Hits/ADC",nBin1,0,1000); 
      meBHalo3_ = m_dbe->book1D("h3_BV3_Beam_Halo_up","BV3, Beam Halo up;ADC;Hits/ADC",nBin1,0,1000); 
      meBHalo4_ = m_dbe->book1D("h4_BV4_Beam_Halo_down","BV4, Beam Halo down;ADC;Hits/ADC",nBin1,0,1000); 
      
      meBHalo1ped_ = m_dbe->book1D("h5_BV1_Beam_Halo_right_ped","BV1, Beam Halo right, pedestal events;ADC;Hits/ADC",nBin1,0,1000);
      meBHalo2ped_ = m_dbe->book1D("h6_BV2_Beam_Halo_left_ped","BV2, Beam Halo left, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      meBHalo3ped_ = m_dbe->book1D("h7_BV3_Beam_Halo_up_ped","BV3, Beam Halo up, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      meBHalo4ped_ = m_dbe->book1D("h8_BV4_Beam_Halo_down_ped","BV4, Beam Halo down, pedestal events;ADC;Hits/ADC",nBin1,0,1000); 
      
      // TDCs and Timing info
      m_dbe->setCurrentFolder(baseFolder_+"/TOF_TDCs_and_Timing");
        
      meTOF1S_ = m_dbe->book1D("h01_TOF_TDC_1S","TOF TDC 1 Saleve side;TDC",nBin1,0,4400);
      meTOF2S_ = m_dbe->book1D("h02_TOF_TDC_2S","TOF TDC 2 Saleve side;TDC",nBin1,0,4400);
      meTOFTS_ = m_dbe->book1D("h03_TOF_Time_S_TOF1S-TOF2S","TOF Time -- Saleve:TOF1S-TOF2S;TDC",1000,-500,500);
    
      meTOF1J_ = m_dbe->book1D("h04_TOF_TDC_1J","TOF TDC 1 Jura side;TDC",nBin1,0,3700);
      meTOF2J_ = m_dbe->book1D("h05_TOF_TDC_2J","TOF TDC 2 Jura side;TDC",nBin1,0,3700);
      meTOFTJ_ = m_dbe->book1D("h06_TOF_Time_J_TOF1J-TOF2J","TOF Time -- Jura:TOF1J-TOF2J;TDC",1000,-500,500);
    
      meTOFT11_ = m_dbe->book1D("h07_TOF_Time_TOF1S-TOF1J","TOF Time: TOF1S-TOF1J;TDC",100,-250,250);
      meTOFT22_ = m_dbe->book1D("h08_TOF_Time_TOF2S-TOF2J","TOF Time: TOF2S-TOF2J;TDC",100,-250,250);
      meTOFT12_ = m_dbe->book1D("h09_TOF_Time_TOF1S-TOF2J","TOF Time: TOF1S-TOF2J;TDC",800,-200,1000);
      meTOFT21_ = m_dbe->book1D("h10_TOF_Time_TOF2S-TOF1J","TOF Time: TOF2S-TOF1J;TDC",100,-500,500);
    
      meTOFT11m22_ = m_dbe->book1D("h11_TOFtime_Mean","TOFtime:Mean;TDC",1000,-500.,500.);
    
      // 2 dim TOF QDC (QADC) plots:
      meTOFT1SvJ_ = m_dbe->book2D("h12_QDCs_TOF1J_vs_TOF1S","QDCs: TOF1J vs TOF1S;ADC;ADC",100,50,1000,100,50,1000); 
      meTOFT2JvS_ = m_dbe->book2D("h13_QDCs_TOF1J_vs_TOF1S","QDCs: TOF1J vs TOF1S;ADC;ADC",100,50,1000,100,50,1000);

      meTrigger_ = m_dbe->book1D("h14_Trigger_Time","Trigger Time",600,2400,2700);
      meTTCL1A_ = m_dbe->book1D("h15_TTC_L1A_Time","TTC L1A Time",1000,3000,4000);
      
      meDT1_ = m_dbe->book1D("h16_Trigger-L1A_Phase","Trigger-L1A Phase",400,-950,-800);
      meDT3_ = m_dbe->book1D("h17_L1A-BC_Phase","L1A-Beam Coincidence Phase",400,-20,150);
    } // if (m_dbe)
    
  return;
}     
      

void H2BeamLineMonitor::processEvent(const HcalTBTriggerData& trigger,
                                     const HcalTBBeamCounters& qadc,
                                     const HcalTBEventPosition& epos,
                                     const HcalTBTiming& time)
{     
      
  if (showTiming)
    { 
      cpu_timer.reset(); cpu_timer.start();
    } 
      
  if (!m_dbe)
  {   
    if (fVerbosity) cout <<"H2BeamLineMonitor::processEvent   DQMStore not instantiated!!!"<<endl;
    return;
  }   
      
  // Fill Event Number
  ++ievt_;
  meEVT_->Fill(ievt_);
      
  if ( trigger.wasBeamTrigger() ) {
    tbbeamEvt_++;
  } else {
    tbpedEvt_++;
  }   
  
      
  // Wire Chambers, filling:
  vector<double> xh,yh;

  if ( qadc.S3adc() > 190 ) {

    xh.clear();
    yh.clear();
      
    epos.getChamberHits('A',xh,yh);
      if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
        for(unsigned int h=0; h<xh.size(); h++) {
            mePlanesT_[0]->Fill(xh[h],yh[h]);
            meXvalueT_[0]->Fill(xh[h]);
            meYvalueT_[0]->Fill(yh[h]);
        }
    } 
      
    xh.clear();
    yh.clear();
      
    epos.getChamberHits('B',xh,yh);
    if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
        for(unsigned int h=0; h<xh.size(); h++) {
            mePlanesT_[1]->Fill(xh[h],yh[h]);
            meXvalueT_[1]->Fill(xh[h]);
            meYvalueT_[1]->Fill(yh[h]);
        }
    }
  
    xh.clear();
    yh.clear();
  
    epos.getChamberHits('C',xh,yh);
    if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
        for(unsigned int h=0; h<xh.size(); h++) {
            mePlanesT_[2]->Fill(xh[h],yh[h]);
            meXvalueT_[2]->Fill(xh[h]);
            meYvalueT_[2]->Fill(yh[h]);
        }
    }
  } // endif cut on S3

  // for all events:
  xh.clear();
  yh.clear();
  
  int nHits[16]; // For wire chamber efficiency: A-H =8*2=16

  epos.getChamberHits('A',xh,yh);
  nHits[0]=xh.size(); 
  nHits[1]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[0]->Fill(xh[h],yh[h]);
          meXvalue_[0]->Fill(xh[h]);
          meYvalue_[0]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('B',xh,yh);
  nHits[2]=xh.size(); 
  nHits[3]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[1]->Fill(xh[h],yh[h]);
          meXvalue_[1]->Fill(xh[h]);
          meYvalue_[1]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('C',xh,yh);
  nHits[4]=xh.size(); 
  nHits[5]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[2]->Fill(xh[h],yh[h]);
          meXvalue_[2]->Fill(xh[h]);
          meYvalue_[2]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('D',xh,yh);
  nHits[6]=xh.size(); 
  nHits[7]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[3]->Fill(xh[h],yh[h]);
          meXvalue_[3]->Fill(xh[h]);
          meYvalue_[3]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('E',xh,yh);
  nHits[8]=xh.size(); 
  nHits[9]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[4]->Fill(xh[h],yh[h]);
          meXvalue_[4]->Fill(xh[h]);
          meYvalue_[4]->Fill(yh[h]);
      }
  }
  xh.clear();
  yh.clear();

  epos.getChamberHits('F',xh,yh);
  nHits[10]=xh.size(); 
  nHits[11]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[5]->Fill(xh[h],yh[h]);
          meXvalue_[5]->Fill(xh[h]);
          meYvalue_[5]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('G',xh,yh);
  nHits[12]=xh.size(); 
  nHits[13]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[6]->Fill(xh[h],yh[h]);
          meXvalue_[6]->Fill(xh[h]);
          meYvalue_[6]->Fill(yh[h]);
      }
  }

  xh.clear();
  yh.clear();

  epos.getChamberHits('H',xh,yh);
  nHits[14]=xh.size(); 
  nHits[15]=yh.size();
  if ((xh.size()>0) && (yh.size()>0) && (xh.size()==yh.size()) ) {
      for(unsigned int h=0; h<xh.size(); h++) {
          mePlanes_[7]->Fill(xh[h],yh[h]);
          meXvalue_[7]->Fill(xh[h]);
          meYvalue_[7]->Fill(yh[h]);
      }
  }
  // end of wire chamber filling
  
  // Efficiency - requires hits in all the WC planes, other than the one, which efficiency is measured (#Hits ==N-1).
  // For A-C WCs, tollerates 1 dead plane. (>=N-2 is used instead of ==N-1)
  for(int iPl=0;iPl<6;iPl++)
   {
     int oHits=0;  
     for(int cPl=0;cPl<6;cPl++)
       if(cPl!=iPl && nHits[cPl]>0) oHits++;
     if(oHits>=4) meWCeff_->Fill(iPl,(nHits[iPl]>0));
   }
  // For D-E WCs, tollerates 1 dead plane.(>=N-2 is used instead of ==N-1) 
  for(int iPl=6;iPl<10;iPl++)
   {
     int oHits=0;  
     for(int cPl=6;cPl<10;cPl++)
       if(cPl!=iPl && nHits[cPl]>0) oHits++;
     if(oHits>=2) meWCeff_->Fill(iPl,(nHits[iPl]>0));
   }
  
  // Fill Cherenkov values
  meCHER1_->Fill(qadc.CK1adc());
  meCHER2_->Fill(qadc.CK2adc());
  meCHER3_->Fill(qadc.CK3adc());
  
  // Fill TOF QADC values
  meTOF1Sadc_->Fill(qadc.TOF1Sadc());
  meTOF2Sadc_->Fill(qadc.TOF2Sadc());
  meTOF1Jadc_->Fill(qadc.TOF1Jadc());
  meTOF2Jadc_->Fill(qadc.TOF2Jadc());
  
  // Fill Trigger Scintillators: 14x14 cm, 4x4 cm, 2x2 cm, 14x14 cm
  meTrigSc1_->Fill(qadc.S1adc()); 
  meTrigSc2_->Fill(qadc.S2adc()); 
  meTrigSc3_->Fill(qadc.S3adc()); 
  meTrigSc4_->Fill(qadc.S4adc());
  
  // Fill VM front and back
  meVMF_->Fill(qadc.VMFadc());
  meVMB_->Fill(qadc.VMBadc());

  // Fill Upstream Muon Veto, now in Sci528adc, 
  meUVMadc_->Fill(qadc.Sci528adc());

  // Fill Muon veto wall
  meVMu1_->Fill(qadc.VM1adc());
  meVMu2_->Fill(qadc.VM2adc());
  meVMu3_->Fill(qadc.VM3adc());
  meVMu4_->Fill(qadc.VM4adc());
  meVMu5_->Fill(qadc.VM5adc());
  meVMu6_->Fill(qadc.VM6adc());
  meVMu7_->Fill(qadc.VM7adc());
  meVMu8_->Fill(qadc.VM8adc());

  // Fill Beam halo info: (up, left, right, down)
  meBHalo1_->Fill(qadc.BH1adc());
  meBHalo2_->Fill(qadc.BH2adc()); 
  meBHalo3_->Fill(qadc.BH3adc()); 
  meBHalo4_->Fill(qadc.BH4adc()); 
  
  // Fill histos for the pedestal events:
  if (trigger.wasInSpillPedestalTrigger()  
    || trigger.wasOutSpillPedestalTrigger())
  {

      // Fill Cherenkov values
      meCHER1ped_->Fill(qadc.CK1adc());
      meCHER2ped_->Fill(qadc.CK2adc());
      meCHER3ped_->Fill(qadc.CK3adc());
    
      // Fill TOF QADC values
      meTOF1Spedadc_->Fill(qadc.TOF1Sadc());
      meTOF2Spedadc_->Fill(qadc.TOF2Sadc());
      meTOF1Jpedadc_->Fill(qadc.TOF1Jadc());
      meTOF2Jpedadc_->Fill(qadc.TOF2Jadc());
    
      // Fill Trigger Scintillators: 14x14 cm, 4x4 cm, 2x2 cm, 14x14 cm
      meTrigSc1ped_->Fill(qadc.S1adc()); 
      meTrigSc2ped_->Fill(qadc.S2adc()); 
      meTrigSc3ped_->Fill(qadc.S3adc()); 
      meTrigSc4ped_->Fill(qadc.S4adc()); 
    
      // Fill VM front and back
      meVMFped_->Fill(qadc.VMFadc());
      meVMBped_->Fill(qadc.VMBadc());
    
      // Fill Upstream Muon Veto, now in Sci528adc, 
      meUVMadcped_->Fill(qadc.Sci528adc());
    
      // Fill Muon veto wall
      meVMu1ped_->Fill(qadc.VM1adc());
      meVMu2ped_->Fill(qadc.VM2adc());
      meVMu3ped_->Fill(qadc.VM3adc());
      meVMu4ped_->Fill(qadc.VM4adc());
      meVMu5ped_->Fill(qadc.VM5adc());
      meVMu6ped_->Fill(qadc.VM6adc());
      meVMu7ped_->Fill(qadc.VM7adc());
      meVMu8ped_->Fill(qadc.VM8adc());
    
      // Fill Beam halo info: (up, left, right, down)
      meBHalo1ped_->Fill(qadc.BH1adc());
      meBHalo2ped_->Fill(qadc.BH2adc()); 
      meBHalo3ped_->Fill(qadc.BH3adc()); 
      meBHalo4ped_->Fill(qadc.BH4adc()); 
  
  }//endif trigger was pedestal
  
  // Fill TDCs and Timing info
  meTOF1S_->Fill(time.TOF1Stime());
  meTOF2S_->Fill(time.TOF2Stime());
  meTOF1J_->Fill(time.TOF1Jtime());
  meTOF2J_->Fill(time.TOF2Jtime());
  
  // Now we DON'T want the pedestal events:
  if ( trigger.wasBeamTrigger() ) {
  
    if ( (time.TOF1Stime()<3700) && (time.TOF2Stime()<3700) ) {
      meTOFTS_->Fill((time.TOF1Stime() - time.TOF2Stime()));
    }
    if ( (time.TOF1Jtime()<3700) && (time.TOF2Jtime()<3700) ) {
      meTOFTJ_->Fill((time.TOF1Jtime() - time.TOF2Jtime()));
    }
  
    if ( (time.TOF1Stime()<3700) && (time.TOF1Jtime()<3700) ) {
      meTOFT11_->Fill((time.TOF1Stime() - time.TOF1Jtime()));
      }
    if ( (time.TOF2Stime()<3700) && (time.TOF2Jtime()<3700) ) {
      meTOFT22_->Fill((time.TOF2Stime() - time.TOF2Jtime()));
    }
  
    if ( (time.TOF1Stime()<3700) && (time.TOF2Jtime()<3700) ) {
      meTOFT12_->Fill((time.TOF1Stime() - time.TOF2Jtime()));
    }
    if ( (time.TOF2Stime()<3700) && (time.TOF1Jtime()<3700) ) {
      meTOFT21_->Fill((time.TOF2Stime() - time.TOF1Jtime()));
      if ( (time.TOF1Stime()<3700) && (time.TOF2Jtime()<3700) ) {
          meTOFT11m22_->Fill((time.TOF1Stime()+time.TOF1Jtime() - time.TOF2Stime()-time.TOF2Jtime())/2.0);
      }
    }
    
    if ( (qadc.TOF1Sadc()<3700 && qadc.TOF1Jadc()<3700) ) {
        meTOFT1SvJ_->Fill(qadc.TOF1Sadc(),qadc.TOF1Jadc());
    }
    if ( (qadc.TOF2Sadc()<3700 && qadc.TOF2Jadc()<3700) ) {
        meTOFT2JvS_->Fill(qadc.TOF2Sadc(),qadc.TOF2Jadc());
    }
  
  } //if was beam trigger
  
  //Leaving this to be still filled for pedestal AND beam events, and overflow:
//   hTOF_DT1_->Fill((time.TOF1Stime() - time.TOF2Stime())-(time.TOF1Jtime() - time.TOF2Jtime()));
//   hTOF_DT2_->Fill(time.TOF1Stime() - time.TOF1Jtime());
//   hTOF_DT3_->Fill(time.TOF2Stime() - time.TOF2Jtime());
  
  meTrigger_->Fill(time.triggerTime());
  meTTCL1A_->Fill(time.ttcL1Atime());
  // this is not working any more:
//   hBeamCoinc_->Fill(time.BeamCoincidenceCount());
  
  meDT1_->Fill(time.triggerTime() - time.ttcL1Atime());
//   hDT2_->Fill(time.triggerTime() - time.BeamCoincidenceCount());
//   hDT3_->Fill(time.ttcL1Atime() - time.BeamCoincidenceCount());
  if (time.ttcL1Atime()>0 && time.BeamCoincidenceCount()>0) meDT3_->Fill(time.ttcL1Atime() - time.BeamCoincidenceHits(0)-1000);
  
  
  if (showTiming)
   {
     cpu_timer.stop();  cout <<"TIMER:: H2BeamLineMonitor PROCESSEVENT -> "<<cpu_timer.cpuTime()<<endl;
   }

  return;
} // void H2BeamLineMonitor::processEvent

