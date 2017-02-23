#ifndef __SIZE_DEFINE_H__
#define __SIZE_DEFINE_H__

const unsigned int PAGE_SIZE = 4096;

static const unsigned int SMALL_MAX_SIZE = PAGE_SIZE;
static const unsigned int SMALL_OBJECT_ALIGN = 16;
static const unsigned int SMALL_OBJECT_ALIGN_BIT = 4;
static const unsigned int SMALL_OBJECT_ARRAY_SIZE = SMALL_MAX_SIZE / SMALL_OBJECT_ALIGN;

#endif