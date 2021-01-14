// ------------------------------- SELECTARE SEMNAL -----------------------------------
double generare_semnal()
{  
	 		double local_referinta,local_a, local_b;

			local_referinta = 0;
			
					 switch (selectare_referinta)
				{		
						 					
					case 0:
							
							//ACTIVAM ANUMITE BUTOANE
							SetCtrlAttribute(panelHandle,PANEL_NUMERIC_5,ATTR_VISIBLE,1);
							
							 // DEZACTIVAM ANUMITE BUTOANE
							SetCtrlAttribute(panelHandle,PANEL_NUMERIC,ATTR_VISIBLE,0);
							SetCtrlAttribute(panelHandle,PANEL_NUMERIC_2,ATTR_VISIBLE,0);
							SetCtrlAttribute(panelHandle,PANEL_NUMERIC_3,ATTR_VISIBLE,0);
							
							//GENERAM SEMNALUL TREAPTA
							
							GetCtrlVal(panelHandle,PANEL_NUMERIC_5, &local_referinta);
						 				
						break;
					
					case 1: 
						
						// ACTIVAM ANUMITE BUTOANE
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC,ATTR_VISIBLE,1);
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_2,ATTR_VISIBLE,1);
						
						// DEZACTIVAM ANUMITE BUTOANE
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_3,ATTR_VISIBLE,0);
					
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_5,ATTR_VISIBLE,0);
						
						if (comutare_sin==0){
																	
											// CITIM VALOAREA AMPLITUDINII DE PE INTERFATA GRAFICA
											GetCtrlVal(panelHandle,PANEL_NUMERIC,&A);
											
											// CITIM PERIOADA DE PE INTERFATA GRAFICA
											GetCtrlVal(panelHandle,PANEL_NUMERIC_2,&T);
						}

						
						
						else  {	
								
								if( (referinta_2<referinta0)&&(referinta_1>=referinta0) ) {
																			comutare_sin=0;
																			tk_sinusoida=2*Te;
																		}
								if( (referinta_2>referinta0)&&(referinta_1<=referinta0) ) {
																			comutare_sin=0;
																			tk_sinusoida=(2*Te)+(T/2);
						}											}
																		
							
												
						// GENERARE SEMNAL SINUSOIDAL
						local_referinta = A*sin( ((2*pi)/T)*tk_sinusoida ) + referinta0 ; 
						
						tk_sinusoida=tk_sinusoida+Te;
						
						
						break;
					
					case 2: 
							// CITIM PANTA DE PE INTERFATA GRAFICA
						GetCtrlVal(panelHandle,PANEL_NUMERIC_3,&local_a);
						// pozitia pe ordonata a rampei ia valoarea referintei anterioare
						local_b = referinta0; 
													
						// ACTIVAM ANUMITE BUTOANE
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_3,ATTR_VISIBLE,1);
						
						
						// DEZACTIVAM ANUMITE BUTOANE
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC,ATTR_VISIBLE,0);
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_2,ATTR_VISIBLE,0);
						SetCtrlAttribute(panelHandle,PANEL_NUMERIC_5,ATTR_VISIBLE,0);
						
						//GENERARE SEMANL RAMPA 
						local_referinta = local_a * tk_rampa + local_b;
						tk_rampa= tk_rampa+Te;
					
						break;
				}
				
	return local_referinta;
}



int CVICALLBACK selectie_semnal (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	 
					 
					 switch (event)
				{		
						 					
					case EVENT_COMMIT:
						// citim referinta de pe interfata grafica
						GetCtrlVal(panelHandle,PANEL_RINGSLIDE,&selectare_referinta);   
						
						switch(selectare_referinta)
						
						{ 
							case 0: // treapta 
									 
									 							 					 
								break;
							
							case 1:  // sinusoida
								tk_sinusoida = 0;
								referinta0=referinta; //stocam referinta anterioara intr-o variabila
								break;
							
							case 2: //rampa
								 
								tk_rampa = 0;
								referinta0=referinta; //stocam referinta anterioara intr-o variabila
								break;
						}
						
						break;
				}
						
								
						 
						
	return 0;
}

int CVICALLBACK modificare_panta (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			tk_rampa=0;
			referinta0=referinta;

			break;
	}
	return 0;
}


int CVICALLBACK Comutare_Sinusoida (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			comutare_sin =1;

			break;
	}
	return 0;
}
 