# def hcallayout(i, p, *rows): i["Hcal/Layouts/" + p] = DQMItem(layout=rows)
# 
# hcallayout(dqmitems, "01 HCAL Shifter Checklist Plots - DataFormat",
#            [{ 'path': "Hcal/DataFormatMonitor/DCC Plots/DCC Nonzero Spigot Conditions",
#               'description':"A list of potential hardware issues, arranged by FED.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" },
#             { 'path': "Hcal/DataFormatMonitor/DCC Plots/Event Fragment Size for each FED",
#               'description':"Average event fragment size for each FED.  Size should be between 1000-2000 bytes.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" }],
#             [{ 'path': "Hcal/DataFormatMonitor/HcalFEDChecking/FEDEntries",
#               'description':"Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" },
#             { 'path': "Hcal/DataFormatMonitor/HTR Plots/HTR Error Word by Crate",
#               'description':"HTR errors arranged by crate.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" }],
#             [{ 'path': "Hcal/DataFormatMonitor/Readout Chain DataIntegrity Check",
#               'description':"Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" }],
#            )
# 
# hcallayout(dqmitems, "02 HCAL Shifter Checklist Plots - RecHits",
#            [{ 'path': "Hcal/RecHitMonitor_Hcal/rechit_1D_plots/HB_energy_1D",
#               'description':"This shows the average rechit energy for each cell in HB.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" },
#             { 'path': "Hcal/RecHitMonitor_Hcal/rechit_1D_plots/HE_energy_1D",
#               'description':"This shows the average rechit energy for each cell in HE.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" }],
#            [{ 'path': "Hcal/RecHitMonitor_Hcal/rechit_1D_plots/HF_energy_1D",
#               'description':"This shows the average rechit energy for each cell in HF.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" },
#             { 'path': "Hcal/RecHitMonitor_Hcal/rechit_1D_plots/HO_energy_1D",
#               'description':"This shows the average rechit energy for each cell in HO.  Please see detailed explanation of this plot at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalShifterChecklist#DQM_Plots>HcalShifterChecklist</a>" }]
#            )
# 
# hcallayout(dqmitems, "03 HCAL Shifter Checklist Plots - Summaries",
#            [{ 'path':"Hcal/EventInfo/reportSummaryMap",
#              'description':"This shows the fraction of bad cells in each subdetector.  All subdetectors should appear green, except ZDC, which should be grey."}],
#            [{ 'path': "Hcal/EventInfo/reportSummaryContents/Hcal_HB",
#               'description':  "This number indicates the fraction of good cells in HB"},
#             { 'path': "Hcal/EventInfo/reportSummaryContents/Hcal_HE",
#               'description':  "This number indicates the fraction of good cells in HE"}],
#            [{ 'path': "Hcal/EventInfo/reportSummaryContents/Hcal_HF",
#               'description':  "This number indicates the fraction of good cells in HF"},
#             { 'path': "Hcal/EventInfo/reportSummaryContents/Hcal_HO",
#               'description':  "This number indicates the fraction of good cells in H0"}],
#            )
# 
# hcallayout(dqmitems, "HCAL Pedestals",
#           [{ 'path': "Hcal/PedestalMonitor_Hcal/HB HF Depth 1 Pedestal Mean Map ADC",
#              'description': "All filled values should appear green (ADC value ~ = 3) <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" },
#            { 'path': "Hcal/PedestalMonitor_Hcal/HB HF Depth 2 Pedestal Mean Map ADC",
#              'description': "All filled values should appear green (ADC value ~ = 3). <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }],
#            [{ 'path': "Hcal/PedestalMonitor_Hcal/HE Depth 1 Pedestal Mean Map ADC",
#               'description': "All filled values should appear green (ADC value ~ = 3) <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" },
#             { 'path': "Hcal/PedestalMonitor_Hcal/HE Depth 2 Pedestal Mean Map ADC",
#               'description': "All filled values should appear green (ADC value ~ = 3). <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }],
#            [{ 'path': "Hcal/PedestalMonitor_Hcal/HE Depth 3 Pedestal Mean Map ADC",
#               'description': "All filled values should appear green (ADC value ~ = 3) <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" },
#             { 'path': "Hcal/PedestalMonitor_Hcal/HO ZDC Pedestal Mean Map ADC",
#               'description': "All filled values should appear green (ADC value ~ = 3). <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }],)
# 
# hcallayout(dqmitems, "HCAL Trigger Primitives",
#            [{ 'path': "Hcal/TrigPrimMonitor/Energy Plots/ADC spectrum positive TP",
#               'description': "Trig Prim Monitor currently disabled for offline debugging.<a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }],
#            [{ 'path': "Hcal/TrigPrimMonitor/Electronics Plots/TP vs Digi",
#               'description': "Trig Prim Monitor currently disabled for offline debugging.<a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }]
#            )
# 
# hcallayout(dqmitems, "HCAL Dead Cell Check",
#           [{ 'path': "Hcal/DeadCellMonitor_Hcal/ ProblemDeadCells",
#              'description': "Potential dead cell candidates in all depths. Seriously dead if dead for >5% of a full run. iPhi (0 to 72) by iEta (-41 to 41) More at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }],
#            [{ 'path': "Hcal/DeadCellMonitor_Hcal/Problem_TotalDeadCells_HCAL",
#              'description': "Total number of dead cells found in HCAL"}],
#            #[{ 'path': "Hcal/DeadCellMonitor_Hcal/Problem_TotalDeadCells_HB",
#            #   'description': "Total number of dead cells found in HB"},
#            # { 'path': "Hcal/DeadCellMonitor_Hcal/Problem_TotalDeadCells_HE",
#            #   'description': "Total number of dead cells found in HE"}],
#            #[{ 'path': "Hcal/DeadCellMonitor_Hcal/Problem_TotalDeadCells_HF",
#            #   'description': "Total number of dead cells found in HF"},
#            #{ 'path': "Hcal/DeadCellMonitor_Hcal/Problem_TotalDeadCells_HO",
#            #  'description': "Total number of dead cells found in HO"}],
#            )
# 
# hcallayout(dqmitems, "HCAL Hot Cell Check",
#           [{ 'path': "Hcal/HotCellMonitor_Hcal/ ProblemHotCells",
#                    'description': "A cell is considered potentially hot if: Above a threshold energy; More than 3 sigma above its pedestal value; or Energy is especially large compared to its neighbors. Seriously hot if hot for >5% of a full run. All depths. iPhi (0 to 72) by iEta (-41 to 41) More at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }]
#            )
# 
# hcallayout(dqmitems, "HCAL Digi Problems",
#           [{ 'path': "Hcal/DigiMonitor_Hcal/ ProblemDigis",
#                    'description': "A digi cell is considered bad if the capid rotation for that digi was incorrect, or if the sum of ADC counts over all time slices for the digi is 0. This plot is the sum of bad digis over all depths. iPhi (0 to 72) by iEta (-41 to 41) More at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistograms>HcalDQMHistograms</a>" }]
#            )
# 
# hcallayout(dqmitems, "HCAL DataFormat Problems",
#            [{ 'path': "Hcal/DataFormatMonitor/ HardwareWatchCells",
#               'description': "A Data Format error indicates that the data received from this channel was somehow corrupted or compromised.  This plot is the sum of bad digis over all d\epths. iPhi (0 to 72) by iEta (-41 to 41) More at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistogra\ms>HcalDQMHistograms</a>" }]
#                       )
# 
# 
# hcallayout(dqmitems, "HCAL Unsuppressed Channels",
#            [{ 'path': "Hcal/DataFormatMonitor/HTR Plots/Fraction UnSuppressed Events",
#               'description': "This shows the fraction of unsuppressed events for each FED and SPIGOT. More (eventually)  at <a href=https://twiki.cern.ch/twiki/bin/view/CMS/HcalDQMHistogra\ms>HcalDQMHistograms</a>" }]
#                       )

