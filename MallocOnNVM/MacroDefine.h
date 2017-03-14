#ifndef __MACRO_DEFINE_H__
#define __MACRO_DEFINE_H__

#define GetOffset(ContainerType,fieldName) reinterpret_cast<unsigned long>(&(reinterpret_cast<ContainerType *>(0)->fieldName))
#define GetContainer(ContainerType,fieldName,pAddress) reinterpret_cast<ContainerType *>(reinterpret_cast<unsigned long>(pAddress) - GetOffset(ContainerType,fieldName))

#endif