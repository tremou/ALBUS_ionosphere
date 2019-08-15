// linfit.h
// least squares linear fitting with singular value decomposition for ionosphere
//_HIST  DATE NAME PLACE INFO
//	2005 Aug 24  James M Anderson  --JIVE  start
//	2007 Jan 03  JMA  --update for GPS satellite fitting
//	2007 Mar 07  JMA  --add spherical harmonics stuff



#ifndef LINFIT_H
#define LINFIT_H

// INCLUDES
#include "JMA_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "station_reference.h"
#include "station_latlon.h"
#include "observation.h"
#include "observation_3D.h"

#include "latlon_cart.h"
#include "cal_source.h"
#include "VTEC.h"
#include "station_maker.h"


// set up a namespace area for stuff.
namespace MIM_PIM {




// GLOBALS


// FUNCTIONS

//_TITLE  calculate_simple_2D_linear_polynomials
    void calculate_simple_2D_linear_polynomials(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters needed,
                               //    must be in 0 < NUM_PARAM < 10000
                               //    (although anything above 36 is almost
                               //    certainly suspect
        const Real64 x,        // I  the "x" value, typically the longitude here
        const Real64 y,        // I  the "y" value, typically the latitude here
        Real64* const poly     // O  the polynomial holder, as poly[NUM_PARAM]
        );




//_TITLE  fit_simple_linear_model --fit a surface to the observations
    void fit_simple_linear_model(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );


//_TITLE  fit_simple_polar_model --fit a surface to the observations
    void fit_simple_polar_model(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );





//_TITLE  calculate_multilayer_2D_linear_polynomials
    void calculate_multilayer_2D_linear_polynomials(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters needed,
                               //    must be in 0 < NUM_PARAM < 10000
                               //    (although anything above 36 is almost
                               //    certainly suspect)
        const Uint32 NUM_POS,  // I  The number of x and y positions to
                               //    accumulate
        const Real64* const x, // I  the "x" value, typically the longitude here
                               //    as x[NUM_POS]
        const Real64* const y, // I  the "y" value, typically the latitude here
                               //    as y[NUM_POS]
        const Real64* const scale,
                               // I  a scaling factor for each position, as
                               //    scale[NUM_POS]
        Real64* const poly     // O  the polynomial holder, as poly[NUM_PARAM]
        );

    
//_TITLE  fit_multilayer_linear_model --fit a surface to the observations
    void fit_multilayer_linear_model(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_STATIONS,
                               // I  the number of stations
        const Station_LatLon* const station,
                               // I  the stations
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );




//_TITLE  calculate_manylayer_2D_linear_polynomials
    void calculate_manylayer_2D_linear_polynomials(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters needed,
                               //    must be in 0 < NUM_PARAM < 10000
                               //    (although anything above 36 is almost
                               //    certainly suspect
        const Real64 x,        // I  the "x" value, typically the longitude here
        const Real64 y,        // I  the "y" value, typically the latitude here
        const Real64 scale,    // I  a scaling constant to multiply the poly's
        Real64* const poly     // O  the polynomial holder, as poly[NUM_PARAM]
        );
//_TITLE  fit_manylayer_linear_model --fit a surface to the observations
    void fit_manylayer_linear_model(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_STATIONS,
                               // I  the number of stations
        const Station_LatLon* const station,
                               // I  the stations
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );









///////////////////
// GPS stuff







//_TITLE  fit_simple_linear_model_2 --fit a surface to the observations
    Sint32 fit_simple_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        const bool Force_Zero_Mean_Bias,
                               // I  Should the bias level be forced to 0?
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)]
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_simple_linear_model_2
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed




//_TITLE  fit_simple_linear_model_2_grad --fit a surface to the observations
Sint32 fit_simple_linear_model_2_grad(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_POLY+7)
                               //              +NUM_PARAM*2]
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_simple_linear_model_2_grad
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -3 more stations and objects than parameters






    
//_TITLE  apply_simple_linear_model_2 --apply 2-D MIM to observations
    void apply_simple_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        const Real64* const parameters,
                               // I  the fit parameters, as parameters[NUM_PARAM]
        const Real64 std_dev,  // I  The standard deviation from the fit.
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_PARAM]
        Observation_Ionosphere* const observation
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        );



//_TITLE  fit_2D_time_linear_model_2 --fit a surface/time to the observations
Sint32 fit_2D_time_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_TIME_TERMS,
                               // I  The maximum order of time polynomials
                               //    to apply.  The ionosphere is made to have
                               //    a (a_0 t^0 + a_1 t^1 + ... + a_N t^N)
                               //    dependence, where N \equiv NUM_TIME_TERMS-1
                               //    Thus, 1 means constant, 2 for linear, 3
                               //    for quadratic, and so on.
        const Real64 Ref_MJD,  // I  The reference Modified Julian Date to
                               //    compare against for time calculations
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        const bool Force_Zero_Mean_Bias,
                               // I  Should the bias level be forced to 0?
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)
                               //              +NUM_TIME_TERMS*2]
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_2D_time_linear_model_2
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed
//                                   -3 more stations and objects than parameters


//_TITLE  fit_2D_time_linear_model_2_grad --fit surface/time to the observations
Sint32 fit_2D_time_linear_model_2_grad(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_TIME_TERMS,
                               // I  The maximum order of time polynomials
                               //    to apply.  The ionosphere is made to have
                               //    a (a_0 t^0 + a_1 t^1 + ... + a_N t^N)
                               //    dependence, where N \equiv NUM_TIME_TERMS-1
                               //    Thus, 1 means constant, 2 for linear, 3
                               //    for quadratic, and so on.
        const Real64 Ref_MJD,  // I  The reference Modified Julian Date to
                               //    compare against for time calculations
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_POLY+7)
                               //              +NUM_PARAM*6
                               //              +NUM_TIME_TERMS*2]
        Observation_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_2D_time_linear_model_2_grad
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 fitter failed
//                                   -3 more stations and objects than parameters


//_TITLE  apply_2D_time_linear_model_2 --apply 2-D+time MIM to observations
void apply_2D_time_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_TIME_TERMS,
                               // I  The maximum order of time polynomials
                               //    to apply.  The ionosphere is made to have
                               //    a (a_0 t^0 + a_1 t^1 + ... + a_N t^N)
                               //    dependence, where N \equiv NUM_TIME_TERMS-1
                               //    Thus, 1 means constant, 2 for linear, 3
                               //    for quadratic, and so on.
        const Real64 Ref_MJD,  // I  The reference Modified Julian Date to
                               //    compare against for time calculations
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        const Real64* const parameters,
                               // I  the fit parameters, as parameters[NUM_PARAM]
        const Real64 std_dev,  // I  The standard deviation from the fit.
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_PARAM+NUM_TIME_TERMS*2]
        Observation_Ionosphere* const observation
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        );






    
//_TITLE  fit_multilayer_linear_model_2 --fit a surface to the observations
    Sint32 fit_multilayer_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        const bool Force_Zero_Mean_Bias,
                               // I  Should the bias level be forced to 0?
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)
                               //              +NUM_HEIGHTS*6]
        Observation_3D_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_multilayer_linear_model_2
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed



//_TITLE  apply_multilayer_linear_model_2 --apply a surface to the observations
    void apply_multilayer_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        const Real64* const parameters,
                               // I  the fit parameters, as parameters[NUM_PARAM]
        const Real64 std_dev,  // I  The standard deviation from the fit.
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_PARAM + NUM_HEIGHTS*6]
        Observation_3D_Ionosphere* const observation
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        );


//_TITLE  fit_manylayer_linear_model_2 --fit a surface to the observations
    Sint32 fit_manylayer_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        const bool Force_Zero_Mean_Bias,
                               // I  Should the bias level be forced to 0?
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)
                               //              +NUM_HEIGHTS*4]
        Observation_3D_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_manylayer_linear_model_2
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed



//_TITLE  apply_manylayer_linear_model_2 --apply a surface to the observations
    void apply_manylayer_linear_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        const Real64* const parameters,
                               // I  the fit parameters, as parameters[NUM_PARAM]
        const Real64 std_dev,  // I  The standard deviation from the fit.
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_PARAM +NUM_HEIGHTS*4]
        Observation_3D_Ionosphere* const observation
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        );





    
//_TITLE  calculate_manylayer_2D_spherical_h_polynomials
void calculate_manylayer_2D_spherical_h_polynomials(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters needed,
                               //    must be in 0 < NUM_PARAM < 10000
                               //    (although anything above 36 is almost
                               //    certainly suspect
        const LatLon_Cart *const pierce,
                               // I  The pierce point through the ionosphere,
                               //    as a LatLon object, which includes
                               //    \cos(Lat), \sin(Lon), and \cos(Lon)
                               //    information.  Note that this is relative
                               //    to some reference position.
        const Real64 scale,    // I  a scaling constant to multiply the poly's
        Real64* const poly     // O  the polynomial holder, as poly[NUM_PARAM]
        );


//_TITLE  fit_manylayer_spherical_h_model_2 --fit spherical harmonics
Sint32 fit_manylayer_spherical_h_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        const bool Force_Zero_Mean_Bias,
                               // I  Should the bias level be forced to 0?
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)
                               //              +NUM_HEIGHTS*5]
        Observation_3D_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_manylayer_spherical_h_model_2
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed

//_TITLE  fit_manylayer_spherical_h_model_2_grad --fit spherical harmonics
Sint32 fit_manylayer_spherical_h_model_2_grad(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Real64 Ref_MJD,  // I  The refernce time, as an MJD
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_POLY+7)
                               //              +6*NUM_PARAM
                               //              +5*NUM_HEIGHTS]
        Observation_3D_Ionosphere* const observation,
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        Real64& std_dev,       // O  The standard deviation from the fit.
        Real64* const parameters
                               // O  the fit parameters, as parameters[NUM_PARAM]
        );
// Sint32 fit_manylayer_spherical_h_model_2_grad
//                                O  The return code
//                                    0 all ok
//                                   -1 More parameters than datapoints
//                                   -2 SVD fitter failed

    
//_TITLE  apply_manylayer_spherical_h_model_2 --apply spherical harmonics model
void apply_manylayer_spherical_h_model_2(
//_ARGS  TYPE           VARIABLE I/O DESCRIPTION
        const Uint32 NUM_PARAM,// I  the number of parameters to use in the
                               //    fit, must be > 0
        const Uint32 NUM_HEIGHTS,
                               // I  The number of heights to use.  Must be > 0
        const Station_Reference& Ref_Point,
                               // I  The reference point
        const Uint32 NUM_OBSERVATIONS,
                               // I  The total number of observations
                               //    NUM_SOURCES*NUM_STATIONS
        const Uint32 NUM_STATIONS,
                               // I  The total number of stations.  If 0,
                               //    then do not fit for station offset.
        const Uint32 NUM_OBJECTS,
                               // I  The total number of objects.  If 0, then
                               //    do not fit for object offset.
        const bool* const use_flag,
                               // I  The use-flag array.  This function flags
                               //    values outside min and max to false.  This
                               //    must be valid before entering this function
        const Real64* const parameters,
                               // I  the fit parameters, as parameters[NUM_PARAM]
        const Real64 std_dev,  // I  The standard deviation from the fit.
        Real64* workspace,
                               // W  Workspace to perform the fitting stuff.
                               //    must be of size
                               //    workspace[NUM_OBSERVATIONS * (2*NUM_PARAM+4)
                               //              +NUM_PARAM*(NUM_PARAM+2)
                               //              +NUM_HEIGHTS*5]
        Observation_3D_Ionosphere* const observation
                               // B  The observations.
                               //    the model_STEC and sigma_model_STEC
                               //    values will be filled in for those
                               //    observations whose use_flag is true
                               //    otherwise, the values are set to magic
                               //    garbage
        );

    





    void fill_IRI_electron_densities(const Station_LatLon& station,
                                     const struct tm& eval_time);





    





    
    
    

}  // end namespace


#endif // LINFIT_H
