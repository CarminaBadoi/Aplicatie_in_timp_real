static int panelHandle,panel_PID;
static int OldWidth,NewWidth; // latimea panelului  
static int OldHeight,NewHeight; // lungimea panelului  

 
int stare_led,mod_regim,stare_pushbutton_led; 
int selectare_referinta;
int activare_Compensare,activare_Perturbatie,activare_Compensare2,activare_Perturbatie2;
double comutare_sin;
double referinta0,referinta=0,referinta_1,referinta_2; 
double Te; // perioada de esantionare
double tk;        // esantionul luat la momentul prezent
double tk_1;     // esantionul luat la momentul anterior
double tk_rampa;
double tk_sinusoida; 
double pi;   // variabila pi
double A;   // amplitudine
double T;  // perioada 
double b;   // pozitia pe ordonata

//------------------- f.d.t parte fixa in matlab ---------------------
double tk_2,yk_mat,yk_mat_1,yk_mat_2,uk_1,uk_2;

// ------------- F.D.T PARTE FIXA ---------------------
 
double yk ;     // functia de transfer = (5s+1) / (7s+1) la momentul prezent
double yk_1;   // functia de transfer = (5s+1) / (7s+1) la momentul anterior 
double yk1_1; // functia de transfer =  1/ (2s+1) la momentul anterior 
double yk1;  // functia de transfer =  1/ (2s+1) la momentul prezent
double uk;  // semnalul de intrare la momentul prezent
double uk_1;// semnalul de intrare la momentul anterior 
double C00,C0,C1,C2,C3,C4,C5; // variabile pentru rescrierea functiilor 
   

// ------------- F.D.T PROCES AFECTAT DE PERTURBATIA 1 ---------------------
 
double yk_perturbata ;     // functia de transfer perturbata = (6s+1) / (8s+1) la momentul prezent
double yk_perturbata_1;   // functia de transfer = (8s+1) / (8s+1) la momentul anterior 
double yk1_perturbata_1; // functia de transfer =  1/ (4s+1) la momentul anterior 
double yk1_perturbata;  // functia de transfer =  1/ (4s+1) la momentul prezent
double yk2_perturbata,yk2_perturbata_1;// functia de transfer =  1/ (0.2s+1) la momentul prezent si anterior
double C1_perturbat,C2_perturbat,C3_perturbat,C4_perturbat; // variabile pentru rescrierea functiilor perturbate

// --------------------- F.D.T PROCES AFECTAT DE PERTURBATIA 2 ------------
double yk_perturbata2, yk_perturbata2_1;
double yk1_perturbata2, yk1_perturbata2_1;
double yk2_perturbata2, yk2_perturbata2_1;
double C11_perturbat,C22_perturbat,C33_perturbat,C44_perturbat; // variabile pentru rescrierea functiilor perturbate


// --------------------------COMPENSATOR PERTURBATIE 1 --------------------------- 
double yk_comp1,yk_comp1_1,yk_comp2,yk_comp2_1,yk_comp3,yk_comp3_1;
double C1_comp,C2_comp,C3_comp,C4_comp,C5_comp,C6_comp;

// --------------------------COMPENSATOR PERTURBATIE 2 --------------------------- 
double yk2_comp1,yk2_comp1_1,yk2_comp2,yk2_comp2_1,yk2_comp3,yk2_comp3_1,yk2_comp4,yk2_comp4_1;
double C11_comp,C22_comp,C33_comp,C44_comp,C55_comp,C66_comp,C77_comp, C88_comp;
 

//---------------comanda ------------------
double yk_comanda_1,yk_comanda; // comanda la momentul de esantionare prezent si anterior

//----------- elementul de executie ----------
double yk_elem_ex,yk_elem_ex_1 ; // elem de execla momentul de esantionare prezent si anterior
 

// -----------traductor proces---------------
double  yk_traductor,yk_traductor_1; //traductor la momentul de esantionare prezent si anterior

// -----------traductor proces afectat de perturbatia 1 ---------------
double  yk_traductor_pert,yk_traductor_pert_1; // iesire traductor cu perturbatie
double C1_trad_perturbatie,C2_trad_perturbatie;

// -----------traductor proces afectat de perturbatia 2 ---------------
double  yk_traductor2_pert,yk_traductor2_pert_1; // iesire traductor cu perturbatie
double  C11_trad_perturbatie, C22_trad_perturbatie;

// ------ PID ---------
double PID,PID_1,PID_2; // iesire PID
double Kr,Ti,Td,alpha;
double a1,a2,b0,b1,b2;
double p0,p1,p2;
double q0,q1,q2;

// --------- eroarea -----------
double eroare,eroare_1,eroare_2; // iesire eroare

//--------------perturbatia 1 ------------
double perturbatiek,perturbatiek_1;
double temperaturak,temperaturak_1; // perturbatie 1

//--------------perturbatia 2 ------------
double perturbatie2_k,perturbatie2_k_1;
double temperatura2_k,temperatura2_k_1; // perturbatie 2

// ----------proces --------------
double yk_proces,yk_proces_1; // iesire proces 