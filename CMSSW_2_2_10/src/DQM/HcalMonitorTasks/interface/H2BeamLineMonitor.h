#ifndef DQM_HCALMONITORTASKS_H2BEAMLINEMONITOR_H
#define DQM_HCALMONITORTASKS_H2BEAMLINEMONITOR_H

#include "DQM/HcalMonitorTasks/interface/HcalBaseMonitor.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include <iostream>
#include <vector>

/** \class H2BeamLineMonitor
 *
 * $Date: 2009/07/10 $
 * \author L. Berntzon  (Texas Tech.), N. Marinelli (Univ. of Notre Dame)
 * \author Jordan Damgov (INRNE, Bulgaria) -- wire chamber efficiency code
 * \author Dinko Ferencek (UMD) -- ported code to the HCAL DQM framework
 */

class H2BeamLineMonitor: public HcalBaseMonitor {
 public:
  H2BeamLineMonitor();
  ~H2BeamLineMonitor();
  
  void setup(const edm::ParameterSet& ps, DQMStore* dbe);
  void reset();
  void done();
  void clearME();

  // processEvent routine -- specifies what inputs are looked at each event
  void processEvent(const HcalTBTriggerData& trigger,
                    const HcalTBBeamCounters& qadc,
                    const HcalTBEventPosition& epos,
                    const HcalTBTiming& time);

 private:

  int ievt_;
  MonitorElement* meEVT_;
  
  int tbbeamEvt_;
  int tbpedEvt_;

  // Add in histograms here (MonitorElements can handle TH1F, TH2F, TProfile plots)
  MonitorElement* meCHER1_;
  MonitorElement* meCHER2_;
  MonitorElement* meCHER3_;
  MonitorElement* meCHER1ped_;
  MonitorElement* meCHER2ped_;
  MonitorElement* meCHER3ped_;
  
  MonitorElement* meTOF1Sadc_;
  MonitorElement* meTOF2Sadc_;
  MonitorElement* meTOF1Jadc_;
  MonitorElement* meTOF2Jadc_;
  MonitorElement* meTOF1Spedadc_;
  MonitorElement* meTOF2Spedadc_;
  MonitorElement* meTOF1Jpedadc_;
  MonitorElement* meTOF2Jpedadc_;
  
  MonitorElement* meTrigSc1_;  
  MonitorElement* meTrigSc2_;  
  MonitorElement* meTrigSc3_;  
  MonitorElement* meTrigSc4_;
  MonitorElement* meTrigSc1ped_;  
  MonitorElement* meTrigSc2ped_;  
  MonitorElement* meTrigSc3ped_;  
  MonitorElement* meTrigSc4ped_;
  
  MonitorElement* meVMF_;  
  MonitorElement* meVMB_;  
  MonitorElement* meUVMadc_;
  MonitorElement* meVMFped_;  
  MonitorElement* meVMBped_;  
  MonitorElement* meUVMadcped_;
  
  MonitorElement* meVMu1_;  
  MonitorElement* meVMu2_; 
  MonitorElement* meVMu3_;  
  MonitorElement* meVMu4_;  
  MonitorElement* meVMu5_;  
  MonitorElement* meVMu6_;  
  MonitorElement* meVMu7_;  
  MonitorElement* meVMu8_;  
  MonitorElement* meVMu1ped_;  
  MonitorElement* meVMu2ped_; 
  MonitorElement* meVMu3ped_;  
  MonitorElement* meVMu4ped_;  
  MonitorElement* meVMu5ped_;  
  MonitorElement* meVMu6ped_;  
  MonitorElement* meVMu7ped_;  
  MonitorElement* meVMu8ped_;  
  
  MonitorElement* meBHalo1_;
  MonitorElement* meBHalo2_;
  MonitorElement* meBHalo3_;
  MonitorElement* meBHalo4_;
  MonitorElement* meBHalo1ped_;
  MonitorElement* meBHalo2ped_;
  MonitorElement* meBHalo3ped_;
  MonitorElement* meBHalo4ped_;


  MonitorElement* meTOF1S_;
  MonitorElement* meTOF2S_;
  MonitorElement* meTOFTS_;

  MonitorElement* meTOF1J_;
  MonitorElement* meTOF2J_;
  MonitorElement* meTOFTJ_;

  MonitorElement* meTOFT11_;
  MonitorElement* meTOFT22_; 
  MonitorElement* meTOFT12_;
  MonitorElement* meTOFT21_;

  MonitorElement* meTOFT11m22_;

  MonitorElement* meTOFT1SvJ_;
  MonitorElement* meTOFT2JvS_;

  MonitorElement* meTrigger_;
  MonitorElement* meTTCL1A_;
  MonitorElement* meBeamCoinc_;
  MonitorElement* meDT1_;
  MonitorElement* meDT2_;
  MonitorElement* meDT3_;

  // for Wire Chambers:

  vector<char> layers_;

  MonitorElement* mePlanes_[8];
  MonitorElement* mePlanesT_[3];

  MonitorElement* meXvalue_[8];
  MonitorElement* meXvalueT_[3];

  MonitorElement* meYvalue_[8];
  MonitorElement* meYvalueT_[3];
  
  MonitorElement* meWCeff_;
}; // class H2BeamLineMonitor

#endif
