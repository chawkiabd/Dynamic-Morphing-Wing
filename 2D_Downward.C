/*********************************************************************/  
/* UDF for  2D Downward Dynamic Morphing Flap.

Chawki Abdessemed, UWE Bristol

Up/Down  = name shown in Fluent GUI
 
                                                                     */  
/*********************************************************************/  
#include "udf.h"  
  
#define Thick       0.12        /*Airfoil thickness 12/100 in NACA 0012 */  
#define FTT         0.20001     /*Time in s when the moprhing starts*/  
#define chord       0.2286      /*Airfoil chord*/  
  
  
DEFINE_GRID_MOTION(Up, domain, dt, time, dtime)  
{  
  Thread *tf = DT_THREAD (dt);  
  face_t f;  
  Node *node_p;  
  real  x, y,z,thickness,camber,theta,yupper,dy_c,x_s,xupper,W_te,T_max,Tmorph,freq;  
  int n;  
    freq    =   6;                  /*Morphing frequency*/    
    Tmorph= 1/(4*freq);             /*Time in s needed for the morphing*/     
    T_max = FTT+Tmorph;             /*Flow time in s when the morphing stops*/  
    W_te= 0.05*chord;               /*Maximum flap deflection */  
    x_s = 0.75*chord;               /*location where the morphing starts */  
    
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
  
              
            /*Airfoil thickness distribution */  
              
        thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));   
          
            /*Loop over the morphing portion*/  
        if ( x > x_s) {  
              
            /*define  motion before T_MAX*/  
  
            if ( CURRENT_TIME >= FTT && CURRENT_TIME <= T_max) {   
              
                  
            /*morphing flap*/  
                          
           
                            camber =-(W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
                          
              
            }  
            /*morphing stops*/    
             if ( CURRENT_TIME > T_max) {  
                      
      
                            camber =-(W_te*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
                                                              
                            xupper = x - thickness*sin(theta);  
          
                            yupper =camber + thickness*cos(theta);  
  
                            NODE_Y (node_p) = yupper ;  
  
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
  real  x, y,z,thickness,camber,theta,yupper,dy_c,x_s,xupper,W_te,T_max,Tmorph,freq;  
  int n;  
    freq    =   6;                  /*Morphing frequency*/    
    Tmorph= 1/(4*freq);             /*Time in s needed for the morphing*/     
    T_max = FTT+Tmorph;             /*Flow time in s when the morphing stops*/  
    W_te= 0.05*chord;               /*Maximum flap deflection */  
    x_s = 0.75*chord;               /*location where the morphing starts */  
      
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
      
  
            /*Airfoil thickness distribution */  
        thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));   
          
        if ( x > x_s) {  
            if ( CURRENT_TIME>=FTT && CURRENT_TIME <= T_max) {   
  
      
                            camber =-(W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            slope = sin(theta);  
                  
                            xlower = x + thickness*slope;  
                      
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;  
                         
                          
            }  
             if ( CURRENT_TIME >= T_max) {  
  
      
                        camber =-(W_te*sin(2*M_PI*Tmorph*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                            dy_c= (-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
                            theta = atan(((-3*W_te*sin(2*M_PI*Tmorph*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                            slope = sin(theta);  
                  
                            xlower = x + thickness*slope;  
  
                            lower= camber - thickness*cos(theta);  
  
                            NODE_Y (node_p) = lower ;  
                      
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
