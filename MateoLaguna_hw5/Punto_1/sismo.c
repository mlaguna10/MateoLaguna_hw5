#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.674E-11
#define pi 3.141592

float numeroAleatorio();
float probability(float *y_obs, float *y_model);
float * modelo(float *x_obs,float m, float b);

//ESTE MODELO AUN NO ESTA ACOPLADO PARA EL SISMO SIGUE TENIENDO LA IDEA DE LOS PLANETAS, SE DEBE MODIFICAR. NO OLVIDAR.
int main()
{
  float *x_obs;
  x_obs = malloc(100000);
  float *y_obs;
  y_obs = malloc(100000);

  //FALTA MODIFICAR ALGUNAS COSAS, NO OLVIDAR.
  float *m_walk;
  m_walk = malloc(100000);
  float *b_walk;
  b_walk = malloc(100000);

  m_walk[0]=0;
  b_walk[0]=0;

  int i;
  for(i=0;i<100;i++)
    {
      float temp1 = m_walk[i] + numeroAleatorio();
      float temp2 = b_walk[i] + numeroAleatorio();

      float probabilidad1 = probability(x_obs,modelo(x_obs,temp1,temp2));
      float probabilidad2 = probability(x_obs,modelo(x_obs,m_walk[i],b_walk[i]));
      float r = exp((1/5000.0)*(-probabilidad1 + probabilidad2));

      if(r>1)
	{
	  
	  m_walk[i+1]=temp1;
	  b_walk[i+1]=temp2;
	  printf("%f %f \n",-m_walk[i] + 1,log(exp(b_walk[i])/G));
	}
      else
	{
	  m_walk[i+1]=m_walk[i];
	  b_walk[i+1]=b_walk[i];
	  printf("%f %f \n",-m_walk[i] + 1,log(exp(b_walk[i])/G));
	}
    }
  
  return 0;
}

float numeroAleatorio()
{
  float sigma = 0.1;
  float phi = drand48()*2*pi;
  float gamma=-log(drand48());
  float r = sigma*sqrt(2*gamma);
  float x = r*cos(phi);
  return x;
}

float probability(float *y_obs, float *y_model)
{
  float z = 0;
  int i;
  for(i=0;i<8;i++)
    {
      z+=0.5*pow((y_obs[i]-y_model[i]),2);
    }
  return -z;
}

float * modelo(float *x_obs,float m,float b)
{
  float *x_modelo;
  x_modelo = malloc(100000);
  
  int i;
  for(i=0;i<8;i++)
    {
      x_modelo[i] = x_obs[i]*m + b;
    }

  return x_modelo;
}



      
