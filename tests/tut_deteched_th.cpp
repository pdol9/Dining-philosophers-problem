/* 
	By default all threads are joinable, we will call pthread_detach() so to make 
	a thread detached. A Detached thread automatically releases its allocated resources 
	on exit. No other thread needs to join it.

	If the main function exits then all other threads will be exited.
	
https://btechgeeks.com/posix-detached-vs-joinable-threads-pthread_join-pthread_detach-examples/

 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
void * threadFunc(void * arg)
{
    std::cout << "Thread Function :: Start" << std::endl;
    std::cout << "Thread Function :: End" << std::endl;
    // Return value from thread
    return NULL;
}
int main()
{
    // Thread id
    pthread_t threadId;
    // Create a thread that will funtion threadFunc()
    int err = pthread_create(&threadId, NULL, &threadFunc, NULL);
    // Check if thread is created sucessfuly
    if (err)
    {
        std::cout << "Thread creation failed : " << strerror(err);
        return err;
    }
    else
        std::cout << "Thread Created with ID : " << threadId << std::endl;
    // Do some stuff
    err = pthread_detach(threadId);
    if (err)
        std::cout << "Failed to detach Thread : " << strerror(err) << std::endl;
    // Sleep for 2 seconds because if main function exits, then other threads will
    // be also be killed. Sleep for 2 seconds, so that detached exits by then
    sleep(2);
    std::cout << "Main function ends " << std::endl;
    return 0;
}