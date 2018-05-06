#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"

double max(double a, double b) {
  return a>b? a: b;
}
double min(double a, double b) {
  return a + b - max(a, b);
}


color get_lighting(double *normal, struct lprops *light) {
  color ambient = calculate_ambient(normal, light);
  color diffuse = calculate_diffuse(normal, light);
  color specular = calculate_specular(normal, light);

  return limit_color(cadd(cadd(ambient, diffuse), specular));
}

color calculate_ambient(double *normal, struct lprops *light) {
  return cscale(cmultiply(light->acolor,
			  light->areflect),
		1.0 / 255);
}

color calculate_diffuse(double *normal, struct lprops *light) {
  return cscale(cmultiply(light->color,
			  light->dreflect),
		(1.0 / 255) *
		max(0,
		    vdot(normal,
			 light->direction)));
}

color calculate_specular(double *normal, struct lprops *light) {
  
  return cscale(cmultiply(light->color, light->sreflect),
		(1.0 / 255) * 
		pow(vdot(vsubtract(vscale(vcopy(normal),
					  2 * vdot(normal,
						   light->direction)),
				   light->direction),
			 light->view),
		    SPECULAR_EXP));
}


double *calculate_normal(struct matrix *polygons, int i) {

  double A[3];
  double B[3];
  double *N = (double *)malloc(3 * sizeof(double));

  A[0] = polygons->m[0][i+1] - polygons->m[0][i];
  A[1] = polygons->m[1][i+1] - polygons->m[1][i];
  A[2] = polygons->m[2][i+1] - polygons->m[2][i];
  
  B[0] = polygons->m[0][i+2] - polygons->m[0][i];
  B[1] = polygons->m[1][i+2] - polygons->m[1][i];
  B[2] = polygons->m[2][i+2] - polygons->m[2][i];

  N[0] = A[1] * B[2] - A[2] * B[1];
  N[1] = A[2] * B[0] - A[0] * B[2];
  N[2] = A[0] * B[1] - A[1] * B[0];
  
  return normalize(N);
}
 
color limit_color(color c) {
  return get_color(min(255, c.red),
		   min(255, c.green),
		   min(255, c.blue));
}

double *normalize(double *v) {
  double norm = sqrt(vdot(v, v));

  v[0] /= norm;
  v[1] /= norm;
  v[2] /= norm;
  
  return v;
}

double vdot(double *v0, double *v1) {
  return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

double *vscale(double *v, double c) {
  v[0] *= c;
  v[1] *= c;
  v[2] *= c;
  
  return v;
}

double *vsubtract(double *v, double *w) {
  v[0] -= w[0];
  v[1] -= w[1];
  v[2] -= w[2];
  
  return v;
}

double *vadd(double *v, double *w) {
  v[0] += w[0];
  v[1] += w[1];
  v[2] += w[2];
  
  return v;
 }

double *vcopy(double *v) {
  double *w = malloc(3 * sizeof(double));

   w[0] = v[0];
   w[1] = v[1];
   w[2] = v[2];

   return w;
}

color cadd(color c1, color c2) {
  return get_color(c1.red + c2.red,
		   c1.green + c2.green,
		   c1.blue + c2.blue);
}
 
color cmultiply(color c1, color c2) {
  return get_color((c1.red * c2.red),
		   (c1.green * c2.green),
		   (c1.blue * c2.blue));
}

color cscale(color c1, double s) {
  return get_color((c1.red * s),
		   (c1.green * s),
		   (c1.blue * s));
}


