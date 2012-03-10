/*
 * float_vec.c
 *
 *  Created on: 25 Aug 2011
 *      Author: chorler
 */

#include "postgres.h"

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <limits.h>

#include "catalog/pg_type.h"
#include "libpq/pqformat.h"
#include "utils/array.h"
#include "utils/builtins.h"

/*
 *  note these are picked to match the float defines with added brackets and commas
 */
#define MAXVEC128WIDTH 264
#define MAXVEC256WIDTH 528

struct vec128 {
	float4 v[4];
};

struct vec256 {
	float4 v[8];
};

Datum
vec128_in(PG_FUNCTION_ARGS) {
	char* str = PG_GETARG_CSTRING(0);
	struct vec128* r = (struct vec128*) palloc(sizeof(struct vec128));

	if (sscanf(str, "( %f , %f  , %f  , %f )", r->v, r->v+1, r->v+2, r->v+3) != 4)
		ereport(ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						errmsg("invalid input syntax for vec128: \"%s\"", str)));

	PG_RETURN_POINTER(r);
}

Datum
vec128_out(PG_FUNCTION_ARGS) {
	struct vec128* r = (struct vec128*) PG_GETARG_POINTER(0);
	char* str = (char*) palloc(MAXVEC128WIDTH+1);

	snprintf(str, MAXVEC128WIDTH+1, "(%g, %g, %g, %g)", *r->v, *(r->v+1), *(r->v+2), *(r->v+3));

	PG_RETURN_CSTRING(str);
}

Datum
vec256_in(PG_FUNCTION_ARGS) {
	char* str = PG_GETARG_CSTRING(0);
	struct vec256* r = (struct vec256*) palloc(sizeof(struct vec256));

	if (sscanf(str, "( %f , %f , %f , %f , %f , %f , %f , %f )",
			r->v, r->v+1, r->v+2, r->v+3, r->v+4, r->v+5, r->v+6, r->v+7) != 8)
		ereport(ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						errmsg("invalid input syntax for vec256: \"%s\"", str)));

	PG_RETURN_POINTER(r);
}

Datum
vec256_out(PG_FUNCTION_ARGS) {
	struct vec256* r = (struct vec256*) PG_GETARG_POINTER(0);
	char* str = (char*) palloc(MAXVEC256WIDTH+1);

	snprintf(str, MAXVEC256WIDTH+1, "(%g, %g, %g, %g, %g, %g, %g, %g)",
			*r->v, *(r->v+1), *(r->v+2), *(r->v+3), *(r->v+4), *(r->v+5), *(r->v+6), *(r->v+7));

	PG_RETURN_CSTRING(str);
}
