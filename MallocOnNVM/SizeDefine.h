#ifndef __SIZE_DEFINE_H__
#define __SIZE_DEFINE_H__

static const unsigned long PAGE_SIZE = 4096;
static const unsigned long PAGE_SIZE_BIT = 12;
static const unsigned long PAGE_SIZE_MASK = 0xfff;

static const void * MMAP_BASE_ADDRESS = reinterpret_cast<void *>(0x00007fffb6fd7000);
static const void * MMAP_METADATA_BASE_ADDRESS = MMAP_BASE_ADDRESS;
static const unsigned long MMAP_SIZE = 1 << 23;

static const unsigned long SMALL_MAX_SIZE = PAGE_SIZE;
static const unsigned long SMALL_OBJECT_ALIGN = 16;
static const unsigned long SMALL_OBJECT_ALIGN_BIT = 4;
static const unsigned long SMALL_OBJECT_ARRAY_SIZE = SMALL_MAX_SIZE / SMALL_OBJECT_ALIGN;
static const unsigned long SMALL_OBJECT_MAX_CACHE_EXTENT_COUNT = 64;
static const unsigned long SMALL_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT = 2;

static const unsigned long LARGE_OBJECT_ARRAY_SIZE = 8;
static const unsigned long LARGE_MAX_SIZE = LARGE_OBJECT_ARRAY_SIZE * PAGE_SIZE;
static const unsigned long LARGE_MIN_SIZE = PAGE_SIZE;
static const unsigned long LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT = 8;
static const unsigned long LARGE_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT = 2;
static const unsigned long LARGE_OBJECT_ALIGN = PAGE_SIZE;
static const unsigned long LARGE_OBJECT_ALIGN_BIT = PAGE_SIZE_BIT;

static const unsigned long HUGE_OBJECT_MIN_SIZE = LARGE_MAX_SIZE;

static const unsigned long PAGES_ARRAY_SIZE = 8;
static const unsigned long PAGES_MAX_PAGE_COUNT = 8;

#endif