river_climate_model <- function (nYears, CC_Temp, CC_Amp) 
{
  #Scorff parameters T°C:        ADJUSTED on 1970-2007 data from Scorff 5/03/2010
  if(missing(CC_Temp)) {
    mT <- 12.674299
  } else {
    mT<-seq(12.674299,12.674299+ CC_Temp,length=365*nYears)  #MeanT
  }
    aT <- 5.909091
    csT <- 114.780948
    alpT <- 0.95184170929478
    betT <- 0.449967327959108

  #Scorff parameters Flow:      ADJUSTED on 1970-2007 data from Scorff 5/03/2010
    mF <- -0.02
    if(missing(CC_Amp)) {
      aF <- 1.010139
    } else {
    aF <- seq(1.010139,1.010139* CC_Amp,length=365*nYears)
    }
    csF <- 327.836285
    alpF <- 0.964034622660953
    betF <- 0.118343974744226

  #compute water temperature
    temperatures <- sinus_model_resid_ar(mT, aT, csT, alpT, betT, 1:(365 * nYears), 365)
  #compute flow 
    logrelflow <- sinus_model_resid_ar(mF, aF, csF, alpF, betF, 1:(365 * nYears), 365) - 0.2 #correction due to residuals not centered on 0
    
temperatures[temperatures < 0] <- 0.01
    logrelflow[logrelflow > 3] <- 3
    logrelflow[logrelflow < -3] <- -3
    return(list(temperatures = temperatures, logrelflow = logrelflow))
}
