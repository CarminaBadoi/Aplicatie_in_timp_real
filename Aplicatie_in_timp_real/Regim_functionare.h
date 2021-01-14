 
//------------------------------- REGIM FUNCTIONARE ------------------------------------//

int regim_functionare(){

//----------------------PRELUCRARE LEDURI -----------------
			
			// CITIM REGIMUL DE FUNCTIONARE : AUTOMAT SAU MANUAL
				GetCtrlVal(panelHandle,PANEL_BINARYSWITCH,&mod_regim);
				
				if(mod_regim ){  // AUTOMAT
					
					//DEZACTIVAM ANUMITE BUTOANE
					SetCtrlAttribute(panelHandle,PANEL_TOGGLEBUTTON,ATTR_DIMMED,1);
					 
					// CITIM STAREA LED-URILOR : ON SAU OFF
					GetCtrlVal(panelHandle,PANEL_LED,&stare_led);
					GetCtrlVal(panelHandle,PANEL_LED_2,&stare_led);
					GetCtrlVal(panelHandle,PANEL_LED_3,&stare_led);
					
				
					// SCHIMBAM STAREA LOR ACTUALA IN FUNCTIE DE CEA ANTERIOARA : DACA AU FOST ON LE FACEM OFF SI INVERS
					
					if(stare_led == 0){
						SetCtrlVal(panelHandle,PANEL_LED,1);
						SetCtrlVal(panelHandle,PANEL_LED_2,1);
						SetCtrlVal(panelHandle,PANEL_LED_3,1);
					}
					else {
						SetCtrlVal(panelHandle,PANEL_LED,0);
						SetCtrlVal(panelHandle,PANEL_LED_2,0);
						SetCtrlVal(panelHandle,PANEL_LED_3,0);
					}
					
				}
				
				else {  // MANUAL
					
					//ACTIVAM ANUMITE BUTOANE
					SetCtrlAttribute(panelHandle,PANEL_TOGGLEBUTTON,ATTR_DIMMED,0);
					// CITIM STAREA PUSHBUTTONULUI PT LED
					GetCtrlVal(panelHandle,PANEL_TOGGLEBUTTON,&stare_pushbutton_led);
					// LED-URILE DEVIN ON SAU OFF IN FUNCTIE DE STAREA PUSHBUTTONULUI
					SetCtrlVal(panelHandle,PANEL_LED,stare_pushbutton_led);
					SetCtrlVal(panelHandle,PANEL_LED_2,stare_pushbutton_led);
					SetCtrlVal(panelHandle,PANEL_LED_3,stare_pushbutton_led);
				}
				





return 0;



}