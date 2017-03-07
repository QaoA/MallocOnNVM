#ifndef __SIZE_DEFINE_H__
#define __SIZE_DEFINE_H__

static const unsigned int PAGE_SIZE = 4096;
static const unsigned int PAGE_SIZE_BIT = 12;
static const unsigned int PAGE_SIZE_MASK = 0xfff;

static const void * MMAP_BASE_ADDRESS = reinterpret_cast<void *>(0x00007fffb6fd7000);
static const unsigned long MMAP_SIZE = 1 << 30;

static const unsigned int SMALL_MAX_SIZE = PAGE_SIZE;
static const unsigned int SMALL_OBJECT_ALIGN = 16;
static const unsigned int SMALL_OBJECT_ALIGN_BIT = 4;
static const unsigned int SMALL_OBJECT_ARRAY_SIZE = SMALL_MAX_SIZE / SMALL_OBJECT_ALIGN;
static const unsigned int SMALL_OBJECT_MAX_CACHE_EXTENT_COUNT = 64;
static const unsigned int SMALL_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT = 2;

static const unsigned int LARGE_OBJECT_ARRAY_SIZE = 8;
static const unsigned int LARGE_MAX_SIZE = LARGE_OBJECT_ARRAY_SIZE * PAGE_SIZE;
static const unsigned int LARGE_MIN_SIZE = PAGE_SIZE;
static const unsigned int LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT = 8;
static const unsigned int LARGE_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT = 2;
static const unsigned int LARGE_OBJECT_ALIGN = PAGE_SIZE;
static const unsigned int LARGE_OBJECT_ALIGN_BIT = PAGE_SIZE_BIT;

static const unsigned int HUGE_OBJECT_MIN_SIZE = LARGE_MAX_SIZE;

static const unsigned int PAGES_ARRAY_SIZE = 8;
static const unsigned int PAGES_MAX_PAGE_COUNT = 8;

#endif