#pragma once

#include "type.h"
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 100
#define SHM_NAME "/my_shared_memory"

struct Queue
{
    int front, rear, count;
    Order data[MAX_QUEUE_SIZE];
    sem_t mutex;
    int reference_count, counter;
};

class SharedQueue
{
private:
    int shm_fd;
    Queue *queue;

public:
    SharedQueue();

    ~SharedQueue();

    void init();

    bool is_empty() const
    {
        return queue->count == 0;
    }

    bool is_full() const
    {
        return queue->count == MAX_QUEUE_SIZE;
    }

    bool enqueue(Order order);
    bool dequeue();

    Order *front() const;
    int counter() const;

    static void destroy();
};
