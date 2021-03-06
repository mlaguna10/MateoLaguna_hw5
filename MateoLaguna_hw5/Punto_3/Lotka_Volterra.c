#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.1415
#define N 96
#define sigma 0.05

float numeroAleatorio();
float probability(float *y_obs, float *y_model);
float * solucionarEcuacion(float * t, float x, float y, float a, float b, float c, float d);

int main(int argc, char const *argv[])
{
  int i;

  FILE *in;
  float n1,n2,n3;
  char bas1[200];
  int res;
  float *time_obs;
  float *x_obs;
  time_obs = malloc(1000000);
  x_obs = malloc(100000000);
  int a = 0;

  in = fopen("lotka_volterra_obs.dat", "r");

  for(i=0;i<5;i++){
    res = fscanf(in, "%s \n", &bas1);
  }

  res = fscanf(in, "%f %f %f\n", &n1, &n2, &n3);
  
  while(res == 3 && a < 96)
    {
      time_obs[a] = n1;
      x_obs[a] = n2;
      x_obs[N+a] = n3;
      res = fscanf(in, "%f %f %f\n", &n1, &n2, &n3);
      a+=1;
    }

  float *alphas;
  float *betas; 
  float *deltas; 
  float *gammas;

  alphas = malloc(1000000);
  betas = malloc(1000000);
  deltas = malloc(1000000);
  gammas = malloc(1000000);

  alphas[0]=20;
  betas[0]=4;
  deltas[0]=4;
  gammas[0]=4;

  //soluciona las ecuaciones diferenciales
  
  solucionarEcuacion(time_obs,x_obs[0],x_obs[N+0],alphas[0],betas[0],gammas[0],deltas[0]);

  for(i=0;i<10000;i++)
    {
      float temp1 = alphas[i] + numeroAleatorio();
      float temp2 = betas[i] + numeroAleatorio();
      float temp3 = gammas[i] + numeroAleatorio();
      float temp4 = deltas[i] + numeroAleatorio();

      float probabilidad1 = probability(x_obs,solucionarEcuacion(time_obs,x_obs[0],x_obs[N+0],temp1,temp2,temp3,temp4));
      float probabilidad2 = probability(x_obs,(solucionarEcuacion(time_obs,x_obs[0],x_obs[N+0],alphas[i],betas[i],gammas[i],deltas[i])));
					
      float r = exp((1/5000.0)*(-probabilidad1 + probabilidad2));
	
      if(r>1)
	{
	  alphas[i+1]=temp1;
	  betas[i+1]=temp2;
	  gammas[i+1]=temp3;
	  deltas[i+1]=temp4;
	  printf("%f %f %f %f \n",alphas[i],betas[i],gammas[i],deltas[i]);
	}
      else
	{
	  alphas[i+1]=alphas[i];
	  betas[i+1]=betas[i];
	  gammas[i+1]=gammas[i];
	  deltas[i+1]=deltas[i];
	  printf("%f %f %f %f \n",alphas[i],betas[i],gammas[i],deltas[i]);
 
	}
    }
}

float probability(float *y_obs, float *y_model)
{
  float z = 0;
  int i;
  for(i=0;i<96;i++)
    {
      z+=0.5*pow((y_obs[i]-y_model[i]),2);
    }
  return -z;
}

float * solucionarEcuacion(float *t, float x,float y, float a, float b, float c, float d)
{
  float *x_arreglo;
  x_arreglo = malloc(1000000);
  
  int i;
  x_arreglo[0]= x;
  x_arreglo[N]= y;
  for(i=1; i < 96; i++)
    {
      x_arreglo[i] = x_arreglo[i-1] + (t[i+1]-t[i])*(x_arreglo[i-1]*(a - b*x_arreglo[N+i-1]));
      x_arreglo[N+i] = x_arreglo[N+i-1] + (t[i+1]-t[i])*(-x_arreglo[N+i-1]*(c - d*x_arreglo[i-1]));
    }
  
  return x_arreglo;
}

float numeroAleatorio()
{
  float phi = drand48()*2*pi;
  float gamma=-log(drand48());
  float r = sigma*sqrt(2*gamma);
  float x = r*cos(phi);
  return x;
}


