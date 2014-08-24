#include "ExampleMainPch.h"

#include "Platform/MemoryHeap.h"

#if HELIUM_HEAP

HELIUM_DEFINE_DEFAULT_MODULE_HEAP( ExampleMain );

#if HELIUM_DEBUG
#include "Platform/NewDelete.h"
#endif

#endif // HELIUM_HEAP