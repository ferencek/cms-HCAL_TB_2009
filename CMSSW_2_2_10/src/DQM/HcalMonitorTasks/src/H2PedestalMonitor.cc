#include "DQM/HcalMonitorTasks/interface/H2PedestalMonitor.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;


// constructor
H2PedestalMonitor::H2PedestalMonitor() {}

// destructor
H2PedestalMonitor::~H2PedestalMonitor() {
  delete m_pRawPedestals;
}

void H2PedestalMonitor::reset() {}

void H2PedestalMonitor::done() {}

void H2PedestalMonitor::clearME()
{
  if (m_dbe) 
    {
      m_dbe->setCurrentFolder(baseFolder_);
      m_dbe->removeContents();
    } // if (m_dbe)
  meEVT_=0;
} // void H2PedestalMonitor::clearME()


void H2PedestalMonitor::setup(const edm::ParameterSet& ps, DQMStore* dbe){

  HcalBaseMonitor::setup(ps,dbe);  // perform setups of base class

  ievt_=0; // set event counter to 0
  jevt_=0;
  
  // number of HB depths in TB09
  m_hbDepths = 4;
     
  // Setup configurable parameters
  m_startSample = 0;		// TODO: Make adjustable
  m_endSample = 9;
  m_MaxADCCounts = 30;
  m_NumEvents = 500;
  m_bUseInSpillPeds = false;
  
  baseFolder_ = rootFolder_ + "H2PedestalMonitor"; // Will create an "H2PedestalMonitor" subfolder in .root output
  if (fVerbosity) cout <<"<H2PedestalMonitor::setup> Setup in progress"<<endl;

  if (m_dbe)
    {
      m_dbe->setCurrentFolder(baseFolder_);
      meEVT_ = m_dbe->bookInt("H2PedestalMonitor Event Number"); // store event number
      
      m_dbe->setCurrentFolder(baseFolder_+"/HB");
      pedestalMeans[HcalBarrel] = m_dbe->book1D("HB_Pedestal_Means","HB Pedestal Means;ADC Counts",m_MaxADCCounts,0,m_MaxADCCounts);
      pedestalWidths[HcalBarrel] = m_dbe->book1D("HB_Pedestal_Widths","HB Pedestal Widths;ADC Counts",50,0,5);
      for (int CapId=0; CapId<MAXCAPS; CapId++) {
        stringstream name;
        stringstream title;
	name << "HB_Pedestals_CapId" << CapId;
        title << "HB Pedestals for CapId" << CapId;
        hbEtaPhi[CapId].setup(m_dbe,name.str(),title.str(),"i#eta;i#phi",m_hbDepths);
      }
      
      m_dbe->setCurrentFolder(baseFolder_+"/HO");
      pedestalMeans[HcalOuter] = m_dbe->book1D("HO_Pedestal_Means","HO Pedestal Means;ADC Counts",m_MaxADCCounts,0,m_MaxADCCounts);
      pedestalWidths[HcalOuter] = m_dbe->book1D("HO_Pedestal_Widths","HO Pedestal Widths;ADC Counts",50,0,5);
      for (int CapId=0; CapId<MAXCAPS; CapId++) {
        stringstream name;
        stringstream title;
	name << "HO_Pedestals_CapId" << CapId;
        title << "HO Pedestals for CapId" << CapId << ";i#eta;i#phi";
        hohfEtaPhi[CapId][HcalOuter] = m_dbe->book2D(name.str(),title.str(),6,4.5,10.5,21,1.5,22.5);
      }
      
      m_dbe->setCurrentFolder(baseFolder_+"/HF");
      pedestalMeans[HcalForward] = m_dbe->book1D("HF_Pedestal_Means","HF Pedestal Means;ADC Counts",m_MaxADCCounts,0,m_MaxADCCounts);
      pedestalWidths[HcalForward] = m_dbe->book1D("HF_Pedestal_Widths","HF Pedestal Widths;ADC Counts",50,0,5);
      for (int CapId=0; CapId<MAXCAPS; CapId++) {
        stringstream name;
        stringstream title;
	name << "HF_Pedestals_CapId" << CapId;
        title << "HF Pedestals for CapId" << CapId << ";i#eta;i#phi";
        hohfEtaPhi[CapId][HcalForward] = m_dbe->book2D(name.str(),title.str(),12,28.5,40.5,4,2.5,6.5);
      }
    } // if (m_dbe)
    
    outputPedestalFile_ = ps.getUntrackedParameter<string>("outputPedestalFile","");
    
    // Create pedestal collection
    m_pRawPedestals = new HcalPedestals();
    
  return;
}     
      

void H2PedestalMonitor::processEvent(const HcalTBTriggerData& trigger,
      				     const HBHEDigiCollection& hbhe,
                                     const HODigiCollection& ho,
                                     const HFDigiCollection& hf)
{     
      
  if (showTiming)
    { 
      cpu_timer.reset(); cpu_timer.start();
    } 
      
  if (!m_dbe)
  {   
    if (fVerbosity) cout <<"H2PedestalMonitor::processEvent   DQMStore not instantiated!!!"<<endl;
    return;
  }   
     
  ++jevt_;
   
  if(trigger.wasOutSpillPedestalTrigger() || (trigger.wasInSpillPedestalTrigger() && m_bUseInSpillPeds))
  {
      // Fill Event Number
      ++ievt_;
      meEVT_->Fill(ievt_);

      // Get data for every HBHE CapID
      try
      {
	 if(!hbhe.size()) throw (int) hbhe.size();

	 HBHEDigiCollection::const_iterator j;
	 for(j=hbhe.begin(); j!=hbhe.end(); j++)
	 {
	    const HBHEDataFrame digi = (const HBHEDataFrame)(*j);	// Grab digi
	    fillRawData(digi);
	 }
      }
      catch(int i)
      {
	 edm::LogInfo("DQMPeds") << "Failed to get HBHE digis! (" << i << " digis read in)";
      }

      // Get data for every HO CapID
      try
      {
	 if(!ho.size()) throw (int) ho.size();

	 HODigiCollection::const_iterator j;
	 for(j=ho.begin(); j!=ho.end(); j++)
	 {
	    const HODataFrame digi = (const HODataFrame)(*j);	// Grab digi
	    fillRawData(digi);
	 }
      }
      catch(int i)
      {
	 edm::LogInfo("DQMPeds") << "Failed to get HO digis! (" << i << " digis read in)";
      }

      // Get data for every HF CapID
      try
      {
	 if(!hf.size()) throw (int) hf.size();

	 HFDigiCollection::const_iterator j;
	 for(j=hf.begin(); j!=hf.end(); j++)
	 {
	    const HFDataFrame digi = (const HFDataFrame)(*j);	// Grab digi
	    fillRawData(digi);
	 }
      }
      catch(int i)
      {
	 edm::LogInfo("DQMPeds") << "Failed to get HF digis! (" << i << " digis read in)";
      }
  }
  
  if(ievt_ && jevt_%checkNevents_ == 0)
  {
     calculatePedestals(hbRawData, &hbPeds);
     calculatePedestals(hoRawData, &hoPeds);
     calculatePedestals(hfRawData, &hfPeds);
     
     pedestalMeans[HcalBarrel]->Reset();
     pedestalMeans[HcalOuter]->Reset();
     pedestalMeans[HcalForward]->Reset();
     pedestalWidths[HcalBarrel]->Reset();
     pedestalWidths[HcalOuter]->Reset();
     pedestalWidths[HcalForward]->Reset();
     
     // TODO: Plot the pedestals
     fillHistos(hbPeds);
     fillHistos(hoPeds);
     fillHistos(hfPeds);
     
     // Output txt file for pedestals
     dumpObject(m_pRawPedestals, outputPedestalFile_);
  }

  
  if (showTiming)
   {
     cpu_timer.stop();  cout <<"TIMER:: H2PedestalMonitor PROCESSEVENT -> "<<cpu_timer.cpuTime()<<endl;
   }

  return;
} // void H2PedestalMonitor::processEvent


template <class T>
void H2PedestalMonitor::fillRawData(const T& digi)
{
   HcalDetId detid = digi.id();

   // Find out which subdetector we are
   mapChannelRaw* subdetData = NULL;	// I hate pointers to STL objects
   switch(detid.subdet())
   {
      case HcalBarrel:
      case HcalEndcap:
	 subdetData = &hbRawData;
	 break;
      case HcalOuter:
	 subdetData = &hoRawData;
	 break;
      case HcalForward:
	 subdetData = &hfRawData;
	 break;
      default:
	 cerr << "H2PedestalMonitor::fillRawData(): Unexpected subdet type encountered (subdet = " << detid.subdet() << ")" << endl;
	 return;
   }

   // See if this is the first entry
   mapChannelRaw::iterator testIter = subdetData->find(detid);
   if(testIter == subdetData->end())
   {
      for(int capid=0; capid<MAXCAPS; capid++)
      {
	 (*subdetData)[detid].ADCTotal[capid] = 0;
         (*subdetData)[detid].ADCEntries[capid] = 0;
	 for(int capid2=0; capid2<MAXCAPS; capid2++)
	 {
	    (*subdetData)[detid].ADCProdTotal[capid][capid2] = 0;
            (*subdetData)[detid].ADCProdEntries[capid][capid2] = 0;
	 }
      }	 
   }

   // Loop through digis
   for(int TS=m_startSample; TS<digi.size() && TS<=m_endSample; TS++)
   {
      int capid = digi[TS].capid();
      int adc = digi[TS].adc();

      (*subdetData)[detid].ADCTotal[capid]+=adc;	// Add to adc array
      (*subdetData)[detid].ADCEntries[capid]++;
      // Loop through neighboring timeslices
      for(int stepTS=0; stepTS < MAXCAPS && (TS + stepTS) < digi.size(); stepTS++)
      {
	 int capid2 = digi[TS + stepTS].capid();
	 int adc2 = digi[TS + stepTS].adc();

	 (*subdetData)[detid].ADCProdTotal[capid][capid2]+=(adc * adc2); // Add to product array
         (*subdetData)[detid].ADCProdEntries[capid][capid2]++;
      }
   }
}

void H2PedestalMonitor::calculatePedestals(const mapChannelRaw& raw, mapChannelPeds* pPeds)
{
   mapChannelPeds& peds = *pPeds;	// I hate pointers to STL containers
    
   // Loop through raw data
   for(mapChannelRaw::const_iterator iter = raw.begin(); iter != raw.end(); iter++)
   {
      HcalDetId detid = iter->first;
      channelPeds& channelData = peds[detid];

      // Loop through each capid
      for(int capid=0; capid<MAXCAPS; capid++)
      {
	 float ped_mean = iter->second.ADCTotal[capid]/static_cast<float>(iter->second.ADCEntries[capid]);
         // Set Pedestal
	 channelData.CapPedMean[capid] = ped_mean;


	 // Determine Product Means
	 for(int capid2=0; capid2<MAXCAPS; capid2++)
	 {
	    float prod_mean = iter->second.ADCProdTotal[capid][capid2]/static_cast<float>(iter->second.ADCProdEntries[capid][capid2]);
	    channelData.CapProdMean[capid][capid2] = prod_mean;
	 }

	 // Set Pedestal Width
	 channelData.CapPedWidth[capid] = channelData.CapCov(capid,capid);

	 // Validate pedestals
	 // For now use a "standard" validation method. TODO Improve this
	/* channelData.CapPedQ[capid] = channelData.CapPedMean[capid]/channelData.CapCov(capid,capid);
	 if(channelData.CapPedQ[capid] > 3)
	    channelData.CapFlag[capid] = PedestalOK;
	 else
	    channelData.CapFlag[capid] = PedestalBadQ;

	 // Add Pedestal to total
	 if(m_saveFlag & SaveTotals)
	 {
	     channel->AllPedMeans->Fill(channelData.CapPedMean[capid]);
	     channel->AllPedWidths->Fill(sqrt(channelData.CapCov(capid,capid)));
	 }*/
      }

      // Store correlation matrix if user asked for it
      /*if(m_saveFlag & SaveCorrelation)
      {
	 for(int capid1=0; capid1<MAXCAPS; capid1++)
	    for(int capid2=0; capid2<MAXCAPS; capid2++)
	       channelData.CapCorrHisto->SetBinContent(capid1+1,capid2+1,channelData.CapCorr(capid1,capid2));
      }

      // Add pedestals and widths
      // Store pedestal values if no flags were raised
      if(channelData.ValidPeds() || m_bIgnoreBadPedestals)
      {
	 HcalPedestal item(detid, channelData.CapPedMean[0], channelData.CapPedMean[1], channelData.CapPedMean[2], channelData.CapPedMean[3]);
	 m_pRawPedestals->addValues(item);

	 HcalPedestalWidth pedWidth(detid);
	 for(int capid1=0; capid1 < MAXCAPS; capid1++)
	    for(int capid2=0; capid2 < MAXCAPS; capid2++)
	       pedWidth.setSigma(capid1,capid2,channelData.CapCov(capid1,capid2));
	 m_pRawPedestalWidths->addValues(pedWidth);
      }*/

   }
}

void H2PedestalMonitor::fillHistos(const mapChannelPeds& peds)
{   
   // Loop through pedestal data
   for(mapChannelPeds::const_iterator iter = peds.begin(); iter != peds.end(); iter++)
   {
      HcalDetId detid = iter->first;
      HcalSubdetector subdet = detid.subdet();
      
      HcalPedestal item(detid, iter->second.CapPedMean[0], iter->second.CapPedMean[1], iter->second.CapPedMean[2], iter->second.CapPedMean[3]);
      m_pRawPedestals->addValues(item);

      for(int CapId=0; CapId<MAXCAPS; CapId++)
      {
	 int eta = detid.ieta();
	 int phi = tb09Phi(detid); //detid.iphi();

	 pedestalMeans[subdet]->Fill(iter->second.CapPedMean[CapId]);
	 pedestalWidths[subdet]->Fill(iter->second.CapPedWidth[CapId]);
         
	 switch(subdet)
	 {
	    case HcalOuter:
	       hohfEtaPhi[CapId][subdet]->setBinContent(eta-HO_ETA_OFFSET, phi-HO_PHI_OFFSET, iter->second.CapPedMean[CapId]);
	       break;
	    case HcalForward:
	       hohfEtaPhi[CapId][subdet]->setBinContent(eta-HF_ETA_OFFSET, phi-HF_PHI_OFFSET, iter->second.CapPedMean[CapId]);
	       break;
	    case HcalBarrel:
		int depth = tb09Depth(detid);
		hbEtaPhi[CapId].depth[depth-1]->setBinContent(eta-HB_ETA_OFFSET, phi-HB_PHI_OFFSET, iter->second.CapPedMean[CapId]);
		break;
	    default:
	       break;
	 }
      }
   }

}
