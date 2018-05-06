#ifndef GMATH_H
#define GMATH_H

#include "matrix.h"
#include "display.h"
#include "ml6.h"

#define SPECULAR_EXP 2

struct lprops {
  double *location; //location of light source
  double *direction; //direction of light source
  double *view; //location of viewer
  
  color color; //color of light source
  color acolor; //color of ambient light
  
  color areflect; //ambient reflection
  color dreflect; //diffuse reflection
  color sreflect; //specular refection
};

double max(double a, double b);
double min(double a, double b);
  
color get_lighting(double *normal, struct lprops *light);
color calculate_ambient (double *normal, struct lprops *light);
color calculate_diffuse (double *normal, struct lprops *light);
color calculate_specular(double *normal, struct lprops *light);

color limit_color(color c);

double *calculate_normal(struct matrix *polygons, int pos);

// vector operations

double *normalize(double *v);
double vdot(double *v0, double *v1);
double *vscale(double *v, double c);
double *vsubtract(double *v, double *w);
double *vadd(double *v, double *w);
double *vcopy(double *v);
color cadd(color, color);
color cmultiply(color, color);
color cscale(color c, double s);

#endif
