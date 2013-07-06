//#include "mainwindow.h"

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxConsoleTraceOutput.hpp>

#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "TraceClientApp.h"

#include "StatusUpdaters/UISensorsFactory.hpp"

#include <NyxLocalTime.hpp>

#include <QtGui/QApplication>
#include <QDir>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>





struct CRYPTO_dynlock_value
{
    pthread_mutex_t mutex;
};

static pthread_mutex_t *mutex_buf = NULL;

/**
 * OpenSSL locking function.
 *
 * @param    mode    lock mode
 * @param    n        lock number
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */
static void locking_function(int mode, int n, const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        pthread_mutex_lock(&mutex_buf[n]);
    } else {
        pthread_mutex_unlock(&mutex_buf[n]);
    }
}

/**
 * OpenSSL uniq id function.
 *
 * @return    thread id
 */
static unsigned long id_function(void)
{
    return ((unsigned long) pthread_self());
}

/**
 * OpenSSL allocate and initialize dynamic crypto lock.
 *
 * @param    file    source file name
 * @param    line    source file line number
 */
static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{
    struct CRYPTO_dynlock_value *value;

    value = (struct CRYPTO_dynlock_value *)
    malloc(sizeof(struct CRYPTO_dynlock_value));
    if (!value) {
        goto err;
    }
    pthread_mutex_init(&value->mutex, NULL);

    return value;

err:
    return (NULL);
}

/**
 * OpenSSL dynamic locking function.
 *
 * @param    mode    lock mode
 * @param    l        lock structure pointer
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */
static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                              const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        pthread_mutex_lock(&l->mutex);
    } else {
        pthread_mutex_unlock(&l->mutex);
    }
}

/**
 * OpenSSL destroy dynamic crypto lock.
 *
 * @param    l        lock structure pointer
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l,
                                 const char *file, int line)
{
    pthread_mutex_destroy(&l->mutex);
    free(l);
}

/**
 * Initialize TLS library.
 *
 * @return    0 on success, -1 on error
 */
int tls_init(void)
{
    int i;

    /* static locks area */
    mutex_buf = (pthread_mutex_t *) malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
    if (mutex_buf == NULL) {
        return (-1);
    }
    for (i = 0; i < CRYPTO_num_locks(); i++) {
        pthread_mutex_init(&mutex_buf[i], NULL);
    }
    /* static locks callbacks */
    CRYPTO_set_locking_callback(locking_function);
    CRYPTO_set_id_callback(id_function);
    /* dynamic locks callbacks */
    CRYPTO_set_dynlock_create_callback(dyn_create_function);
    CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
    CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();

//    RAND_load_file("/dev/urandom", 1024);

    return (0);
}







#define NYXTRACE(filter, output)    { Nyx::CTraceStream stream(filter); stream << output; }



Nyx::CTraceStream& operator << ( Nyx::CTraceStream& stream, const Nyx::CLocalTime& ltime )
{
    stream << ltime.Hours() << L":" << ltime.Minutes() << L":" << ltime.Seconds();
    return stream;
}




int main(int argc, char *argv[])
{
    Nyx::CModuleRef                             refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef                          refNetModule = NyxNet::CModule::Alloc();

#if defined(_DEBUG)
	Nyx::CTraceCompositorRef                    refTraceCompositor = Nyx::CTraceCompositor::Alloc();

    refTraceCompositor->SetOutput(Nyx::CConsoleTraceOutput::Alloc());
//    refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc("TraceViewer"));
#endif

    QDir currentFolder = QDir::current();

    CRYPTO_malloc_init(); // Initialize malloc, free, etc for OpenSSL's use
    SSL_library_init(); // Initialize OpenSSL's SSL libraries
    SSL_load_error_strings(); // Load SSL error strings
    ERR_load_BIO_strings(); // Load BIO error strings
    OpenSSL_add_all_algorithms(); // Load all available encryption algorithms
    tls_init();

    Nyx::CLocalTime     ltime = Nyx::CLocalTime::Get();

    NYXTRACE(0x0, L"current time is : " << ltime << L":");

//    Nyx::CTraceStream(0x0) << ltime.Hours() << L":"
//                           << ltime.Minutes() << L":"
//                           << ltime.Seconds();

    TraceClientCore::CModule                    TraceClientCoreModule;

    Nyx::CTraceStream(0x0).Write(L"Application starting");

    CTraceClientApp     TheApp;

    TheApp.Init(argc, argv);
    TheApp.Run();
    TheApp.Destroy();

	CUISensorsFactory::Terminate();

	TraceClientCoreModule.TracesPools().Clear();

    Nyx::CTraceStream(0x0).Write(L"Application ending");

    return TheApp.ReturnValue();
}

