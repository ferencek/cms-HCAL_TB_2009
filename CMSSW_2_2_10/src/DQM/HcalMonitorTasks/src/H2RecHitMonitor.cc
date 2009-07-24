#include "DQM/HcalMonitorTasks/interface/H2RecHitMonitor.h"

using namespace std;


// constructor
H2RecHitMonitor::H2RecHitMonitor() {}

// destructor
H2RecHitMonitor::~H2RecHitMonitor() {}

void H2RecHitMonitor::reset() {}

void H2RecHitMonitor::done() {}

void H2RecHitMonitor::clearME()
{
  if (m_dbe) 
    {
      m_dbe->setCurrentFolder(baseFolder_);
      m_dbe->removeContents();
    } // if (m_dbe)
  meEVT_=0;
} // void H2RecHitMonitor::clearME()


void H2RecHitMonitor::setup(const edm::ParameterSet& ps, DQMStore* dbe){

  HcalBaseMonitor::setup(ps,dbe);  // perform setups of base class

  ievt_=0; // set event counter to 0
  jevt_=0;
  
  // number of HB depths in TB09
  hbDepths_ = 4;
  
  baseFolder_ = rootFolder_ + "H2RecHitMonitor"; // Will create an "H2RecHitMonitor" subfolder in .root output
  if (fVerbosity) cout <<"<H2RecHitMonitor::setup> Setup in progress"<<endl;

  if (m_dbe)
    {
      m_dbe->setCurrentFolder(baseFolder_);
      meEVT_ = m_dbe->bookInt("H2RecHitMonitor Event Number"); // store event number
      
      // HB
      m_dbe->setCurrentFolder(baseFolder_+"/HB");
      hbTowerEnergyDist = m_dbe->book1D("d00_tower_energy_dist","Max HB Tower Energy Distribution (Beam Trigger);Max Energy",203,-45,3000);
      hbTowerEnergy = m_dbe->book2D("h00_tower_energy","HB Tower Energy (Beam Trigger);i#eta;i#phi",4,5.5,9.5,4,1.5,5.5);
      hbRecHitEnergyDistByDepth.setup(m_dbe,"rechit_energy_dist","HB RecHit Energy Distribution (Beam Trigger)","Energy",105,-20,400,hbDepths_);
      hbRecHitEnergyByDepth.setup(m_dbe,"rechit_energy","HB RecHit Energy (Beam Trigger)","i#eta;i#phi",hbDepths_);
      m_dbe->setCurrentFolder(baseFolder_+"/HB/Occupancy");
      hbTowerOccupancy = m_dbe->book2D("h00_tower_occupancy","HB Tower Occupancy (Beam Trigger);i#eta;i#phi",4,5.5,9.5,4,1.5,5.5);
      hbRecHitOccupancyByDepth.setup(m_dbe,"rechit_occupancy","HB RecHit Occupancy (Beam Trigger)","i#eta;i#phi",hbDepths_);

      // HO
      m_dbe->setCurrentFolder(baseFolder_+"/HO");
      hoRecHitEnergyDist = m_dbe->book1D("d_rechit_energy_dist","HO RecHit Energy Distribution (Beam Trigger);Energy",105,-20,400);
      hoRecHitEnergy     = m_dbe->book2D("h_rechit_energy","HO RecHit Energy (Beam Trigger);i#eta;i#phi",6,4.5,10.5,21,1.5,22.5);
      hoRecHitOccupancy  = m_dbe->book2D("h_rechit_occupancy","HO RecHit Occupancy (Beam Trigger);i#eta;i#phi",6,4.5,10.5,21,1.5,22.5);
      
      // HF
      m_dbe->setCurrentFolder(baseFolder_+"/HF");
      hfRecHitEnergyDist = m_dbe->book1D("d_rechit_energy_dist","HF RecHit Energy Distribution (Beam Trigger);Energy",110,-40,400);
      hfRecHitEnergy     = m_dbe->book2D("h_rechit_energy","HF RecHit Energy (Beam Trigger);i#eta;i#phi",12,28.5,40.5,4,2.5,6.5);
      hfRecHitOccupancy  = m_dbe->book2D("h_rechit_occupancy","HF RecHit Occupancy (Beam Trigger);i#eta;i#phi",12,28.5,40.5,4,2.5,6.5);
      
      // set HB array to zero
      for (int eta=0;eta<4;++eta)
        {
          for (int phi=0;phi<4;++phi)
            {
              towerEnergyHB_[eta][phi]=0;
              for (int depth=0;depth<hbDepths_;++depth)
                {
                  energyHB_[eta][phi][depth]=0;
                  occupancyHB_[eta][phi][depth]=0; 
                }
            }
        }
      // set HO array to zero 
      for (int eta=0;eta<6;++eta)
        {
          for (int phi=0;phi<21;++phi)
            {
              energyHO_[eta][phi]=0;
              occupancyHO_[eta][phi]=0;
            }
        }
      // set HF array to zero 
      for (int eta=0;eta<12;++eta)
        {
          for (int phi=0;phi<4;++phi)
            {
              energyHF_[eta][phi]=0;
              occupancyHF_[eta][phi]=0;
            }
        }
    } // if (m_dbe)
    
  return;
}     
      

void H2RecHitMonitor::processEvent(const HcalTBTriggerData& trigger,
                                   const HBHERecHitCollection& hbheHits,
                                   const HORecHitCollection& hoHits,
                                   const HFRecHitCollection& hfHits)
{     
      
  if (showTiming)
    { 
      cpu_timer.reset(); cpu_timer.start();
    } 
      
  if (!m_dbe)
  {   
    if (fVerbosity) cout <<"H2RecHitMonitor::processEvent   DQMStore not instantiated!!!"<<endl;
    return;
  }
  
  ++jevt_;
     
  if (trigger.wasBeamTrigger()) {
  
    // Fill Event Number
    ++ievt_;
    meEVT_->Fill(ievt_);
    
    double towerEnergyHBEvt_[4][4];
    for (int eta=0;eta<4;++eta)
      {
        for (int phi=0;phi<4;++phi)
          {
            towerEnergyHBEvt_[eta][phi] = -99999.;
          }
      }
    // loop over HBHE RecHits
    for (HBHERecHitCollection::const_iterator iter=hbheHits.begin(); iter!=hbheHits.end(); ++iter) 
    {
      double en = iter->energy();
  
      HcalDetId id(iter->detid().rawId());
      int ieta = id.ieta();
      int iphi = tb09Phi(id);
      int depth = tb09Depth(id);

      ++occupancyHB_[ieta-6][iphi-2][depth-1];
      energyHB_[ieta-6][iphi-2][depth-1]+=en;
      towerEnergyHB_[ieta-6][iphi-2]+=en;
      if (towerEnergyHBEvt_[ieta-6][iphi-2]==-99999.) towerEnergyHBEvt_[ieta-6][iphi-2]=en;
      else towerEnergyHBEvt_[ieta-6][iphi-2]+=en;
        
      hbRecHitEnergyDistByDepth.depth[depth-1]->Fill(en);
    }
    // HB tower energy and occupancy
    double maxTowerEnergyHB = -99999.;
    for (int eta=0;eta<4;++eta)
      {
        for (int phi=0;phi<4;++phi)
          {
            if (towerEnergyHBEvt_[eta][phi]>-99999.)
              {
                ++towerOccupancyHB_[eta][phi];
                
                if (towerEnergyHBEvt_[eta][phi]>maxTowerEnergyHB) maxTowerEnergyHB = towerEnergyHBEvt_[eta][phi];
              }
          }
      }
    hbTowerEnergyDist->Fill(maxTowerEnergyHB);
    
    // loop over HO RecHits
    for (HORecHitCollection::const_iterator iter=hoHits.begin(); iter!=hoHits.end(); ++iter) 
    {
      double en = iter->energy();
  
      HcalDetId id(iter->detid().rawId());
      int ieta = id.ieta();
      int iphi = id.iphi();
    
      ++occupancyHO_[ieta-5][iphi-2];
      energyHO_[ieta-5][iphi-2]+=en;
      
      hoRecHitEnergyDist->Fill(en);   
    }
    
    // loop over HF RecHits
    for (HFRecHitCollection::const_iterator iter=hfHits.begin(); iter!=hfHits.end(); ++iter) 
    {
      double en = iter->energy();
  
      HcalDetId id(iter->detid().rawId());
      int ieta = id.ieta();
      int iphi = tb09Phi(id);
      
      ++occupancyHF_[ieta-29][iphi-3];
      energyHF_[ieta-29][iphi-3]+=en;
      
      hfRecHitEnergyDist->Fill(en);
    }
  }
  
  if (ievt_ && jevt_%checkNevents_ == 0)
    {
      fillHistos();
    }
  
  if (showTiming)
   {
     cpu_timer.stop();  cout <<"TIMER:: H2RecHitMonitor PROCESSEVENT -> "<<cpu_timer.cpuTime()<<endl;
   }

  return;
} // void H2RecHitMonitor::processEvent

void H2RecHitMonitor::fillHistos(void)
{

  if (ievt_>0)
    {
      // here, pedestals are subtracted dynamically
      // fill in HB histos
      for (int eta=0;eta<4;++eta)
        {
          for (int phi=0;phi<4;++phi)
            {
              if (towerOccupancyHB_[eta][phi]>0) 
                {
                   hbTowerEnergy->setBinContent(eta+1, phi+1, towerEnergyHB_[eta][phi]/towerOccupancyHB_[eta][phi]);
                   hbTowerOccupancy->setBinContent(eta+1, phi+1, towerOccupancyHB_[eta][phi]);
                }
              for (int depth=0;depth<hbDepths_;++depth)
                {
                  if (occupancyHB_[eta][phi][depth]>0)
                    {
                      hbRecHitEnergyByDepth.depth[depth]->setBinContent(eta+1, phi+1, energyHB_[eta][phi][depth]/occupancyHB_[eta][phi][depth]);
                      hbRecHitOccupancyByDepth.depth[depth]->setBinContent(eta+1, phi+1, occupancyHB_[eta][phi][depth]);
                    }
                }
            }
        }
      // fill in HO histos 
      for (int eta=0;eta<6;++eta)
        {
          for (int phi=0;phi<21;++phi)
            {
              if (occupancyHO_[eta][phi]>0)
                {
                  hoRecHitEnergy->setBinContent(eta+1, phi+1, energyHO_[eta][phi]/occupancyHO_[eta][phi]);
                  hoRecHitOccupancy->setBinContent(eta+1, phi+1, occupancyHO_[eta][phi]);
                }
            }
        }
      // fill in HF histos 
      for (int eta=0;eta<12;++eta)
        {
          for (int phi=0;phi<4;++phi)
            {
              if (occupancyHF_[eta][phi]>0)
                {
                  hfRecHitEnergy->setBinContent(eta+1, phi+1, energyHF_[eta][phi]/occupancyHF_[eta][phi]);
                  hfRecHitOccupancy->setBinContent(eta+1, phi+1, occupancyHF_[eta][phi]);
                }
            }
        }  
    }

} // void H2RecHitMonitor::fillHistos
