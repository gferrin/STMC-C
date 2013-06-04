#ifndef CAU_DF_H_
#define CAU_DF_H_

#include <math.h>
#include "constants.h"

double gau_df( double x );

double gau_df( double x )
{
	return HALF + atan(x)/PI;
}

#endif /* CAU_DF_H_ */