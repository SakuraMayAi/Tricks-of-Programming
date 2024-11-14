/**
 * Ҫע�⣬�� linux �º� windows ��
 * �����̺߳͵ȴ��߳̽����ĺ����ǲ�һ����
 * ��Ҫ����ϵͳ���и��ģ�����ܲ���
 * 
 * �� linux �´����̵߳Ĺ���
 * ����ͷ�ļ���     <pthread.h>
 * �����̺߳ţ�     pthread_t thread_id;
 * �������̣߳�     pthread_create(&thread_id, NULL, &thread_function, NULL);
 * ���߳̽�����     pthread_join(thread_id, NULL);
 * �̴߳����ɹ��������̺߳ţ������� true�����򷵻� false
 * �߳̽����ɹ����� 0�����򷵻ط���ֵ
 * pthread_join() �ĵڶ���������һ�� void**
 * ��ָ��ָ���ָ�룬���ڱ����߳̽����ķ���ֵ
 * 
 * �� windows �´����̵߳Ĺ���
 * ����ͷ�ļ���     <process.h> <windows.h>
 * �����߳̾����   HANDLE hThread;
 * �������̣߳�     hThread = (HANDLE)_beginthread(&thread_function, 0, this);
 * ��ֹ���̣߳�     _endthread();   // �� thread_function ������
 * ���߳̽�����     WaitForSingleObject(hThread, INFINITE);
 * �ر��߳̾����   CloseHandle(hThread);
 * �� windows �£�WaitForSingleObject() �᷵������ֵ
 * WAIT_TIMEOUT ��ʾ�ȴ���ʱ��WAIT_OBJECT_0 ��ʾ�߳̽���
 * ����ͨ������ֵ���ж��߳��Ƿ����
 */

#include <atomic>
#include <mutex>
#include <vector>

/** ���������
 * ������̳иû��࣬Ȼ��ʵ����ִ�к���������
 * ��ͬ������ʵ���˸��Ե�ִ�к���
 * ������ڴ��� MyWorker ����ʱ
 * ���ǿ��Դ��벻ͬ�����������
 * ʵ��һ���ӿ�ִ�в�ͬ���������������
 * �������� C++ �Ķ�̬��
 */
class MyTasker {};
using PFTask = int (MyTasker::*)(); // ��Ա����ָ��



// ����������
// ��װһ�����������������ִ�к���������
// ͨ�� operator() ���ù������󣬼���ִ������
// ���̳߳��еġ�����ִ�е�Ԫ�����������Ϊ�����ˡ�
class MyWorker
{
public:
    // ָ����Ծ���������ʱִ���ĸ��������
    MyTasker* pTasker;  // ָ����������ָ��
    PFTask pFunc;       // ָ��ִ�к�����ָ��
    
    MyWorker() : pTasker(nullptr), pFunc(nullptr) {}
    /**
     * �������һ����������һ��ָ�� MyTasker* ���͵�ָ��
     * ���� MyTasker ����һ�������� MyTaskerChild
     * �����ʹ����һ�� MyTaskerChild* ���͵�ָ��
     * �ᱻ��ʽ��ת��Ϊ MyTasker* ���ͣ�����ת����
     * ��� pTasker �ᱻ��Ϊ MyTasker* ����
     * ��ʱ pTasker ֻ�ܷ��� MyTasker �ĳ�Ա
     * ���ܷ��� MyTaskerChild �е���չ��Ա
     */
    MyWorker(MyTasker* obj, PFTask pfunc) : pTasker(obj), pFunc(pfunc) {}

    // �������캯��
    MyWorker(const MyWorker& worker)
    {
        pTasker = worker.pTasker;
        pFunc = worker.pFunc;
    }

    // ��ֵ���캯��
    MyWorker& operator=(const MyWorker& worker)
    {
        if (this != &worker)
        {
            pTasker = worker.pTasker;
            pFunc = worker.pFunc;
        }

        return *this;
    }

    // ���ù�������
    // ʵ���ǵ�����������ִ�к������൱�ڡ�����������
    int operator()()    // ���ص������������
    {
        if (IsValid()) return(pTasker->*pFunc)();

        return -1;
    }

    // ��鹤�������Ƿ���Ч
    // ����������Ϊ�գ������������û��ִ�к���
    // ����������߹�����������Ч�ģ����� false��
    bool IsValid() const
    {
        return (pTasker != nullptr) && (pFunc != nullptr);
    }
};



// �Զ����߳���
// ����װ��һ���̣߳���������̵߳���������
// �� UpdateWorker() �����л�ȡһ����������
// ��ͨ�� threadFunc() �����ں�ִ̨������
class MyThread
{
public:
    MyThread()
    {
        // TODO���˴�����̱߳�ʶ������ʼ������
        m_status = false;
    }

    ~MyThread()
    {
        Stop();
    }

    // ����߳��Ƿ���Ч
    // ���� true �����̻߳������У���Ч
    // ���� false �����߳��쳣�����Ѿ���ֹ����Ч
    bool IsValid()
    {
        /**
         * �߳��Ƿ���Ч�Ͳ鿴�̱߳�ʶ����
         * linux �¼��̺߳��Ƿ�Ϊ-1����ʼֵ��
         * winodws �¼�����Ƿ�Ϊ�ջ����Ƿ�Ϊ��Ч���
         */
        // TODO���˴�����ж��̱߳�־���Ƿ���Ч���ж�
        return true;
    }
    
    // �����߳�
    // �����ɹ����� true��ʧ�ܷ��� false
    bool Start()
    {
        m_status = true;
        // TODO���˴�������������̵߳Ĵ���
        if (IsValid() == false) m_status = false;

        return m_status;
    }

    // �����߳�
    // ����߳��Ѿ�ֹͣ�˾ͷ��� false
    // ����̻߳�δֹͣ���͵ȴ��߳�ֱ������
    bool Stop()
    {
        if (m_status == false) return true;
        m_status = false;
        bool ret;
        /**
         * ����ָ��ʱ���ڵȴ��߳���Ȼ����
         * ����߳�û�н���
         * �������ؽӿ�ǿ����ֹ�߳�
         * linux ��Ϊ pthread_exit()
         * windows ��Ϊ WaitForSingleObject()
         * ��ȡ��������������� ret ��
         * ����Ҫע�⣬ǿ����ֹ�߳�ʱ
         * �̳߳��е���Դ�����ڴ桢�ļ���������ȣ����ᱻ�ͷ�
         * ������Ҫ��ӻ�����Դ�����
         */
        //! TODO���˴������ֹ�̵߳Ĵ���
        UpdateWorker(); // �ÿչ�������

        return ret;
    }

    // �����̵߳Ĺ�������
    // �������������Ч�������µ� worker �滻��ǰ��������
    // �������������Ч���������ǰ����
    void UpdateWorker(const MyWorker& worker = MyWorker())
    {
        if (m_worker.load() != nullptr && m_worker.load() != &worker)
        {
            /**
             * load() �� store() ���� std::atomic �ṩ�ĳ�Ա����
             * ǰ���������̰߳�ȫ�ķ�ʽ��ȡԭ�ӱ���
             * ��������ǻ�ȡָ���������ָ��
             * �����������̰߳�ȫ�ķ�ʽ����ԭ�ӱ���
             * ��������ǽ�ָ���ÿգ������Ϊ����ָ��
             */
            MyWorker* pWorker = m_worker.load();
            m_worker.store(nullptr);   // �� m_worker ��ֵ����Ϊ��
            delete pWorker;
        }
        if (worker.IsValid() == false)  // ����������Ч������Ϊ��
        {
            m_worker.store(nullptr);
            return;
        }
        // �� new ��Ӧ����� delete
        m_worker.store(new MyWorker(worker));
    }

    // ����߳��Ƿ����
    // �����������Ϊ�գ����߹���������Ч��˵���߳̿��У����� true
    // �����������Ϊ�գ�������Ч��˵���̲߳��ǿ��еģ����� false
    bool IsIdle()
    {
        if (m_worker.load() == nullptr) return true;
        return !m_worker.load()->IsValid();
    }

private:
    // TODO���˴�����Ψһ��ʶ�̵߳ı���
    // linux �����̺߳ţ�windows���Ǿ��

    // ��ʶ�̵߳�״̬��false ��ʾ�߳̽�Ҫ�رգ�true ��ʾ�߳���������
    bool m_status;

    // MyWorker* ���͵�ԭ�ӱ���
    // ȷ�����̻߳����ж� m_worker �ķ������̰߳�ȫ��
    // m_worker �洢�˵�ǰ�̹߳���Ĺ�������ĵ�ַ
    std::atomic<MyWorker*> m_worker;
    
    // �߳����
    static void threadEntry(void* arg)
    {
        MyThread* thiz = (MyThread*)arg;
        if (thiz) thiz->threadFunc();
        /**
         * �����̣߳��� linux �²���Ҫ
         * linux ���̻߳��Զ���ֹ
         * �� windows ����Ҫ���\
         * _endthread() ���� _endthreadEx()
         */
        // TODO���˴�����߳���ֹ�Ĵ���
    }

    // �̵߳�ʵ�ʹ�������
    void threadFunc()
    {
        while (m_status)
        {
            // �����ڹ�����������ֱ�������˹�������Ϊֹ
            if (!m_worker.load())
            {
                /**
                 * ֮����Ҫ������ߴ���
                 * �Ƿ�ֹ�̳߳���ռ�� CPU
                 * linux ��Ϊ slepp()
                 * windows ��Ϊ Sleep()
                 */
                // TODO���˴�������ߴ���
                continue;
            }
            // ��ȡ��������
            MyWorker worker = *m_worker.load();    
            if (worker.IsValid() == true)   // ����������Ч
            {
                int ret = worker(); // ���ù�������
                /**
                 * ���ݾ�����Ҫ�����Ӧ�Ĵ������
                 * �����ӡ������Ϣ��ִ�лص�������
                 */
                // TODO���˴���������������

                // ���ؽ��С��0��˵�����������������
                // Ҳ���߳�ִ������������̵߳Ĺ������������
                if (ret < 0)
                {
                    MyWorker* pWorker = m_worker.load();
                    m_worker.store(nullptr);
                    delete pWorker;
                }
            }
            else
            {
                // TODO���˴���ӹ���������Чʱ�Ĵ���
                // Ҳ����������ߴ����ֹ����ѭ��
            }
        }
    }
};



// �Զ����̳߳���
// ����װ�˶�һ���̵߳���������ֹ
// ͨ�� DispatchWorker() ������������䵽�����߳���
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

    // �������е����߳�
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
            // ret Ϊ false���������߳�����ʧ��
            // �ر������Ѿ��������߳�
            if (ret == false)
            {
                for (size_t i = 0; i < m_threads.size(); ++i)
                    m_threads[i]->Stop();
            }
        }

        return ret;
    }

    // ��ֹ�������߳�
    void Stop()
    {
        for (size_t i = 0; i < m_threads.size(); ++i)
            m_threads[i]->Stop();
    }

    /** ���乤������
     * ���������������̳߳��п����߳�
     * �������ʹ���̳߳ؿ��Բ��д�������
     * Ҳ��ͨ���̳߳ؿ���ͬʱִ�ж������
     * ��������������̬�����������
     * ����ɹ�ʱ�����̵߳���������
     * ����ʧ��ʱ����-1
     */
    int DispatchWorker(const MyWorker& worker)
    {
        int index = -1;
        m_lock.lock();
        for (size_t i = 0; i < m_threads.size(); ++i)
        {
            // OPTIMIZE�����ü�¼�����߳�����ֵ�ķ�ʽ���Ż�����������ѯ�Ĳ���
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