#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.674E-11
#define pi 3.141592

float numeroAleatorio();
float probability(float *y_obs, float *y_model);
float * modelo(float *x_obs,float m, float b);

int main()
{
  float *x_obs;
  x_obs = malloc(100000);
  float *y_obs;
  y_obs = malloc(100000);

  //Posiciones en raiz
  x_obs[0]=log(sqrt(pow(0.324190175,2) + pow(0.090955208,2) + pow(-0.022920510,2)));
  x_obs[1]=log(sqrt(pow(-0.701534590,2) + pow(-0.168809218,2) + pow(0.037947785,2)));
  x_obs[2]=log(sqrt(pow(-0.982564148,2) + pow(-0.191145980,2) + pow(-0.000014724,2)));
  x_obs[3]=log(sqrt(pow(1.104185888,2) + pow(-0.826097003,2) + pow(-0.044595990,2)));
  x_obs[4]=log(sqrt(pow(3.266443877,2) + pow(-3.888055863,2) + pow(-0.057015321,2)));
  x_obs[5]=log(sqrt(pow(-9.218802228,2) + pow(1.788299816,2) + pow(0.335737817,2)));
  x_obs[6]=log(sqrt(pow(19.930781147,2) + pow(-2.555241579,2) + pow(-0.2677110968,2)));
  x_obs[7]=log(sqrt(pow(24.323085642,2) + pow(-17.606227355,2) + pow(-0.197974999,2)));

  //velocidades al cuadrado
  y_obs[0]=log(pow(-4.627851589,2) + pow(10.390063716,2) + pow(1.273504997,2));
  y_obs[1]=log(pow(1.725066954,2) + pow(-7.205747212,2) + pow(-0.198268558,2));
  y_obs[2]=log(pow(1.126784520,2) + pow(-6.187988860,2) + pow(0.000330572,2));
  y_obs[3]=log(pow(3.260215854,2) + pow(4.524583075,2) + pow(0.014760239,2));
  y_obs[4]=log(pow(2.076140727,2) + pow(1.904040630,2) + pow(-0.054374153,2));
  y_obs[5]=log(pow(-0.496457364,2) + pow(-2.005021061,2) + pow(0.054667082,2));
  y_obs[6]=log(pow(0.172224285,2) + pow(1.357933443,2) + pow(0.002836325,2));
  y_obs[7]=log(pow(0.664855006,2) + pow(0.935497207,2) + pow(-0.034716967,2));
  
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
	  //Cuidado: se necesita el exponente alfa no m
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



      
