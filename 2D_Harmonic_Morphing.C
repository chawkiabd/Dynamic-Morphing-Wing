/*********************************************************************/  
/* UDF for 2D Harmonic Morphing Trailing-Edge Flap.
     
    		Chawki Abdessemed, UWE Bristol          
 
       morphing_upper/lower  = name shown in Fluent GUI 
                             dt  = thread 
                           time  = current time 
                          dtime  = time step 
                                                                     */  
/*********************************************************************/  
#include "udf.h"  
  
#define T_max   1                   /*Flow time in s when the morphing stops*/  
/*#define   x_morph     0.75        /*location where the morphing starts */  
#define W_te    0.001*0.2286        /*Maximum flap deflection */
#define x_s     0.75*0.2286         /*location where the morphing starts */  
#define Thick   0.12                /*Airfoil thickness 12/100 in NACA 0012 */ 
#define freq    1600                /*Morphing frequency*/  
#define FTT     0.8005              /*Time in s when the moprhing starts*/ 
#define chord   0.2286              /*Airfoil chord*/ 
  
  
DEFINE_GRID_MOTION(morphing_upper, domain, dt, time, dtime)  
{  
  Thread *tf = DT_THREAD (dt);  
  face_t f;  
  Node *node_p;  
  real  x, y, thickness,camber,theta,yupper,dy_c,slope,xupper;  
  int n;  
    
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
          /* previously visited:                                     */  
          if (NODE_POS_NEED_UPDATE (node_p))  
            {  
              /* Set flag to indicate that the current node's        */  
              /* position has been updated, so that it will not be   */  
              /* updated during a future pass through the loop:      */  
              NODE_POS_UPDATED (node_p);  
                
              x     = NODE_X (node_p);  

            thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));  
              
          
        if ( CURRENT_TIME>FTT) {   
            if( x>=x_s) {  
                  
  
                camber =-(W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq)*pow((x-x_s),2))/(pow((chord-x_s),3));  
  
  
                theta = atan(((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3))));  
  
                  
                  
                xupper = x - thickness*sin(theta);  
          
  
                yupper =camber + thickness*cos(theta);  

                    NODE_Y (node_p) = yupper ;  
            }  
            }  
        }  
      
          }    
      
  end_f_loop (f, tf);  
  }  
  
}  
  
DEFINE_GRID_MOTION(morphing_lower, domain, dt, time, dtime)  
{  
  Thread *tf = DT_THREAD (dt);  
  face_t f;  
  Node *node_p;  
  real  x, y, thickness,camber,theta,lower,dy_c,xlower,slope;  
  int n;  
    
/* Set/activate the deforming flag on adjacent cell zone, which      */  
/* means that the cells adjacent to the deforming wall will also be  */  
/* deformed, in order to avoid skewness.                             */  
  SET_DEFORMING_THREAD_FLAG (THREAD_T0 (tf));  
  
/* Compute the angles:                                               */  
  
    
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
  
            thickness= (chord*Thick / 0.2) * (0.2969*sqrt(x/chord)-0.1260*x/chord-0.3516*pow((x/chord),2) + 0.2843*pow((x/chord),3)-0.1036*pow((x/chord),4));  
  
if ( CURRENT_TIME>FTT) {  
  
            if(x >=x_s){  
                  
  
                camber =-(W_te*sin(2*M_PI*((CURRENT_TIME-FTT)*freq))*pow((x-x_s),3))/(pow((chord-x_s),3));  
  
                dy_c= (-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3));  
  
  
                theta = atan((-3*W_te*sin(2*M_PI*(CURRENT_TIME-FTT)*freq))*pow((x-x_s),2)/(pow((chord-x_s),3)));  
  
                slope = sin(theta);  
                  
                xlower = x + thickness*slope;  
                      
  
                lower= camber -thickness*cos(theta);  
  
                  
  
                    NODE_Y (node_p) = lower ;  
            }  
          }  
        }  
          }  
          }  
   
  end_f_loop (f, tf);  
    
}  
  
  
  
/*********************************************************************/  
/*                                                                   */  
/*  End of the UDF.                                                  */
/*                                                                   */  
/*********************************************************************/  
