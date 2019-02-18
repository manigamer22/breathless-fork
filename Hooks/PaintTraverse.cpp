#include "main.h"
#include "../Drawings/menu.h"
#include "../Hacks/crosshair.h"
#include "../Hacks/esp.h"
#include "../Hacks/spectators.h"
#include "../Hacks/antiaiminfos.h"
#include "../Hacks/hitmarker.h"

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    
    if (vars.misc.noscope && !strcmp("HudZoom", pPanel->GetName(panel)))
        return;
    
    paintVMT->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    static VPANEL last = 0;
    
    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
        {
            framefont       = draw->createfont(framefont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);
            espfont         = draw->createfont(espfont, "Arial Bold", 12, FONTFLAG_DROPSHADOW);
            
            mFont           = draw->createfont(mFont, "BigNoodleTitling", 1, FONTFLAG_ANTIALIAS);
            sFont           = draw->createfont(sFont, "BigNoodleTitling", 12, FONTFLAG_ANTIALIAS);     // Used for sliders
            tFont           = draw->createfont(tFont, "BigNoodleTitling", 18, FONTFLAG_ANTIALIAS);     // Used for tabs
            heading         = draw->createfont(heading, "BigNoodleTitling", 21, FONTFLAG_ANTIALIAS);   // Used for headings
            osFont          = draw->createfont(osFont, "osmiummenufont", 30, FONTFLAG_ANTIALIAS);
            cFont           = draw->createfont(cFont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);     // Combos
            titleFont       = draw->createfont(cFont, "BigNoodleTitling", 52, FONTFLAG_ANTIALIAS);     // vlone.cc Title
            subtitleFont    = draw->createfont(cFont, "Verdana", 30, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // vlone.cc Subtitle
            o4Font_03       = draw->createfont(o4Font_03, "04b03", 12, FONTFLAG_ANTIALIAS);
            o4Font_11       = draw->createfont(o4Font_11, "04b11", 12, FONTFLAG_ANTIALIAS);
            o4Font_20       = draw->createfont(o4Font_20, "04b_20", 12, FONTFLAG_ANTIALIAS);
            
            last = panel;
        }
        
        {   // Initialisation
            vars.colors.ctchams     = Color::White();
            vars.colors.ctchams_ign = Color::Red();
            
            vars.colors.tchams      = Color::White();
            vars.colors.tchams_ign  = Color::Red();
            
            vars.colors.tbox        = Color(18, 18, 18, 255);
            vars.colors.tbox_ign    = Color(18, 18, 18, 255);
            
            vars.colors.ctbox       = Color(18, 18, 18, 255);
            vars.colors.ctbox_ign   = Color(18, 18, 18, 255);
            
            vars.colors.hands       = Color(255, 0, 83, 255);
            vars.colors.weapon      = Color(18, 18, 18, 255);
            
            vars.colors.scope       = Color::Red();
            vars.colors.world       = Color::Test();
            vars.colors.sky         = Color::Red();
        }
        
    }
    
    
    if(panel == last)
    {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu();
        
        {   // Drawing features / own scope just for readablity
            
            DrawOtherESP();     // Other ESP
            
            DrawPlayerESP();    // Player esp
            
            DrawScope(local);   // Draws the crosshar for noscope
            
            rCrosshair(local);  // Draws recoil crosshair
            
            manualaa(local);        // Manual AA idicator
            
            Spectatorlist();    // Draws speclist
            
            //aw_hitmarker->initilisze();
        }
        
        if(vars.menu)
        {   // Draw menu items
            menu->renderMenu();
            draw->drawmouse();
            pCvar->FindVar("cl_mouseenable");
        }
        
        //draw->drawstring(10, 15, Color::White(), espfont, "[-zeX Priv]");
        
        
        /* static int Tick = 0;
         Tick++;
         
         if (Tick > 0 && Tick < 30)
         {
         draw->drawstring(10, 15, Color::Red(), espfont, "[-vape.us]");
         }
         else if (Tick > 30 && Tick < 60)
         {
         draw->drawstring(10, 15, Color::Orange(), espfont, "[-vape.us]");
         }
         else if (Tick > 60 && Tick < 90)
         {
         draw->drawstring(10, 15, Color::Yellow(), espfont, "[-vape.us]");
         }
         else if (Tick > 90 && Tick < 120)
         {
         draw->drawstring(10, 15, Color::Green(), espfont, "[-vape.us]");
         }
         else if (Tick > 120 && Tick < 150)
         {
         draw->drawstring(10, 15, Color::LightBlue(), espfont, "[-vape.us]");
         }
         else if (Tick > 150 && Tick < 180)
         {
         draw->drawstring(10, 15, Color::Purple(), espfont, "[-vape.us]");
         }
         else if (Tick > 180 && Tick < 210)
         {
         draw->drawstring(10, 15, Color::Pink(), espfont, "[-vape.us]");
         }
         
         
         // Reset
         if(Tick > 210)
         {
         Tick = 0;
         } */
        
        if(vars.misc.watermark)
        {
            
            static int Tick = 0;
            Tick++;
            
            if (Tick > 0 && Tick < 30)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "");
            }
            else if (Tick > 30 && Tick < 60)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "|");
            }
            else if (Tick > 60 && Tick < 90)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-");
            }
            else if (Tick > 90 && Tick < 120)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-|");
            }
            else if (Tick > 120 && Tick < 150)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-c");
            }
            else if (Tick > 150 && Tick < 180)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-c|");
            }
            else if (Tick > 180 && Tick < 210)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cr");
            }
            else if (Tick > 210 && Tick < 240)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cr|");
            }
            else if (Tick > 240 && Tick < 270)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cre");
            }
            else if (Tick > 270 && Tick < 300)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cre|");
            }
            else if (Tick > 300 && Tick < 330)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cred");
            }
            else if (Tick > 330 && Tick < 360)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cred|");
            }
            else if (Tick > 360 && Tick < 390)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credi");
            }
            else if (Tick > 390 && Tick < 420)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credi|");
            }
            else if (Tick > 420 && Tick < 450)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credit");
            }
            else if (Tick > 450 && Tick < 480)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credit|");
            }
            if (Tick > 480 && Tick < 510)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc");
            }
            else if (Tick > 510 && Tick < 540)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc|");
            }
            if (Tick > 540 && Tick < 570)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0");
            }
            else if (Tick > 570 && Tick < 600)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0|");
            }
            //
            
            if (Tick > 600 && Tick < 630)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-vape.us");
            }
            else if (Tick > 630 && Tick < 660)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-vape.us|");
            }
            else if (Tick > 660 && Tick < 690)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0.d|");
            }
            else if (Tick > 690 && Tick < 720)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0.");
            }
            else if (Tick > 720 && Tick < 750)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0|");
            }
            else if (Tick > 750 && Tick < 780)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc0");
            }
            else if (Tick > 780 && Tick < 810)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc|");
            }
            else if (Tick > 810 && Tick < 840)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-creditc");
            }
            else if (Tick > 840 && Tick < 870)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credit|");
            }
            else if (Tick > 870 && Tick < 900)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credit");
            }
            else if (Tick > 900 && Tick < 930)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credi|");
            }
            else if (Tick > 930 && Tick < 960)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-credi");
            }
            else if (Tick > 960 && Tick < 990)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cred|");
            }
            else if (Tick > 990 && Tick < 1020)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cred");
            }
            else if (Tick > 1020 && Tick < 1050)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cre|");
            }
            else if (Tick > 1050 && Tick < 1080)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cre");
            }
            else if (Tick > 1080 && Tick < 1110)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cr|");
            }
            else if (Tick > 1110 && Tick < 1140)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-cr");
            }
            else if (Tick > 1140 && Tick < 1170)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-c|");
            }
            else if (Tick > 1170 && Tick < 1200)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-c");
            }
            else if (Tick > 1200 && Tick < 1230)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-|");
            }
            else if (Tick > 1270 && Tick < 1300)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "-");
            }
            else if (Tick > 1300 && Tick < 1330)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "");
            }
            else if (Tick > 1330 && Tick < 1360)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "|");
            }
            else if (Tick > 1360 && Tick < 1390)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "");
            }
            else if (Tick > 1390 && Tick < 1420)
            {
                draw->drawstring(10, 15, Color::White(), espfont, "|");
            }
            
            
            // Reset
            if(Tick > 1420)
            {
                Tick = 0;
            }
        }
        
        
        
        
        /*{
         
         static int Tick = 0;
         Tick++;
         
         if (Tick > 0 && Tick < 30)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "");
         }
         else if (Tick > 30 && Tick < 60)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "|");
         }
         else if (Tick > 60 && Tick < 90)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-");
         }
         else if (Tick > 90 && Tick < 120)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-|");
         }
         else if (Tick > 120 && Tick < 150)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-z");
         }
         else if (Tick > 150 && Tick < 180)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-z|");
         }
         else if (Tick > 180 && Tick < 210)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-ze");
         }
         else if (Tick > 210 && Tick < 240)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-ze|");
         }
         else if (Tick > 240 && Tick < 270)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-zeX");
         }
         else if (Tick > 270 && Tick < 300)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-zeX|");
         }
         else if (Tick > 300 && Tick < 330)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-ze|");
         }
         else if (Tick > 330 && Tick < 360)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-ze");
         }
         else if (Tick > 360 && Tick < 390)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-z|");
         }
         else if (Tick > 390 && Tick < 420)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-z");
         }
         else if (Tick > 420 && Tick < 450)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-|");
         }
         else if (Tick > 450 && Tick < 480)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "-");
         }
         if (Tick > 480 && Tick < 510)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "");
         }
         else if (Tick > 510 && Tick < 540)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "|");
         }
         if (Tick > 540 && Tick < 570)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "");
         }
         else if (Tick > 570 && Tick < 600)
         {
         draw->drawstring(10, 15, Color::White(), espfont, "|");
         }
         
         
         // Reset
         if(Tick > 600)
         {
         Tick = 0;
         }
         }*/
        
        
    }
}

