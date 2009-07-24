#ifndef DQM_HCALMONITORTASKS_H2PEDESTALMONITOR_H
#define DQM_HCALMONITORTASKS_H2PEDESTALMONITOR_H

#include "DQM/HcalMonitorTasks/interface/HcalBaseMonitor.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "CalibCalorimetry/HcalAlgos/interface/HcalDbASCIIIO.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

/** \class H2PedestalMonitor
 *
 * $Date: 2009/07/22 $
 * \author Philip Lawson (BU)
 * \author Dinko Ferencek (UMD) -- small code adaptations 
 */

// Global constants
const int MAXCAPS = 4;
const int NUM_TIMESLICES = 10;

#define HF_ETA_OFFSET 28
#define HF_PHI_OFFSET 2
#define HO_ETA_OFFSET 4
#define HO_PHI_OFFSET 1
#define HB_ETA_OFFSET 5
#define HB_PHI_OFFSET 1

// Struct to store ADC totals and CapId cross products (for correlation values)
typedef struct
{
   float ADCTotal[MAXCAPS];
   int ADCEntries[MAXCAPS];
   float ADCProdTotal[MAXCAPS][MAXCAPS];
   int ADCProdEntries[MAXCAPS][MAXCAPS];
} channelRawData;

// "Dumb" class to store per CapId pedestal & correlation data
//  Not to be treated as a robust class. Since it's local I'm not going to worry about input validation and what not
typedef class
{
   public:
      float CapPedMean[MAXCAPS];
      float CapPedWidth[MAXCAPS];
      float CapProdMean[MAXCAPS][MAXCAPS];

      float CapCov(int capid1, int capid2) 
      { return CapProdMean[capid1][capid2] - CapPedMean[capid1]*CapPedMean[capid2]; }

      float CapCorr(int capid1, int capid2)
      { return CapCov(capid1,capid2)/(sqrt(fabs(CapCov(capid1,capid1)))*sqrt(fabs(CapCov(capid2,capid2)))); }
} channelPeds;

// Map of raw channel data / pedestal data by DetId 
typedef std::map<HcalDetId, channelRawData> mapChannelRaw;
typedef std::map<HcalDetId, channelPeds> mapChannelPeds;
typedef std::map<HcalSubdetector, MonitorElement*> mapSubdetMonElement;

// Helper function
std::string getDetectorName(const HcalDetId& detid)
{
   std::string name;
   switch(detid.subdet())
   {
      case HcalBarrel:
	 name = "HB"; break;
      case HcalEndcap:
	 name = "HE"; break;
      case HcalOuter:
	 name = "HO"; break;
      case HcalForward:
	 name = "HF"; break;
      default:
	 name = "unknown";
   }

   return name;
}

bool asciiFile (const std::string fParam) {
   return fParam.find (':') == std::string::npos && std::string (fParam, fParam.length () - 4) == ".txt";
}

template <class T>
bool dumpObject (T* fObject, const std::string& fFile) {
  if (fFile.empty()) return false;
  if (asciiFile(fFile)) {
    std::ofstream stream (fFile.c_str());
    HcalDbASCIIIO::dumpObject (stream, *fObject);
    return true;
  } else {
    std::cout << ">> Output pedestal file name is invalid" << std::endl;
    return false;
  }
}

class H2PedestalMonitor: public HcalBaseMonitor {
 public:
  H2PedestalMonitor();
  ~H2PedestalMonitor();
  
  void setup(const edm::ParameterSet& ps, DQMStore* dbe);
  void reset();
  void done();
  void clearME();

  // processEvent routine -- specifies what inputs are looked at each event
  void processEvent(const HcalTBTriggerData& trigger,
	            const HBHEDigiCollection& hbhe,
                    const HODigiCollection& ho,
                    const HFDigiCollection& hf);

  template <class T>
     void fillRawData(const T& digi);

  void calculatePedestals(const mapChannelRaw& raw, mapChannelPeds* pPeds);
  void fillHistos(const mapChannelPeds& peds);

 private:

  int ievt_;
  int jevt_;
  MonitorElement* meEVT_;
  
  HcalPedestals* m_pRawPedestals;

  // Data structs
  mapChannelRaw hbRawData, hfRawData, hoRawData;	//< Raw Digi Data
  mapChannelPeds hbPeds, hfPeds, hoPeds;		//< Calculated pedestal values for subdetectors

  // Configurable parameters
  int m_startSample;
  int m_endSample;
  int m_MaxADCCounts;
  int m_NumEvents;
  bool m_bUseInSpillPeds;
  int m_hbDepths;
  std::string outputPedestalFile_; 

  // Add in histograms here (MonitorElements can handle TH1F, TH2F, TProfile plots)
  mapSubdetMonElement pedestalMeans;
  mapSubdetMonElement pedestalWidths;
  mapSubdetMonElement hohfEtaPhi[MAXCAPS];
  HBTB09EtaPhiHists hbEtaPhi[MAXCAPS];
  
}; // class H2PedestalMonitor

#endif
