#ifndef DQM_HCALMONITORTASKS_H2TRIGGERMONITOR_H
#define DQM_HCALMONITORTASKS_H2TRIGGERMONITOR_H

#include "DQM/HcalMonitorTasks/interface/HcalBaseMonitor.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include <iostream>
#include <vector>

/** \class H2TriggerMonitor
 *
 * $Date: 2009/07/18 $
 * \author Dinko Ferencek (UMD)
 */

class H2TriggerMonitor: public HcalBaseMonitor {
 public:
  H2TriggerMonitor();
  ~H2TriggerMonitor();
  
  void setup(const edm::ParameterSet& ps, DQMStore* dbe);
  void reset();
  void done();
  void clearME();

  // processEvent routine -- specifies what inputs are looked at each event
  void processEvent(const HcalTBTriggerData& trigger);

 private:

  int ievt_;
  MonitorElement* meEVT_;
  
  // Add in histograms here (MonitorElements can handle TH1F, TH2F, TProfile plots)
  MonitorElement* meTriggerType_;
  
}; // class H2TriggerMonitor

#endif
