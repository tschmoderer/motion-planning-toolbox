#include "interpolator1d.h"

/* CONSTRUCTORS */
Interpolator1D::Interpolator1D() : Interpolator() {
    this->extend_left_method = EXTEND_CONSTANT; 
    this->extend_right_method = EXTEND_CONSTANT;
}

Interpolator1D::Interpolator1D(interpolation_method_t imethod, extend_t exleft, extend_t exright) : Interpolator(imethod,1){
    this->extend_left_method = exleft; 
    this->extend_right_method = exright;   
}

/* DESTRUCTOR */
Interpolator1D::~Interpolator1D() {};

/* ACCESSORS */
void Interpolator1D::set_exleft(extend_t new_exleft) {
    this->extend_left_method = new_exleft;
}

void Interpolator1D::set_exright(extend_t new_exright) {
    this->extend_right_method = new_exright;
}

extend_t Interpolator1D::get_exleft() const {
    return this->extend_left_method;
}

extend_t Interpolator1D::get_exright() const {
    return this->extend_right_method;
}

/* METHODS */
double Interpolator1D::interp1d(Vector * times, Vector * data, double t) const {
    assert(times->get_dim() == data->get_dim());
    
    /*
        Case time t is less than minimal interpolation time
    */
    if (t < (*times)[0]) {
        return this->interp1D_extend_left(times, data , t);
    }

    /*
        Case time t is bigger than maximal interpolation time
    */
    if (t > (*times)[times->get_dim()-1]) {
        return this->interp1D_extend_right(times, data, t);
    }

    /*
        Case time t is equal than minimal interpolation time
    */
    if (t == (*times)[0]) {
        return (*data)[0];
    }

    /*
        Case time t is equal than maximal interpolation time
    */
    if (t == (*times)[times->get_dim()-1]) {
        return (*data)[times->get_dim()-1];
    }

    // At this point we necessarily have $$t \in ] times[0], times[end] [
    // Locate index i such that $$t \in [t_i, t_{i+1} [
    uint16_t idx_inf = 0; // can take values in {0, ..., N-2}
    uint16_t N = times->get_dim();
   
    while (t > (*times)[idx_inf] && idx_inf < N-1) {
        idx_inf++;
    }
    idx_inf = (idx_inf == 0) ? 0 : idx_inf-1;
    
    if (t == (*times)[idx_inf]) {
        return (*data)[idx_inf];
    }

    switch (this->i_method) {   
        case INTERP_CONSTANT_LEFT:
            return this->interp1d_constant_left(times, data, t, idx_inf);
            break;

        case INTERP_CONSTANT_RIGHT:
            return this->interp1d_constant_right(times, data, t, idx_inf);
            break;

        case INTERP_NEAREST:
            return this->interp1d_nearest(times, data, t, idx_inf);
            break;    
        
        default: // default is linear
            return this->interp1d_linear(times, data, t, idx_inf);
            break;
    }

    return 0.;
}

double Interpolator1D::interp1d_constant_left(Vector * times, Vector * data, double t, uint16_t idx_inf) const {
    return (*data)[idx_inf]; 
}

double Interpolator1D::interp1d_constant_right(Vector * times, Vector * data, double t, uint16_t idx_inf) const {
    return (*data)[idx_inf+1]; 
}

double Interpolator1D::interp1d_nearest(Vector * times, Vector * data, double t, uint16_t idx_inf) const {
    double mid = ((*times)[idx_inf+1] + (*times)[idx_inf]) / 2.; 
    if (t <= mid) {
        return this->interp1d_constant_left(times, data, t, idx_inf);
    } else {
        return this->interp1d_constant_right(times, data, t, idx_inf);
    }
}

double Interpolator1D::interp1d_linear(Vector * times, Vector * data, double t, uint16_t idx_inf) const {
    double dx = (*times)[idx_inf+1] - (*times)[idx_inf]; 
    double a = ((*data)[idx_inf+1] - (*data)[idx_inf]) / dx; 
    double b = ((*times)[idx_inf+1] * (*data)[idx_inf] -(*times)[idx_inf] * (*data)[idx_inf+1]) / dx;
    return a*t+b; 
}

double Interpolator1D::interp1D_extend_left(Vector * times, Vector * data, double t) const {
    switch (this->extend_left_method) {
        case EXTEND_CONSTANT:
            return (*data)[0];
            break;
        
        default: // extend by 0
            return 0.;
            break;
    }
}

double Interpolator1D::interp1D_extend_right(Vector * times, Vector * data, double t) const {
    switch (this->extend_right_method) {
        case EXTEND_CONSTANT:
            return (*data)[data->get_dim()-1];
            break;
        
        default: // extend by 0
            return 0.;
            break;
    }
}