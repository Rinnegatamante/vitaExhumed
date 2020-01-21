#include "compat.h"

#ifdef _WIN32
# define NEED_PROCESS_H
# include "windows_inc.h"
#endif

#include "mutex.h"
#include <vitasdk.h>

int32_t mutex_init(mutex_t *mutex)
{
#ifdef RENDERTYPEWIN
    *mutex = CreateMutex(0, FALSE, 0);
    return (*mutex == 0);
#else
    *mutex = sceKernelCreateMutex("mutex", 0, 0, NULL);
    return 0;
#endif
}

void mutex_lock(mutex_t *mutex)
{
#ifdef RENDERTYPEWIN
    WaitForSingleObject(*mutex, INFINITE);
#else
	sceKernelLockMutex(*mutex, 1, NULL);
#endif
}

void mutex_unlock(mutex_t *mutex)
{
#ifdef RENDERTYPEWIN
    ReleaseMutex(*mutex);
#else
    sceKernelUnlockMutex(*mutex, 1);
#endif
}
