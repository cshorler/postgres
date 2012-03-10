/*-------------------------------------------------------------------------
 *
 * pg_type.h
 *	  definition of the system "type" relation (pg_type)
 *	  along with the relation's initial contents.
 *
 *
 * Portions Copyright (c) 1996-2011, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/catalog/pg_type.h
 *
 * NOTES
 *	  the genbki.pl script reads this file and generates .bki
 *	  information from the DATA() statements.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_VEC_TYPES_H
#define PG_VEC_TYPES_H

#include "catalog/genbki.h"

/* ----------------
 *		pg_type definition.  cpp turns this into
 *		typedef struct FormData_pg_type
 *
 *		Some of the values in a pg_type instance are copied into
 *		pg_attribute instances.  Some parts of Postgres use the pg_type copy,
 *		while others use the pg_attribute copy, so they must match.
 *		See struct FormData_pg_attribute for details.
 * ----------------
 */
#define TypeRelationId	1247
#define TypeRelation_Rowtype_Id  71

#define CATALOG(name,oid)

CATALOG(pg_type,1247) BKI_BOOTSTRAP BKI_ROWTYPE_OID(71) BKI_SCHEMA_MACRO

/* ----------------
 *		initial contents of pg_type
 * ----------------
 */

/*
 * Keep the following ordered by OID so that later changes can be made more
 * easily.
 *
 * For types used in the system catalogs, make sure the values here match
 * TypInfo[] in bootstrap.c.
 */

/* SIMD vector types */
DATA(insert OID = 3122 ( vec128			PGNSP PGUID 16 f b U f t \054 0 0 0 vec128_in vec128_out - - - - - x p f 0 -1 0 0 _null_ _null_ ));
DESCR("128 bit vector type");

DATA(insert OID = 3124 ( vec256			PGNSP PGUID 32 f b U f t \054 0 0 0 vec256_in vec256_out - - - - - y p f 0 -1 0 0 _null_ _null_ ));
DESCR("256 bit vector type");

