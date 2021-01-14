 
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Aplicatie_in_timp_real.h"
 

#include "Declarare_Variabile.h"
#include "Functii_utilitare.h"
#include "Generare_semnal.h"
#include "Initilializare_Aplicatie.h"
#include "Regim_functionare.h"
#include "Seteaza_Perioada_Esantionare.h"
#include "Seteaza_PID.h"

 

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Aplicatie_in_timp_real.uir", PANEL)) < 0)
		return -1;
	if ((panel_PID = LoadPanel (panelHandle, "Aplicatie_in_timp_real.uir", PANEL_2)) < 0)
		return -1;
	
	GetPanelAttribute(panelHandle,ATTR_WIDTH,&OldWidth); 
	GetPanelAttribute(panelHandle,ATTR_HEIGHT,&OldHeight); 
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}


 //-------------------------  ESANTIONARE ------------------------------------

int CVICALLBACK esantionare (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			 regim_functionare(); // apelare functiei care prelucreaza regimul de functionare		
				
				//------------------- SELECTARE INTRARE ------------------------
				
				 referinta=generare_semnal();
				  
				 
				//---------------------ELEMENTUL DE COMPARATIE ------------------
				
				eroare = referinta -  yk_traductor_1; 
				
				//---------------- TRADUCTORUL PROCES PERTURBAT ------------------
				
					// Citim perturbatia 1
					GetCtrlVal (panelHandle, PANEL_NUMERIC_6, &temperaturak);
					// Citim perturbatia 2
					GetCtrlVal (panelHandle, PANEL_NUMERIC_7, &temperatura2_k);
					//Calculam perturbatia 1
					perturbatiek=yk_traductor_1-temperaturak;
					//Calculam perturbatia 2
					perturbatie2_k=yk_traductor_1-temperatura2_k;
					
					if(perturbatiek>20)
			 		perturbatiek=20;  //[-10..10]%c
					if(perturbatiek<-20)
					perturbatiek=-20; 
					
					if(perturbatie2_k>20)
			 		perturbatie2_k=20;  //[-10..10]%c
					if(perturbatie2_k<-20)
					perturbatie2_k=-20; 
					
					//-------------------TRADUCTOR PERTURBATIE 1 -----------------------
					yk_traductor_pert = yk_traductor_pert_1 + C1_trad_perturbatie*(perturbatiek - yk_traductor_pert_1);  
					
					//-------------------TRADUCTOR PERTURBATIE 2 -----------------------
					yk_traductor2_pert = yk_traductor2_pert_1 + C11_trad_perturbatie*(perturbatie2_k - yk_traductor2_pert_1);
				
				//---------------------- PID ------------------------------------
				PID = -a1*PID_1 - a2*PID_2 + b0*eroare + b1*eroare_1 + b2*eroare_2;
								
				 		 			
					
				// ----------------- FUNCTIE DE TRANSFER  COMPENSATOR 1 --------------
				yk_comp1 = yk_comp1_1 + C1_comp*(yk_traductor_pert - yk_comp1_1) + C2_comp*(yk_traductor_pert - yk_traductor_pert_1);
				yk_comp2 = yk_comp2_1 + C3_comp*(yk_comp1 - yk_comp2_1) + C4_comp*(yk_comp1 - yk_comp1_1);
				yk_comp3 = yk_comp3_1 + C5_comp*(yk_comp2 - yk_comp3_1) + C6_comp*(yk_comp2 - yk_comp2_1);
				
				
				if(!activare_Compensare){
					yk_comp3=0;
				}
				
				// ----------------- FUNCTIE DE TRANSFER  COMPENSATOR 2 --------------
				yk2_comp1 = yk2_comp1_1 + C11_comp*(yk_traductor2_pert - yk2_comp1_1) + C22_comp*(yk_traductor2_pert - yk_traductor2_pert_1);
				yk2_comp2 = yk2_comp2_1 + C33_comp*(yk2_comp1 - yk2_comp2_1) + C44_comp*(yk2_comp1 - yk2_comp1_1);
				yk2_comp3 = yk2_comp3_1 + C55_comp*(yk2_comp2 - yk2_comp3_1) + C66_comp*(yk2_comp2 - yk2_comp2_1);
				yk2_comp4 = yk2_comp4_1 + C77_comp*(yk2_comp3 - yk2_comp4_1) + C88_comp*(yk2_comp3 - yk2_comp3_1);
				
				if(!activare_Compensare2){
					yk2_comp4=0;
				}
							
				
								
				// ----------------------- ELEMENTUL DE EXECUTIE --------------------
				yk_comanda = PID + yk_comp3 + yk2_comp4;  
				yk_elem_ex = yk_elem_ex_1+ C00*(yk_comanda - yk_elem_ex_1) + C0*(yk_comanda - yk_comanda_1 );
				
			/*	if(yk_elem_ex>100)
			 				yk_elem_ex=100;  //[0..100]%c
				if(yk_elem_ex<0)
							yk_elem_ex=0; */
				
				
				// ------------------------ FUNCTIA DE TRANSFER  PROCES -----------------------
				yk = yk_1 + C1*(yk_elem_ex- yk_1) + C2*(yk_elem_ex - yk_elem_ex_1);
				yk1 = yk1_1 + C3*(yk - yk1_1);
				
				 		
								
				//------------------ FUNCTIE DE TRANSFER AFECTATA DE PERTURBATIA 1 ---------------------
				yk_perturbata = yk_perturbata_1 + C1_perturbat*(perturbatiek - yk_perturbata_1) + C2_perturbat*(perturbatiek - perturbatiek_1);
				yk1_perturbata = yk1_perturbata_1 + C3_perturbat*(yk_perturbata - yk1_perturbata_1);
				yk2_perturbata = yk2_perturbata_1 + C4_perturbat*(yk1_perturbata - yk2_perturbata_1);
				if(!activare_Perturbatie ){
					yk2_perturbata=0;
				}	
				
				//------------------ FUNCTIE DE TRANSFER AFECTATA DE PERTURBATIA 2 ---------------------
				yk_perturbata2 = yk_perturbata2_1 + C11_perturbat*(perturbatie2_k - yk_perturbata2_1) + C22_perturbat*(perturbatie2_k - perturbatie2_k_1);
				yk1_perturbata2 = yk1_perturbata2_1 + C33_perturbat*(yk_perturbata2 - yk1_perturbata2_1);
				yk2_perturbata2 = yk2_perturbata2_1 + C44_perturbat*(yk1_perturbata2 - yk2_perturbata2_1);
				if(!activare_Perturbatie2){
					yk2_perturbata2=0;
				}	
						
									
				
				// --------IESIREA PROCESULUI --------------------
				yk_proces = yk1 - yk2_perturbata - yk2_perturbata2;
				
				// --------TRADUCTOR PROCES NEPERTURBAT ----------
				yk_traductor = yk_traductor_1 + C4*(yk_proces - yk_traductor_1);
				 
								
				//--------- FUNCTIA DE TRANSFER DISCREZITATA IN MATLAB ------------
			    //  yk_mat =   1.937*yk_mat_1- 0.9377*yk_mat_2 + 0.01747*uk + 0.00346* uk_1 - 0.01713* uk_2;
				
				// -------- PLOTARE RASPUNSUL FUNCTIEI DE TRANSFER -----------
				 
				//--------- PLOTARE RASPUNSUL FUNCTIEI DE TRANSFER DISCRETIZATA IN MATLAB ---------------
			    //PlotLine (panelHandle, PANEL_GRAPH, tk_1, yk_mat_1, tk, yk_mat, VAL_RED);
				
				// -------- PLOTARE RASPUNSUL FUNCTIEI DE TRANSFER -----------
				PlotLine (panelHandle, PANEL_GRAPH, tk_1, referinta_1, tk, referinta, VAL_GREEN);
				//PlotLine (panelHandle, PANEL_GRAPH, tk_1, yk1_1, tk, yk1, VAL_RED);
				PlotLine (panelHandle, PANEL_GRAPH, tk_1, yk_traductor_1, tk, yk_traductor, VAL_RED);
				PlotLine (panelHandle, PANEL_GRAPH, tk_1, temperaturak_1, tk, temperaturak, VAL_BLUE);
				PlotLine (panelHandle, PANEL_GRAPH, tk_1, temperatura2_k_1, tk, temperatura2_k, VAL_MAGENTA);
				 
				
				
				//--------------PLOTARE marimi de comanda -----------------------------------
				PlotLine(panelHandle, PANEL_GRAPH_2, tk_1, PID_1, tk, PID, VAL_GREEN);
				PlotLine(panelHandle, PANEL_GRAPH_2, tk_1, yk_comp3_1, tk, yk_comp3, VAL_BLACK);
				PlotLine(panelHandle, PANEL_GRAPH_2, tk_1, yk_comanda_1, tk, yk_comanda, VAL_RED);
				PlotLine(panelHandle, PANEL_GRAPH_2, tk_1, yk_elem_ex_1, tk, yk_elem_ex, VAL_BLUE);
				
				
				//resetare timp
				tk_1=tk;
				tk_2=tk_1;
				tk=tk+Te;
				
								
				//---------------generare esantioane noi-----------------
				
				// REFERINTA
				referinta_2 = referinta_1;
				referinta_1=referinta;
				// EROARE
				eroare_2=eroare_1;
				eroare_1=eroare;
				// PERTURBATIE 1
				perturbatiek_1 = perturbatiek;
				temperaturak_1 = temperaturak;
				// PERTURBATIE 2
				perturbatie2_k_1 = perturbatie2_k;
				temperatura2_k_1 = temperatura2_k;
				// PID 
				PID_2=PID_1;
				PID_1=PID;
				// COMPENSATOR 1
				yk_comp1_1= yk_comp1;
				yk_comp2_1 = yk_comp2;
				yk_comp3_1 = yk_comp3;
				
				// COMPENSATOR 2
				yk2_comp1_1= yk2_comp1;
				yk2_comp2_1 = yk2_comp2;
				yk2_comp3_1 = yk2_comp3;
				yk2_comp4_1 = yk2_comp4;
				
				// COMANDA
				yk_comanda_1 = yk_comanda;
				// ELEM DE EXECUTIE
				yk_elem_ex_1 = yk_elem_ex ; 
				
				// F.D.T PROCES NEPERTURBAT
				yk_1 = yk;
				yk1_1=yk1;
				// F.D.T PROCES PERTURBAT DE PERTURBATIE 1
				yk_perturbata_1 = yk_perturbata;
				yk1_perturbata_1 = yk1_perturbata;
				yk2_perturbata_1 = yk2_perturbata;
				
				// F.D.T PROCES PERTURBAT DE PERTURBATIE 2
				yk_perturbata2_1 = yk_perturbata2;
				yk1_perturbata2_1 = yk1_perturbata2;
				yk2_perturbata2_1 = yk2_perturbata2;
				
				// PROCES
				yk_proces_1= yk_proces;
				
				// TRADUCTOR PROCES NEPERTURBAT
				yk_traductor_1 = yk_traductor;
				
				// TRADUCTOR PROCES AFECTAT DE PERTURBATIA 1
				yk_traductor_pert_1 = yk_traductor_pert;
				
				// TRADUCTOR PROCES AFECTAT DE PERTURBATIA 2
				yk_traductor2_pert_1 = yk_traductor2_pert;
				
				 
				
				
				yk_mat_1=yk_mat;
				yk_mat_2=yk_mat_1;
				
				uk_1=uk;
				
				uk_2=uk_1;
				
				 
				 
									

			break;
	}
	return 0;
}

 






