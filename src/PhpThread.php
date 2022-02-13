<?php

namespace Mrsuh;

class PhpThread
{
    private static ?\FFI $libc = null;

    private static function init(): void
    {
        if (self::$libc !== null) {
            return;
        }

        if (\php_uname('m') !== 'x86_64') {
            throw new \RuntimeException('Unsupported machine type');
        }

        switch (\php_uname('s')) {
            case 'Linux':
                $libraryFileName = 'phpthreads_linux.so';
                break;
            case 'Darwin':
                $libraryFileName = 'phpthreads_darwin.dylib';
                break;
            default:
                throw new \RuntimeException('Unsupported operating system');
        }

        if (!PHP_ZTS) {
            throw new \RuntimeException('PHP must be compiled with ZTS');
        }

        self::$libc = \FFI::cdef(
            "
            typedef void (*_phpthread_function)();
            void phpthread_create(_phpthread_function function);
            void phpthread_join();
            ",
            __DIR__ . "/../library/" . $libraryFileName);
    }

    public static function run(callable $function): void
    {
        self::init();

        self::$libc->phpthread_create($function);
    }

    public static function wait(): void
    {
        self::init();

        self::$libc->phpthread_join();
    }
}
