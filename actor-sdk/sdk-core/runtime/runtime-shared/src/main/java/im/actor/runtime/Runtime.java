package im.actor.runtime;

import im.actor.runtime.actors.ThreadPriority;
import im.actor.runtime.power.WakeLock;
import im.actor.runtime.threading.Dispatcher;
import im.actor.runtime.threading.AtomicIntegerCompat;
import im.actor.runtime.threading.AtomicLongCompat;
import im.actor.runtime.threading.ImmediateDispatcher;
import im.actor.runtime.threading.ThreadLocalCompat;

public class Runtime {

    private static final ThreadingRuntime threadingRuntime = new ThreadingRuntimeProvider();
    private static final DispatcherRuntime dispatcherRuntime = new DispatcherRuntimeProvider();
    private static final MainThreadRuntimeProvider mainThreadRuntime = new MainThreadRuntimeProvider();
    private static final LifecycleRuntime lifecycleRuntime = new LifecycleRuntimeProvider();
    private static final LocaleRuntime localeRuntime = new LocaleRuntimeProvider();

    public static LocaleRuntime getLocaleRuntime() {
        return localeRuntime;
    }

    public static Dispatcher createDispatcher(String name) {
        return threadingRuntime.createDispatcher(name);
    }

    public static ImmediateDispatcher createImmediateDispatcher(String name, ThreadPriority priority) {
        return threadingRuntime.createImmediateDispatcher(name, priority);
    }

    public static long getActorTime() {
        return threadingRuntime.getActorTime();
    }

    public static long getCurrentTime() {
        return threadingRuntime.getCurrentTime();
    }

    public static long getCurrentSyncedTime() {
        return threadingRuntime.getSyncedCurrentTime();
    }

    public static AtomicIntegerCompat createAtomicInt(int init) {
        return threadingRuntime.createAtomicInt(init);
    }

    public static AtomicLongCompat createAtomicLong(long init) {
        return threadingRuntime.createAtomicLong(init);
    }

    public static <T> ThreadLocalCompat<T> createThreadLocal() {
        return threadingRuntime.createThreadLocal();
    }

    public static boolean isSingleThread() {
        return mainThreadRuntime.isSingleThread();
    }

    public static int getCoresCount() {
        return threadingRuntime.getCoresCount();
    }

    public static void checkMainThread() {
        if (mainThreadRuntime.isSingleThread()) {
            return;
        }
        if (!mainThreadRuntime.isMainThread()) {
            throw new RuntimeException("Unable to perform operation not from Main Thread");
        }
    }

    public static void postToMainThread(Runnable runnable) {
        mainThreadRuntime.postToMainThread(runnable);
    }

    public static void dispatch(Runnable runnable) {
        dispatcherRuntime.dispatch(runnable);
    }

    public static void killApp() {
        lifecycleRuntime.killApp();
    }

    public static WakeLock makeWakeLock() {
        return lifecycleRuntime.makeWakeLock();
    }
}