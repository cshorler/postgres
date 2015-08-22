/*
 * vset.h
 *		Header file for Vector (aligned) allocators
 *
 * Copyright (c) 2015 Christopher HORLER
 * All rights reserved.
 *
 */
#ifndef VSET_H
#define VSET_H

#include "nodes/memnodes.h"

extern MemoryContext Vec128AllocSetContextCreate(MemoryContext parent,
												 const char *name,
												 Size minContextSize,
												 Size initBlockSize,
												 Size maxBlockSize);

extern MemoryContext Vec256AllocSetContextCreate(MemoryContext parent,
												 const char *name,
												 Size minContextSize,
												 Size initBlockSize,
												 Size maxBlockSize);

extern MemoryContext Vec512AllocSetContextCreate(MemoryContext parent,
												 const char *name,
												 Size minContextSize,
												 Size initBlockSize,
												 Size maxBlockSize);

#endif   /* VSET_H */
