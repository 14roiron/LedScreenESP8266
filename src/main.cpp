//*

#define DEBUG 0

#include <Arduino.h>
#include "LittleFS.h"
#include "LedPannel.h"
#include "DaftPunkHead.h"
#include "WiFiManager.h"
#include "webServer.h"
#include "updater.h"
#include "configManager.h"
#include "dashboard.h"
#include "timeSync.h"




struct task
{    
    unsigned long rate;
    unsigned long previous;
};
void runMatrixAnimation(void);
task ScrollText = { .rate = 100, .previous = 0 };

void saveCallback() {
    newMessageAvailable = getText(configManager.data.printingPhrase, newMessage, MESG_SIZE);
    ScrollText.rate= configManager.data.scrollSpeed;
    Serial.println(configManager.data.printingPhrase);
}

void setup() 
{
    Serial.begin(115200);

    LittleFS.begin();
    GUI.begin();
    configManager.begin();
    configManager.setConfigSaveCallback(saveCallback);
    WiFiManager.begin(configManager.data.projectName);
    timeSync.begin();
    dash.begin(500);
    // Display initialization
    mx.begin();
    mx.setShiftDataInCallback(scrollDataSource);
    //curMessage[0] = newMessage[0] = '\0';
    sprintf(curMessage, configManager.data.printingPhrase);
    ScrollText.rate= configManager.data.scrollSpeed;
    prevTimeAnim = millis();
    prevTimeDemo = millis();

}

void loop() 
{
    //software interrupts
    WiFiManager.loop();
    updater.loop();
    configManager.loop();
    dash.loop();

    //your code here
    //task A
    if(configManager.data.runDemo){
        runMatrixAnimation();
    }
    else{
        if (ScrollText.previous == 0 || (millis() - ScrollText.previous > ScrollText.rate))
        {
            scrollText();
            ScrollText.previous = millis();
            
        
        }
    }
}
//*/









void runMatrixAnimation(void)
// Schedule the animations, switching to the next one when the
// the mode switch is pressed.
{
  static  uint8_t state = 0;
  static  boolean bRestart = true;
  static boolean	bInMessages = false;
  boolean changeState = false;

  // check if one second has passed and then count down the demo timer. Once this
  // gets to zero, change the state.
  if (millis()-prevTimeDemo >= 1000)
  {
    prevTimeDemo = millis();
    if (--timeDemo == 0)
    {
      timeDemo = configManager.data.runDemoTime;
      changeState = true;
    }
  }

  if (changeState)
  {
    if (bInMessages) // the message display state
    {
    //   mesg++;
    //   if (mesg >= sizeof(msgTab)/sizeof(msgTab[0]))
    //   {
    //     mesg = 0;
    // 	bInMessages = false;
    //     
    //   }

        bInMessages=false;
    }
    if(configManager.data.randomRun)
        state=random(19);
    else
        state++;

    bRestart = true;
  };

  // now do whatever we do in the current state
  switch(state)
  {
    case  0: 
        if(configManager.data.activateTextAnimation)
        {
            bInMessages = true; bRestart = scrollText(bRestart, curMessage);
            break;
        }
        else{
            state++;
        }

    case  1: 
        if(configManager.data.activateGraphicMidline1)
        {
            bRestart = graphicMidline1(bRestart);      
            break;
        }
        else{
            state++;
        }

    case  2: 
        if(configManager.data.activateGraphicMidline2)
        {
            bRestart = graphicMidline2(bRestart);      
            break;
        }
        else{
            state++;
        }

    case  3: 
        if(configManager.data.activateGraphicScanner)
        {
            bRestart = graphicScanner(bRestart);       
            break;
        }
        else{
            state++;
        }

    case  4: 
        if(configManager.data.activateGraphicRandom)
        {
            bRestart = graphicRandom(bRestart);        
            break;
        }
        else{
            state++;
        }

    case  5: 
        if(configManager.data.activateGraphicFade)
        {
            bRestart = graphicFade(bRestart);          
            break;
        }
        else{
            state++;
        }

    case  6: 
        if(configManager.data.activateGraphicSpectrum1)
        {
            bRestart = graphicSpectrum1(bRestart);     
            break;
        }
        else{
            state++;
        }

    case  7: 
        if(configManager.data.activateGraphicHeartbeat)
        {
            bRestart = graphicHeartbeat(bRestart);     
            break;
        }
        else{
            state++;
        }

    case  8: 
        if(configManager.data.activateGraphicHearts)
        {
            bRestart = graphicHearts(bRestart);        
            break;
        }
        else{
            state++;
        }

    case  9: 
        if(configManager.data.activateGraphicEyes)
        {
            bRestart = graphicEyes(bRestart);          
            break;
        }
        else{
            state++;
        }

    case 10: 
        if(configManager.data.activateGraphicBounceBall)
        {
            bRestart = graphicBounceBall(bRestart);    
            break;
        }
        else{
            state++;
        }

    case 11: 
        if(configManager.data.activateGraphicArrowScroll)
        {
            bRestart = graphicArrowScroll(bRestart);   
            break;
        }
        else{
            state++;
        }

    case 12: 
        if(configManager.data.activateGraphicScroller)
        {
            bRestart = graphicScroller(bRestart);      
            break;
        }
        else{
            state++;
        }

    case 13: 
        if(configManager.data.activateGraphicWiper)
        {
            bRestart = graphicWiper(bRestart);         
            break;
        }
        else{
            state++;
        }

    case 14: 
        if(configManager.data.activateGraphicInvader)
        {
            bRestart = graphicInvader(bRestart);       
            break;
        }
        else{
            state++;
        }

    case 15: 
        if(configManager.data.activateGraphicPacman)
        {
            bRestart = graphicPacman(bRestart);        
            break;
        }
        else{
            state++;
        }

    case 16: 
        if(configManager.data.activateGraphicArrowRotate)
        {
            bRestart = graphicArrowRotate(bRestart);   
            break;
        }
        else{
            state++;
        }

    case 17: 
        if(configManager.data.activateGraphicSpectrum2)
        {
            bRestart = graphicSpectrum2(bRestart);     
            break;
        }
        else{
            state++;
        }

    case 18: 
        if(configManager.data.activateGraphicSinewave)
        {
            bRestart = graphicSinewave(bRestart);      
            break;
        }
        else{
            state++;
        }


    default: state = 0;
  }
}
