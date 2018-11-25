/** @return True if called from the rendering thread, or if called from ANY thread during single threaded rendering */
extern TASKGRAPH_API bool IsInRenderingThread();