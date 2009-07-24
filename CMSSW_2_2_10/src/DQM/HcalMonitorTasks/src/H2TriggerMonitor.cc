#include "DQM/HcalMonitorTasks/interface/H2TriggerMonitor.h"

using namespace std;


// constructor
H2TriggerMonitor::H2TriggerMonitor() {}

// destructor
H2TriggerMonitor::~H2TriggerMonitor() {}

void H2TriggerMonitor::reset() {}

void H2TriggerMonitor::done() {}

void H2TriggerMonitor::clearME()
{
  if (m_dbe) 
    {
      m_dbe->setCurrentFolder(baseFolder_);
      m_dbe->removeContents();
    } // if (m_dbe)
  meEVT_=0;
} // void H2TriggerMonitor::clearME()


void H2TriggerMonitor::setup(const edm::ParameterSet& ps, DQMStore* dbe){

  HcalBaseMonitor::setup(ps,dbe);  // perform setups of base class

  ievt_=0; // set event counter to 0
  
  baseFolder_ = rootFolder_ + "H2TriggerMonitor"; // Will create an "H2TriggerMonitor" subfolder in .root output
  if (fVerbosity) cout <<"<H2TriggerMonitor::setup> Setup in progress"<<endl;

  if (m_dbe)
    {
      m_dbe->setCurrentFolder(baseFolder_);
      meEVT_ = m_dbe->bookInt("H2TriggerMonitor Event Number"); // store event number
      
      meTriggerType_ = m_dbe->book1D("h_TriggerType","Trigger Type",5,0.5,5.5);
      meTriggerType_->setBinLabel(1,"In-Spill Ped");
      meTriggerType_->setBinLabel(2,"Out-Spill Ped");
      meTriggerType_->setBinLabel(3,"Beam");
      meTriggerType_->setBinLabel(4,"LED");
      meTriggerType_->setBinLabel(5,"Laser");
    } // if (m_dbe)
    
  return;
}     
      

void H2TriggerMonitor::processEvent(const HcalTBTriggerData& trigger)
{     
      
  if (showTiming)
    { 
      cpu_timer.reset(); cpu_timer.start();
    } 
      
  if (!m_dbe)
  {   
    if (fVerbosity) cout <<"H2TriggerMonitor::processEvent   DQMStore not instantiated!!!"<<endl;
    return;
  }   
      
  // Fill Event Number
  ++ievt_;
  meEVT_->Fill(ievt_);

  if (trigger.wasInSpillPedestalTrigger())  meTriggerType_->Fill(1);
  if (trigger.wasOutSpillPedestalTrigger()) meTriggerType_->Fill(2);
  if (trigger.wasBeamTrigger())             meTriggerType_->Fill(3);
  if (trigger.wasLEDTrigger())              meTriggerType_->Fill(4);
  if (trigger.wasLaserTrigger())            meTriggerType_->Fill(5);
  
  if (showTiming)
   {
     cpu_timer.stop();  cout <<"TIMER:: H2TriggerMonitor PROCESSEVENT -> "<<cpu_timer.cpuTime()<<endl;
   }

  return;
} // void H2TriggerMonitor::processEvent

