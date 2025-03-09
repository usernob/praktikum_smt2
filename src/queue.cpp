#include "queue.h"

// TODO: implement memory mapped file for windows
SharedQueue::SharedQueue()
{
    shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);
    if (shm_fd == -1)
    {
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(Queue));

    void *ptr = mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        exit(EXIT_FAILURE);
    }
    queue = static_cast<Queue *>(ptr);
    if (queue->reference_count <= 0 || queue->reference_count > 10) // 10 client seems enough
    {
        init();
    }
    else
    {
        queue->reference_count++;
    }
}

SharedQueue::~SharedQueue()
{
    sem_wait(&queue->mutex);

    queue->reference_count--;
    if (queue->reference_count == 0)
    {
        sem_destroy(&queue->mutex);
        shm_unlink(SHM_NAME);
    }

    sem_post(&queue->mutex);
    munmap(queue, sizeof(Queue));
    close(shm_fd);
}

void SharedQueue::init()
{
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    queue->counter = 0;
    queue->reference_count = 1;
    sem_init(&queue->mutex, 1, 1);
}

bool SharedQueue::enqueue(Order order)
{
    sem_wait(&queue->mutex);

    if (is_full())
    {
        sem_post(&queue->mutex);
        return false;
    }

    queue->counter++;
    queue->data[queue->rear] = order;
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->count++;

    sem_post(&queue->mutex);
    return true;
}

bool SharedQueue::dequeue()
{
    sem_wait(&queue->mutex);

    if (is_empty())
    {
        sem_post(&queue->mutex);
        return false;
    }

    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->count--;

    sem_post(&queue->mutex);
    return true;
}

Order *SharedQueue::front() const
{
    if (is_empty())
    {
        return nullptr;
    }
    return &queue->data[queue->front];
}

int SharedQueue::counter() const
{
    return queue->counter;
}

void SharedQueue::destroy()
{
    shm_unlink(SHM_NAME);
}
