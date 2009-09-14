#include "SimCalorimetry/HcalZeroSuppressionAlgos/interface/HcalZSAlgoRealistic.h"
#include <iostream>

HcalZSAlgoRealistic::HcalZSAlgoRealistic(HcalZeroSuppressionAlgo::ZSMode mode, int levelHB, int levelHE, int levelHO, int levelHF) : 
  HcalZeroSuppressionAlgo(mode),
  thresholdHB_(levelHB),
  thresholdHE_(levelHE),
  thresholdHO_(levelHO),
  thresholdHF_(levelHF)
{
}

HcalZSAlgoRealistic::HcalZSAlgoRealistic(HcalZeroSuppressionAlgo::ZSMode mode) : 
  HcalZeroSuppressionAlgo(mode)
{
  thresholdHB_ = -1;
  thresholdHE_ = -1;
  thresholdHO_ = -1;
  thresholdHF_ = -1;
}


  
//template <class DIGI> 
//For HBHE Data Frame 
bool HcalZSAlgoRealistic::keepMe(const HBHEDataFrame& inp, int threshold) const{
  
  bool keepIt=false;
  int mask = 999;
  if ((threshold < 0) && (m_dbService != 0)){
    threshold = (m_dbService->getHcalZSThreshold(inp.id()))->getValue();
  }
  
  //determine the sum of 2 timeslices
  for (int i=0; i< inp.size()-1 && !keepIt; i++) {
    int sum=0;
    
    for (int j=i; j<(i+2); j++){
      sum+=inp[j].adc();
      //pedsum+=pedave;
    }
    if (mask==0) continue; 
    else if (sum>=threshold) keepIt=true;
  }
  return keepIt;
}

//For HO Data Frame 
bool HcalZSAlgoRealistic::keepMe(const HODataFrame& inp, int threshold) const{
  
  bool keepIt=false;
  int mask = 999;
  if ((threshold < 0) && (m_dbService != 0)){
    threshold = (m_dbService->getHcalZSThreshold(inp.id()))->getValue();
  }
  
  //determine the sum of 2 timeslices
  for (int i=0; i< inp.size()-1 && !keepIt; i++) {
    int sum=0;
    
    for (int j=i; j<(i+2); j++){
      sum+=inp[j].adc();
      //pedsum+=pedave;
    }
    if (mask==0) continue; 
    else if (sum>=threshold) keepIt=true;
  }
  return keepIt;
}

//For HF Data Frame 
bool HcalZSAlgoRealistic::keepMe(const HFDataFrame& inp, int threshold) const{
  
  bool keepIt=false;
  int mask = 999;
  if ((threshold < 0) && (m_dbService != 0)){
    threshold = (m_dbService->getHcalZSThreshold(inp.id()))->getValue();
  }
  
  //determine the sum of 2 timeslices
  for (int i=0; i< inp.size()-1 && !keepIt; i++) {
    int sum=0;
    
    for (int j=i; j<(i+2); j++){
      sum+=inp[j].adc();
      //pedsum+=pedave;
    }
    if (mask==0) continue; 
    else if (sum>=threshold) keepIt=true;
  }
  return keepIt;
}


bool HcalZSAlgoRealistic::shouldKeep(const HBHEDataFrame& digi) const{
  if (digi.id().subdet()==HcalBarrel) 
    return keepMe(digi,thresholdHB_);
  else return keepMe(digi,thresholdHE_);
}  

bool HcalZSAlgoRealistic::shouldKeep(const HODataFrame& digi) const{
  return keepMe(digi,thresholdHO_);
}

bool HcalZSAlgoRealistic::shouldKeep(const HFDataFrame& digi) const{
  return keepMe(digi,thresholdHF_);
}
