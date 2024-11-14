/**
 * 要注意，在 linux 下和 windows 下
 * 创建线程和等待线程结束的函数是不一样的
 * 需要根据系统进行更改，但框架不变
 * 
 * 在 linux 下创建线程的过程
 * 引入头文件：     <pthread.h>
 * 定义线程号：     pthread_t thread_id;
 * 创建新线程：     pthread_create(&thread_id, NULL, &thread_function, NULL);
 * 等线程结束：     pthread_join(thread_id, NULL);
 * 线程创建成功会设置线程号，并返回 true；否则返回 false
 * 线程结束成功返回 0；否则返回非零值
 * pthread_join() 的第二个参数是一个 void**
 * 即指向指针的指针，用于保存线程结束的返回值
 * 
 * 在 windows 下创建线程的过程
 * 引入头文件：     <process.h> <windows.h>
 * 定义线程句柄：   HANDLE hThread;
 * 创建新线程：     hThread = (HANDLE)_beginthread(&thread_function, 0, this);
 * 终止新线程：     _endthread();   // 在 thread_function 最后调用
 * 等线程结束：     WaitForSingleObject(hThread, INFINITE);
 * 关闭线程句柄：   CloseHandle(hThread);
 * 在 windows 下，WaitForSingleObject() 会返回两种值
 * WAIT_TIMEOUT 表示等待超时；WAIT_OBJECT_0 表示线程结束
 * 可以通过返回值来判断线程是否结束
 */

#include <atomic>
#include <mutex>
#include <vector>

/** 任务对象类
 * 派生类继承该基类，然后实现其执行函数（任务）
 * 不同派生类实现了各自的执行函数
 * 因此在在创建 MyWorker 对象时
 * 我们可以传入不同的派生类对象
 * 实现一个接口执行不同的任务，任务多样化
 * 这体现了 C++ 的多态性
 */
class MyTasker {};
using PFTask = int (MyTasker::*)(); // 成员函数指针



// 工作对象类
// 封装一个具体的任务对象和其执行函数（任务）
// 通过 operator() 调用工作对象，即可执行任务
// 是线程池中的“任务执行单元”，可以理解为“工人”
class MyWorker
{
public:
    // 指针可以决定在运行时执行哪个任务对象
    MyTasker* pTasker;  // 指向任务对象的指针
    PFTask pFunc;       // 指向执行函数的指针
    
    MyWorker() : pTasker(nullptr), pFunc(nullptr) {}
    /**
     * 在这里，第一个参数接收一个指向 MyTasker* 类型的指针
     * 假如 MyTasker 类有一个派生类 MyTaskerChild
     * 如果即使传入一个 MyTaskerChild* 类型的指针
     * 会被隐式的转换为 MyTasker* 类型（向上转换）
     * 因此 pTasker 会被视为 MyTasker* 类型
     * 此时 pTasker 只能访问 MyTasker 的成员
     * 不能访问 MyTaskerChild 中的扩展成员
     */
    MyWorker(MyTasker* obj, PFTask pfunc) : pTasker(obj), pFunc(pfunc) {}

    // 拷贝构造函数
    MyWorker(const MyWorker& worker)
    {
        pTasker = worker.pTasker;
        pFunc = worker.pFunc;
    }

    // 赋值构造函数
    MyWorker& operator=(const MyWorker& worker)
    {
        if (this != &worker)
        {
            pTasker = worker.pTasker;
            pFunc = worker.pFunc;
        }

        return *this;
    }

    // 调用工作对象
    // 实际是调用任务对象的执行函数，相当于“让它工作”
    int operator()()    // 重载调用运算符函数
    {
        if (IsValid()) return(pTasker->*pFunc)();

        return -1;
    }

    // 检查工作对象是否有效
    // 如果任务对象为空，或者任务对象没有执行函数
    // 表明任务或者工作对象是无效的，返回 false，
    bool IsValid() const
    {
        return (pTasker != nullptr) && (pFunc != nullptr);
    }
};



// 自定义线程类
// 它封装了一个线程，并管理该线程的生命周期
// 从 UpdateWorker() 函数中获取一个工作对象
// 并通过 threadFunc() 函数在后台执行任务
class MyThread
{
public:
    MyThread()
    {
        // TODO：此处添加线程标识变量初始化代码
        m_status = false;
    }

    ~MyThread()
    {
        Stop();
    }

    // 检查线程是否有效
    // 返回 true 表明线程还在运行，有效
    // 返回 false 表明线程异常或者已经终止，无效
    bool IsValid()
    {
        /**
         * 线程是否有效就查看线程标识变量
         * linux 下即线程号是否为-1（初始值）
         * winodws 下即句柄是否为空或者是否为无效句柄
         */
        // TODO：此处添加判断线程标志符是否有效的判断
        return true;
    }
    
    // 启动线程
    // 启动成功返回 true，失败返回 false
    bool Start()
    {
        m_status = true;
        // TODO：此处添加启动启动线程的代码
        if (IsValid() == false) m_status = false;

        return m_status;
    }

    // 结束线程
    // 如果线程已经停止了就返回 false
    // 如果线程还未停止，就等待线程直到结束
    bool Stop()
    {
        if (m_status == false) return true;
        m_status = false;
        bool ret;
        /**
         * 先在指定时间内等待线程自然结束
         * 如果线程没有结束
         * 则调用相关接口强制终止线程
         * linux 下为 pthread_exit()
         * windows 下为 WaitForSingleObject()
         * 获取操作结果，保存在 ret 中
         * 但是要注意，强制终止线程时
         * 线程持有的资源（如内存、文件句柄、锁等）不会被释放
         * 所以需要添加回收资源的语句
         */
        //! TODO：此处添加终止线程的代码
        UpdateWorker(); // 置空工作对象

        return ret;
    }

    // 更新线程的工作对象
    // 如果工作对象有效，就用新的 worker 替换当前工作对象
    // 如果工作对象无效，则清除当前任务
    void UpdateWorker(const MyWorker& worker = MyWorker())
    {
        if (m_worker.load() != nullptr && m_worker.load() != &worker)
        {
            /**
             * load() 和 store() 都是 std::atomic 提供的成员函数
             * 前者用于以线程安全的方式获取原子变量
             * 在这里就是获取指向工作对象的指针
             * 后者用于以线程安全的方式更新原子变量
             * 在这里就是将指针置空，以免成为悬挂指针
             */
            MyWorker* pWorker = m_worker.load();
            m_worker.store(nullptr);   // 将 m_worker 的值设置为空
            delete pWorker;
        }
        if (worker.IsValid() == false)  // 工作对象无效，重置为空
        {
            m_worker.store(nullptr);
            return;
        }
        // 该 new 对应上面的 delete
        m_worker.store(new MyWorker(worker));
    }

    // 检查线程是否空闲
    // 如果工作对象为空，或者工作对象无效，说明线程空闲，返回 true
    // 如果工作对象不为空，或者有效，说明线程不是空闲的，返回 false
    bool IsIdle()
    {
        if (m_worker.load() == nullptr) return true;
        return !m_worker.load()->IsValid();
    }

private:
    // TODO：此处声明唯一标识线程的变量
    // linux 下是线程号，windows下是句柄

    // 标识线程的状态：false 表示线程将要关闭；true 表示线程正在运行
    bool m_status;

    // MyWorker* 类型的原子变量
    // 确保多线程环境中对 m_worker 的访问是线程安全的
    // m_worker 存储了当前线程管理的工作对象的地址
    std::atomic<MyWorker*> m_worker;
    
    // 线程入口
    static void threadEntry(void* arg)
    {
        MyThread* thiz = (MyThread*)arg;
        if (thiz) thiz->threadFunc();
        /**
         * 结束线程，在 linux 下不需要
         * linux 下线程会自动终止
         * 在 windows 下需要添加\
         * _endthread() 或者 _endthreadEx()
         */
        // TODO：此处添加线程终止的代码
    }

    // 线程的实际工作函数
    void threadFunc()
    {
        while (m_status)
        {
            // 不存在工作对象，休眠直到分配了工作对象为止
            if (!m_worker.load())
            {
                /**
                 * 之所以要添加休眠代码
                 * 是防止线程持续占用 CPU
                 * linux 下为 slepp()
                 * windows 下为 Sleep()
                 */
                // TODO：此处添加休眠代码
                continue;
            }
            // 获取工作对象
            MyWorker worker = *m_worker.load();    
            if (worker.IsValid() == true)   // 工作对象有效
            {
                int ret = worker(); // 调用工作对象
                /**
                 * 根据具体需要添加相应的处理代码
                 * 比如打印警告信息、执行回调函数等
                 */
                // TODO：此处添加其他处理情况

                // 返回结果小于0，说明工作对象出问题了
                // 也即线程执行任务出错，将线程的工作对象清除掉
                if (ret < 0)
                {
                    MyWorker* pWorker = m_worker.load();
                    m_worker.store(nullptr);
                    delete pWorker;
                }
            }
            else
            {
                // TODO：此处添加工作对象无效时的处理
                // 也可以添加休眠代码防止无限循环
            }
        }
    }
};



// 自定义线程池类
// 它封装了对一组线程的启动和终止
// 通过 DispatchWorker() 将工作对象分配到空闲线程中
class MyThreadPool
{
public:
    MyThreadPool(size_t size)
    {
        m_threads.resize(size);
        for (size_t i = 0; i < size; i++)
            m_threads[i] = new MyThread();
    }

    ~MyThreadPool()
    {
        Stop();
        m_threads.clear();
    }

    // 启动所有的子线程
    bool Invoke()
    {
        bool ret = true;
        for (size_t i = 0; i < m_threads.size(); ++i)
        {
            if (m_threads[i]->Start() == false)
            {
                ret = false;
                break;
            }
            // ret 为 false，表明有线程启动失败
            // 关闭其它已经启动的线程
            if (ret == false)
            {
                for (size_t i = 0; i < m_threads.size(); ++i)
                    m_threads[i]->Stop();
            }
        }

        return ret;
    }

    // 终止所有子线程
    void Stop()
    {
        for (size_t i = 0; i < m_threads.size(); ++i)
            m_threads[i]->Stop();
    }

    /** 分配工作对象
     * 将工作对象分配给线程池中空闲线程
     * 这种设计使得线程池可以并行处理任务
     * 也即通过线程池可以同时执行多个任务
     * 并根据任务量动态调整分配策略
     * 分配成功时返回线程的数组索引
     * 分配失败时返回-1
     */
    int DispatchWorker(const MyWorker& worker)
    {
        int index = -1;
        m_lock.lock();
        for (size_t i = 0; i < m_threads.size(); ++i)
        {
            // OPTIMIZE：采用记录空闲线程索引值的方式，优化下面这种轮询的操作
            if (m_threads[i]->IsIdle())
            {
                m_threads[i]->UpdateWorker(worker);
                index = i;
                break;
            }
        }
        m_lock.unlock();

        return index;
    }

private:
    std::mutex m_lock;
    std::vector<MyThread*> m_threads;
};