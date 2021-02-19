typedef void (*TaskFunction_t)( void * );

osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

typedef struct os_thread_def  {
    char                   *name;           ///< Thread name 
    os_pthread             pthread;         ///< start address of thread function
    osPriority             tpriority;       ///< initial thread priority
    uint32_t               instances;       ///< maximum number of instances of that thread function
    uint32_t               stacksize;       ///< stack size requirements in bytes; 0 is default stack size
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    uint32_t               *buffer;         ///< stack buffer for static allocation; NULL for dynamic allocation
    osStaticThreadDef_t    *controlblock;   ///< control block to hold thread's data for static allocation; NULL for dynamic allocation
#endif
} osThreadDef_t;

#define osThreadDef(name, thread, priority, instances, stacksz)  \
    const osThreadDef_t os_thread_def_##name = \
{ #name, (thread), (priority), (instances), (stacksz) }
#endif

osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument)
{
    if (xTaskCreate((TaskFunction_t)thread_def->pthread,(const portCHAR *)thread_def->name,
            thread_def->stacksize, argument, makeFreeRtosPriority(thread_def->tpriority),
            &handle) != pdPASS)  {
        return NULL;
    }
} 
