/************************************************************************/  
/*UDF for 3D Morphing Wing with Seamless Side-edge Transition.
     
    		Chawki Abdessemed, UWE Bristol          
 
 			     Up/lower  = name shown in Fluent GUI 
                             dt  = thread 
                           time  = current time 
                          dtime  = time step 

                                                                     ***/  
/***********************************************************************/  
#include "udf.h"  
  
  
#define Thick       0.12        /*Airfoil thickness 12/100 in NACA 0012 */  
#define FTT         0.20001     /*Time in s when the morphing starts*/  
#define chord       0.2286      /*Airfoil chord (m)*/  
  
  
DEFINE_GRID_MOTION(Up, domain, dt, time, dtime)  
{  
  Thread *tf = DT_THREAD (dt);  
  face_t f;  
  Node *node_p;  
  real  x, y,z,thickness,camber,theta,yupper,dy_c,xupper,W_t,T_max,Tmorph,freq,W_te,x_s,h,l,ltrans_start,ltrans_end,rtrans_start,rtrans_end;  
  int n;  
    freq    =   6;                  /*Morphing frequency*/    
    Tmorph= 1/(4*freq);             /*Time in s needed for the morphing*/     
    T_max = FTT+Tmorph;             /*Flow time in s when the morphing stops*/  
    W_te= 0.05*chord;               /*Maximum flap deflection */  
    x_s = 0.75*chord;               /*location where the morphing starts */  
    h   =   -0.025*chord;           /*h the half-amplitude of the TEF deflection*/  
    l   = 0.05*chord;               /*l the seamless transition size*/  
    ltrans_start    = 0.3*chord;    /*left transition start*/  
    ltrans_end      = 0.35*chord;       /*left transition end*/  
    rtrans_start    = 0.65*chord;   /*Right transition start*/  
    rtrans_end      = 0.7*chord;        /*Right transition end*/  
      
/* Set/activate the deforming flag on adjacent cell zone, which      */  
/* means that the cells adjacent to the deforming wall will also be  */  
/* deformed, in order to avoid skewness.   */  
  
  SET_DEFORMING_THREAD_FLAG (THREAD_T0 (tf));  
  
/* Loop over the deforming boundary zone's faces;                    */  
/* inner loop loops over all nodes of a given face;                  */  
/* Thus, since one node can belong to several faces, one must guard  */  
/* against operating on a given node more than once:                 */  
  
  begin_f_loop (f, tf)  
    {  
      f_node_loop (f, tf, n)  
        {  
          node_p = F_NODE (f, tf, n);  
  
          /* Update the current node only if it has not been         */  
          /* previously visited:                                     */  
           
  
          if (NODE_POS_NEED_UPDATE (node_p))  
            {  
              /* Set flag to indicate that the current node's        */  
              /* position has been updated, so that it will not be   */  
              /* updated during a future pass through the loop:      */  
              NODE_POS_UPDATED (node_p);  
                
            x     = NODE_X (node_p);  
            z     = NODE_Z (node_p);  
  
            /*definition of transition function*/  
  
            W_t = (h*cos(M_PI*z/l)-h) ;       
  
            /*Airfoil thickness distribution for NACA0012*/  
              
        thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));   
            /*Loop over the morphing portion*/  
              
          if ( x > x_s) {  
          if (z>ltrans_start || z< rtrans_end){   
            /*Define  motion before T_MAX*/  
  
            if ( CURRENT_TIME >= FTT && CURRENT_TIME <= T_max) {   
            /*transition modeling*/  
                    if ( z > ltrans_start && z < ltrans_end) {  
                              
                            camber =-(W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
                    }  
                      
                    if ((z > rtrans_start) && z < rtrans_end){  
                            camber =-(W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;    
                    }  
            /*morphing flap*/  
                    if (z >= ltrans_end && z <= rtrans_start) {     
           
                            camber =-(W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
                          
                        }  
              
            }  
            /* when morphing stops*/      
             if ( CURRENT_TIME > T_max) {  
                    if (z > ltrans_start  && z < ltrans_end) {  
      
                            camber =-(W_t*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                                                              
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
                        }  
                    if (z > rtrans_start && z < rtrans_end){  
                            camber =-(W_t*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                                                              
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;    
                    }  
                    if (z >= ltrans_end && z <= rtrans_start) {     
           
                            camber =-(W_te*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                                                              
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
  
              
                        }  
                      
                  }  
                  }  
        }  
            }  
          end_f_loop (f, tf);  
          }  
  
        }  
        }  
  
DEFINE_GRID_MOTION(Down, domain, dt, time, dtime)  
{  
  Thread *tf = DT_THREAD (dt);  
  face_t f;  
  Node *node_p;  
  real  x, y,z,thickness,camber,theta,yupper,dy_c,xupper,W_t,T_max,Tmorph,freq,W_te,x_s,h,l,ltrans_start,ltrans_end,rtrans_start,rtrans_end;  
  int n;  
    
    freq    =   6;                  /*Morphing frequency*/    
    Tmorph= 1/(4*freq);             /*Time in s needed for the morphing*/     
    T_max = FTT+Tmorph;             /*Flow time in s when the morphing stops*/  
    W_te= 0.05*chord;               /*Maximum flap deflection */  
    x_s = 0.75*chord;               /*location where the morphing starts */  
    h   =   -0.025*chord;           /*h the half-amplitude of the TEF deflection*/  
    l   = 0.05*chord;               /*l the seamless transition size*/  
    ltrans_start    = 0.3*chord;    /*left transition start*/  
    ltrans_end  = 0.35*chord;       /*left transition end*/  
    rtrans_start    = 0.65*chord;   /*Right transition start*/  
    rtrans_end  = 0.7*chord;        /*Right transition end*/  
      
      
/* Set/activate the deforming flag on adjacent cell zone, which      */  
/* means that the cells adjacent to the deforming wall will also be  */  
/* deformed, in order to avoid skewness.                             */  
  SET_DEFORMING_THREAD_FLAG (THREAD_T0 (tf));  
  
    
/* Loop over the deforming boundary zone's faces;                    */  
/* inner loop loops over all nodes of a given face;                  */  
/* Thus, since one node can belong to several faces, one must guard  */  
/* against operating on a given node more than once:                 */  
  
  begin_f_loop (f, tf)  
    {  
      f_node_loop (f, tf, n)  
        {  
          node_p = F_NODE (f, tf, n);  
  
          /* Update the current node only if it has not been         */  
          /* previously visited:     
          */  
           
          if (NODE_POS_NEED_UPDATE (node_p))  
            {  
              /* Set flag to indicate that the current node's        */  
              /* position has been updated, so that it will not be   */  
              /* updated during a future pass through the loop:      */  
              NODE_POS_UPDATED (node_p);  
                
              x     = NODE_X (node_p);  
              z     = NODE_Z (node_p);  
            /*definition of transition function*/  
  
            W_t = (h*cos(M_PI*z/l)-h) ;        
  
            /*Airfoil thickness distribution */  
        thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));   
          
        if ( x > x_s) {  
        if (z>ltrans_start || z< rtrans_end){   
            if ( CURRENT_TIME>=FTT && CURRENT_TIME <= T_max) {   
  
                    if ( z > ltrans_start && z < ltrans_end) {  
      
                              
                            camber =-(W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                  
                            xlower = x + thickness*sin(theta);  
                      
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;  
                        }  
                  
              
                    if (z > rtrans_start && z < rtrans_end){  
                          
                            camber =-(W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                  
                            xlower = x + thickness*sin(theta);  
                      
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;                         
                    }     
                    if (z >= ltrans_end && z <= rtrans_start) {  
                          
                            camber =-(W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                                              
                            xlower = x + thickness*sin(theta);  
                      
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;     
                    }  
  
      
                /*stops*/         
                  
            }  
             if ( CURRENT_TIME >= T_max) {  
                   
                if (z > ltrans_start && z < ltrans_end) {  
      
                            camber =-(W_t*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                  
                            xlower = x + thickness*sin(theta);  
  
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;  
                        }  
                          
                if (z > rtrans_start && z < rtrans_end){  
                      
                            camber =-(W_t*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_t*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                  
                            xlower = x + thickness*sin(theta);  
  
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;                     
                }         
  
                    if (z >= ltrans_end && z <= rtrans_start) {     
           
                            camber =-(W_te*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                  
                            xlower = x + thickness*sin(theta);  
  
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;  
                        }  
                      
                  }  
                  }  
        }  
            }  
          end_f_loop (f, tf);  
          }  
  
        }  
        }  
  
/*********************************************************************/  
/*                                                                   */  
/*                      End of the UDF.                              */  
/*                                                                   */  
/*********************************************************************/  
