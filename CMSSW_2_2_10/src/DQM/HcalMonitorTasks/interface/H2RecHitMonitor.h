#ifndef DQM_HCALMONITORTASKS_H2RECHITMONITOR_H
#define DQM_HCALMONITORTASKS_H2RECHITMONITOR_H

#include "DQM/HcalMonitorTasks/interface/HcalBaseMonitor.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include <iostream>
#include <vector>

// Define number of eta, phi bins for H2 histogram objects

/** \class H2RecHitMonitor
 *
 * $Date: 2009/07/13 $
 * \author Dinko Ferencek (UMD)
 */

class H2RecHitMonitor: public HcalBaseMonitor {
 public:
  H2RecHitMonitor();
  ~H2RecHitMonitor();
  
  void setup(const edm::ParameterSet& ps, DQMStore* dbe);
  void reset();
  void done();
  void clearME();

  // processEvent routine -- specifies what inputs are looked at each event
  void processEvent(const HcalTBTriggerData& trigger,
                    const HBHERecHitCollection& hbHits,
                    const HORecHitCollection& hoHits,
                    const HFRecHitCollection& hfHits);

 private:
 
  void fillHistos(void);

  int ievt_;
  int jevt_;
  MonitorElement* meEVT_;
  
  // Add in histograms here (MonitorElements can handle TH1F, TH2F, TProfile plots)
  MonitorElement* hbTowerEnergyDist;
  MonitorElement* hbTowerEnergy;
  MonitorElement* hbTowerOccupancy;
  HBTB09Hists       hbRecHitEnergyDistByDepth;
  HBTB09EtaPhiHists hbRecHitEnergyByDepth;
  HBTB09EtaPhiHists hbRecHitOccupancyByDepth;
 
  MonitorElement* hoRecHitEnergyDist; 
  MonitorElement* hoRecHitEnergy;
  MonitorElement* hoRecHitOccupancy;

  MonitorElement* hfRecHitEnergyDist;
  MonitorElement* hfRecHitEnergy;
  MonitorElement* hfRecHitOccupancy;
  
  int hbDepths_;
  
  double energyHB_[4][4][16];
  unsigned int occupancyHB_[4][4][16];
  double towerEnergyHB_[4][4];
  unsigned int towerOccupancyHB_[4][4];
  double energyHO_[6][21];
  unsigned int occupancyHO_[6][21];
  double energyHF_[12][4];
  unsigned int occupancyHF_[12][4];
  
}; // class H2RecHitMonitor

#endif
